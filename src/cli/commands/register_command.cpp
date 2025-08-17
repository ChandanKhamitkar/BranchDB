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
    branchdb::ResponseMetaData handleREGISTER(branchdb::Database &db, const string &username)
    {
        string new_token;
        if (!db.username_exists(username))
        {
            new_token = db.generate_new_auth_token();
            db.add_auth_token(username, new_token);
        }
        else
        {
            new_token = db.get_stored_token(username);
        }
        return branchdb::make_response(200, true, "Here is your token ", new_token);
    }
}