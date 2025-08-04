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

#ifndef BRANCHDB_SOCKET_H
#define BRANCHDB_SOCKET_H
#include <boost/asio.hpp>
#include <branchdb/db/database.h>
#include <string>

namespace persistent_connect
{
    void handle_client(boost::asio::ip::tcp::socket socket, branchdb::Database& db);
} // namespace persistent_connect


#endif