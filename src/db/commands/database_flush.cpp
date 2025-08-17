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

#include "branchdb/db/value_metadata.h"
#include "branchdb/db/database.h"
#include "branchdb/db/response_metadata.h"
#include <iostream>
#include <mutex>

using namespace std;

namespace branchdb
{
    branchdb::ResponseMetaData Database::flush(const string &auth_token)
    {
        unique_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        auto &user_data = data_.at(auth_token);
        if (user_data.empty())
        {
            cout << "Zero keys exists to FLUSH." << endl;
            return branchdb::make_response(200, true, "[FLUSH] Zero keys exists to flush.", monostate{});
        }

        size_t deleted_count = user_data.size();
        user_data.clear();

        compact_log();

        cout << "[OK] FLUSH: " << deleted_count << " key(s) deleted." << endl;
        return branchdb::make_response(200, true, "[FLUSH] " + to_string(deleted_count) + " key(s) deleted.", monostate{});
    }

}