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
    branchdb::ResponseMetaData Database::getall(const string &auth_token)
    {
        shared_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        const auto &user_data = data_.at(auth_token);
        if (user_data.empty())
        {
            cout << "DB is empty | No keys exists." << endl;
            return branchdb::make_response(200, true, "[GETALL] DB is empty.", monostate{});
        }

        cout << "Logging ALL keys: " << endl;
        vector<string> keylist;
        for (auto &[key, _] : user_data)
        {
            if (!_.is_expired())
            {
                keylist.push_back(key);
            }
            cout << key << endl;
        }
        return branchdb::make_response(200, true, "[GETALL] Keys List : ", keylist);
    }

}