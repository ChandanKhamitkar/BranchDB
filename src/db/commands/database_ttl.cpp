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
#include <chrono>
#include <mutex>

using namespace std;
using namespace chrono;

namespace branchdb
{
    branchdb::ResponseMetaData Database::ttl(const string &auth_token, const string &key)
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
            cout << "[X] TTL: key " << key << " not found." << endl;
            // return -2; // -2 indicates key not found
            return branchdb::make_response(404, false, "[TTL] Key : " + key + " not found.", monostate{});
        }

        // Key expired
        if (it->second.is_expired())
        {
            // return 0;
            return branchdb::make_response(404, false, "[TTL] Key : " + key + " expired.", monostate{});
        }

        long long remaining = it->second.remaining_ttl_seconds();
        // Persist Key
        if (remaining == -1)
        {
            cout << "[OK] TTL: key " << key << " has no expiry" << endl;
            return branchdb::make_response(200, true, "[TTL] Key : " + key + " has no expiry.", monostate{});
        }
        else
        {
            cout << "[OK] TTL: key " << key << " has " << remaining << " seconds remaining." << endl;
        }
        // return remaining;
        return branchdb::make_response(200, true, "[TTL] Key : " + key + " has " + to_string(remaining) + " seconds remaining.", monostate{});
    }

}