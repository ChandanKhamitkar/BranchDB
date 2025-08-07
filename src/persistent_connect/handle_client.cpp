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

namespace persistent_connect
{
    void handle_client(boost::asio::ip::tcp::socket socket, branchdb::Database &db)
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
            cout << "[CLIENT] Buffer data recieved: " << payload << endl;
            cout << "[CLIENT] Payload size: " << payload.size() << " bytes" << endl;
            branchdb::ResponseMetaData response_obj = helper::command_parser(db, payload);

            stringstream ss;
            response_obj.to_binary(ss);
            string serialized_response = ss.str();

            serialized_response += '\n';

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