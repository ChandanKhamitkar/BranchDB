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

#include "branchdb/db/database.h"
#include "branchdb/db/response_metadata.h"

namespace command
{
    branchdb::ResponseMetaData handleAUTH(branchdb::Database &db, const string &token)
    {
        if (db.is_valid_auth_token(token))
        {
            return branchdb::make_response(200, true, "AUTH Token verified.", monostate{});
        }
        return branchdb::make_response(400, false, "[X] AUTH failed. Invalid token.", monostate{});
    }
}