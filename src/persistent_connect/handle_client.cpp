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
#include <thread>
#include <optional>
#include <string>
#include <boost/asio.hpp>

using namespace std;

bool write_response_to_client(boost::asio::ip::tcp::socket &socket, string serialized_response)
{
    boost::system::error_code write_error;
    boost::asio::write(socket, boost::asio::buffer(serialized_response), write_error);

    if (write_error)
    {
        cerr << "Error writing response to client: " << write_error.message() << endl;
        return false;
    }

    return true;
}

namespace persistent_connect
{
    void handle_client(boost::asio::ip::tcp::socket socket, branchdb::Database &db)
    {
        cout << "New connection established : " << socket.remote_endpoint() << endl;

        // 1. Get AUTH TOKEN & Verify it
        string auth_token;
        bool user_authenticated = false;

        while (!user_authenticated)
        {
            boost::asio::streambuf auth_buffer;
            boost::system::error_code auth_error;
            size_t auth_bytes_read = boost::asio::read_until(socket, auth_buffer, '\n', auth_error);

            if (auth_bytes_read > 0)
            {
                istream is(&auth_buffer);
                string auth_payload;
                getline(is, auth_payload);
                helper::trim_whitespace(auth_payload);

                stringstream ss(auth_payload);
                string command_str;
                ss >> command_str; // First word of Command

                string rest_payload;
                ss >> rest_payload;

                branchdb::ResponseMetaData response_obj;
                auto cmdEnumOpt = helper::CmdStringToEnum(command_str);

                if (!cmdEnumOpt.has_value())
                {
                    branchdb::ResponseMetaData response_obj = branchdb::make_response(400, false, "Invalid command: " + command_str + " | Type 'HELP' for list of commands.", monostate{});
                    write_response_to_client(socket, helper::build_serialized_response(response_obj));
                    return;
                }

                switch (cmdEnumOpt.value())
                {
                case helper::CommandEnums::AUTH:
                    response_obj = command::handleAUTH(db, rest_payload);
                    if (response_obj.success)
                    {
                        auth_token = rest_payload;
                        user_authenticated = true;
                    }
                    break;

                case helper::CommandEnums::REGISTER:
                    response_obj = command::handleREGISTER(db, rest_payload);
                    break;

                default:
                    response_obj = branchdb::make_response(400, false, "[X] AUTH or REGISTER required. First command must be AUTH.", monostate{});
                    break;
                }

                if (!write_response_to_client(socket, helper::build_serialized_response(response_obj)))
                {
                    return;
                }
                if (!user_authenticated && response_obj.success == false)
                {
                    return;
                }
            }
            else
            {
                socket.close();
                return;
            }
        }

        if (user_authenticated)
        {
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

                branchdb::ResponseMetaData response_obj = helper::command_parser(db, "radheradhe", payload);
                string serialized_response = helper::build_serialized_response(response_obj);

                if (!write_response_to_client(socket, helper::build_serialized_response(response_obj)))
                {
                    break;
                }
            }
        }
    }
}
