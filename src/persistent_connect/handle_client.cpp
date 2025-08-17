/**
 * BranchDB – An in-memory key-value database
 * with TTL, disk persistence.
 *
 * © 2025 KHAMITKAR SAI CHANDAN
 * Licensed under the Apache License, Version 2.0.
 * You may obtain a copy at:
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * You must retain this header in any redistribution or modification.
 */

#include <iostream>
#include <branchdb/db/database.h>
#include <branchdb/db/response_metadata.h>
#include <branchdb/helper/helper.h>
#include <branchdb/helper/enum_parser.h>
#include <branchdb/cli/command.h>
#include <branchdb/auth/auth_handler.h>
#include <thread>
#include <optional>
#include <string>
#include <boost/asio.hpp>

using namespace std;

namespace persistent_connect
{
    void handle_client(boost::asio::ip::tcp::socket socket, branchdb::Database &db)
    {
        cout << "New connection established : " << socket.remote_endpoint() << endl;

        // Authenticate or Register Token
        string auth_token = auth_handler::authenticate_client_session(socket, db);
        bool user_authenticated = !auth_token.empty();

        // Enter command loop only after client autheticated
        if (user_authenticated)
        {
            cout << "Authentication Successfull." << endl;
            while (true)
            {

                boost::asio::streambuf buffer;
                boost::system::error_code error;

                size_t bytes_read = boost::asio::read_until(socket, buffer, '\n', error);
                if (error == boost::asio::error::eof || bytes_read == 0)
                {
                    cout << "Client disconnected gracefully: " << error.message() << endl;
                    break;
                }
                else if (error)
                {
                    cerr << "Error reading from client: " << error.message() << endl;
                    break;
                }

                // log the payload
                istream is(&buffer);
                string payload;
                getline(is, payload);

                // cout << "[CLIENT] Buffer data recieved: " << payload << endl;
                cout << payload << endl;

                branchdb::ResponseMetaData response_obj = helper::command_parser(db, auth_token, payload);
                if (response_obj.message == "EXIT")
                {
                    if (helper::write_response_to_client(socket,  helper::build_serialized_response(response_obj)))
                    {
                        break;
                    }
                }
                if (!helper::write_response_to_client(socket, helper::build_serialized_response(response_obj)))
                {
                    break;
                }
            }
        }
        else
        {
            cout << "Authentication failed. Disconnecting client." << endl;
            socket.close();
        }
    }
}
