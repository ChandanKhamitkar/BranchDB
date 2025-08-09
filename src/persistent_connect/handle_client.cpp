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
#include <thread>
#include <optional>
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

        // 1. Get AUTH TOKEN & Verify it
        /*
        string auth_token;
        bool user_authenticated = false;

        boost::asio::streambuf auth_buffer;
        boost::system::error_code auth_error;
        size_t auth_bytes_read = boost::asio::read_until(socket, auth_buffer, '\n', auth_error);

        if (auth_bytes_read > 0)
        {
            istream is(&auth_buffer);
            string auth_payload;
            getline(is, auth_payload);
            cout << "[AUTH] Buffer data recieved: " << auth_payload << endl;

            if (auth_payload.substr(0, 4) == "AUTH")
            {
                string token = auth_payload.substr(4);
                cout << "TOKEN extracted:  " << token << endl;

                if (token == "radheradhe")
                {
                    auth_token = token;
                    user_authenticated = true;

                    branchdb::ResponseMetaData response_obj = branchdb::make_response(200, true, "AUTH Token verified.", monostate{});
                    string serialized_response = helper::build_serialized_response(response_obj);

                    if (!write_response_to_client(socket, serialized_response))
                    {
                        return;
                    }
                }
                else
                {
                    branchdb::ResponseMetaData response_obj = branchdb::make_response(400, false, "[X] AUTH failed. Invalid token.\n", monostate{});
                    string serialized_response = helper::build_serialized_response(response_obj);
                    cerr << "Error: Invalid auth token " << endl;
                    write_response_to_client(socket, serialized_response);
                    return;
                }
            }
            else
            {
                branchdb::ResponseMetaData response_obj = branchdb::make_response(400, false, "[X] AUTH required. First command must be AUTH.\n", monostate{});
                string serialized_response = helper::build_serialized_response(response_obj);
                cerr << "Error: missing auth token " << endl;
                write_response_to_client(socket, serialized_response);
                return;
            }
        }
        */

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
            cout << "[CLIENT] Buffer data recieved: " << payload << endl;
            // cout << "[CLIENT] Payload size: " << payload.size() << " bytes" << endl;
            branchdb::ResponseMetaData response_obj = helper::command_parser(db, payload);

            string serialized_response = helper::build_serialized_response(response_obj);
            boost::system::error_code write_error;
            boost::asio::write(socket, boost::asio::buffer(serialized_response), write_error);

            if (write_error)
            {
                cerr << "Error writing response to client: " << write_error.message() << endl;
                break;
            }
        }
    }
}