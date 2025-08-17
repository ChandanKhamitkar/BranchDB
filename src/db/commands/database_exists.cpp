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
    branchdb::ResponseMetaData Database::exists(const string &auth_token, const string &key)
    {
        shared_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        auto it = data_.at(auth_token).find(key);

        // Key Not Found
        if (it == data_.at(auth_token).end())
        {
            cout << "[X] EXISTS: key " << key << " not found." << endl;
            return branchdb::make_response(404, false, "[EXISTS] Key : " + key + " not found.", monostate{});
        }

        // Key expired
        if (it->second.is_expired())
        {
            return branchdb::make_response(404, false, "[DEL] Key : " + key + " expired.", monostate{});
        }

        // Key Exists
        cout << "[OK] EXISTS: key " << key << " exists." << endl;
        return branchdb::make_response(200, true, "[EXISTS] Key : " + key + " exists.", monostate{});
    }

}