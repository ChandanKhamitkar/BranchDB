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

#ifndef BRANCHDB_AUTH_H
#define BRANCHDB_AUTH_H

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <branchdb/db/database.h>

using namespace std;

namespace auth_handler
{
    // validates the entire authentication handshake
    string authenticate_client_session(boost::asio::ip::tcp::socket &socket, branchdb::Database &db);
} // namespace auth_handler

#endif