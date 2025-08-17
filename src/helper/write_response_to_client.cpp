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
#include <string>
#include <boost/asio.hpp>

using namespace std;

namespace helper
{
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

}