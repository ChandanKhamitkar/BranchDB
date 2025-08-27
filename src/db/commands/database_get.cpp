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
    branchdb::ResponseMetaData Database::get(const string &auth_token, const string &key)
    {
        shared_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        auto it = data_.at(auth_token).find(key);

        // Key not found
        if (it == data_.at(auth_token).end())
        {
            cout << "[X] GET: key " << key << " not found." << endl;
            return branchdb::make_response(404, false, "[GET] Key : " + key + " not found.", monostate{});
        }

        // if key expired
        if (it->second.is_expired())
        {
            return branchdb::make_response(404, false, "[GET] Key : " + key + " expired.", monostate{});
        }

        // Update the LRU List
        string composite_key = auth_token + ":" + key;
        if(lru_map_.find(composite_key) != lru_map_.end()){
            lru_list_.splice(lru_list_.begin(), lru_list_, lru_map_[composite_key]);          
        }

        // Key found
        cout << "[OK] GET: key " << key << " -> " << it->second.value << endl;
        return branchdb::make_response(200, true, "", it->second.value);
    }

}