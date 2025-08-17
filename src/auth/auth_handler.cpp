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

// src/auth_handler/auth_handler.cpp
#include "branchdb/auth/auth_handler.h"
#include "branchdb/helper/helper.h"
#include "branchdb/helper/enum_parser.h"
#include "branchdb/db/response_metadata.h"
#include <branchdb/db/database.h>
#include <branchdb/cli/command.h>
#include <sstream>

using namespace std;
using namespace branchdb;

namespace auth_handler
{
    string authenticate_client_session(boost::asio::ip::tcp::socket &socket, branchdb::Database &db)
    {
        while (true)
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
                ss >> command_str;

                // convert to Upper Case
                for (char &ch : command_str)
                {
                    ch = static_cast<char>(toupper(ch));
                }

                string rest_payload;
                ss >> rest_payload;

                branchdb::ResponseMetaData response_obj;
                auto cmdEnumOpt = helper::CmdStringToEnum(command_str);

                if (!cmdEnumOpt.has_value())
                {
                    response_obj = branchdb::make_response(400, false, "Autentication - Invalid command: " + command_str, monostate{});
                }
                else
                {
                    switch (cmdEnumOpt.value())
                    {
                    case helper::CommandEnums::AUTH:
                        response_obj = command::handleAUTH(db, rest_payload);
                        if (response_obj.success)
                        {
                            return rest_payload;
                        }
                        break;
                    case helper::CommandEnums::REGISTER:
                        response_obj = command::handleREGISTER(db, rest_payload);
                        break;
                    default:
                        response_obj = branchdb::make_response(400, false, "[X] AUTH or REGISTER required.", monostate{});
                        break;
                    }
                }

                if (!helper::write_response_to_client(socket, helper::build_serialized_response(response_obj)))
                {
                    socket.close();
                    return "";
                }
            }
            else
            {
                // Client disconnected
                return "";
            }
        }
    }
} // namespace auth_handler