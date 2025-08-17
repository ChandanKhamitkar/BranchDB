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

#ifndef BRANCHDB_HELPER_H
#define BRANCHDB_HELPER_H

#include <string>
#include <branchdb/db/response_metadata.h>
#include <boost/asio.hpp>

namespace helper
{
    long long is_valid_seconds(const string &s);
    void trim_whitespace(string &str);
    branchdb::ResponseMetaData command_parser(branchdb::Database &db, const string &auth_token, string &cmd_line);
    string build_serialized_response(branchdb::ResponseMetaData &response_obj);
    bool write_response_to_client(boost::asio::ip::tcp::socket &socket, string serialized_response);
} // namespace helper

#endif