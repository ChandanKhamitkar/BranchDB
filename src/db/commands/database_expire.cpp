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
    branchdb::ResponseMetaData Database::expire(const string &auth_token, const string &key, seconds ttl_duration)
    {
        unique_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        auto it = data_.at(auth_token).find(key);

        // Key found
        if (it != data_.at(auth_token).end())
        {
            ValueMetaData new_metadata(it->second.value, ttl_duration);
            if (!is_recovering_)
            {
                try
                {
                    log_file_out_.put(SET_OP);
                    write_string_to_log(log_file_out_, auth_token);
                    write_string_to_log(log_file_out_, key);
                    new_metadata.to_binary(log_file_out_);
                    log_file_out_.flush();
                }
                catch (const runtime_error &e)
                {
                    cerr << "ERROR: Failed to log EXPIRE operation for key '" << key << "': " << e.what() << endl;
                    return branchdb::make_response(500, false, "[EXPIRE] Key : " + key + " operation failed " + e.what(), monostate{});
                }
            }
            internal_set(auth_token, key, new_metadata);
            cout << "[OK] Expire: key " << key << " TTL set to " << ttl_duration.count() << "s." << endl;
            return branchdb::make_response(200, true, "[EXPIRE] Key : " + key + " TTL saved successfully.", monostate{});
        }

        // key not found
        cout << "[X] EXPIRE: Key '" << key << "' not found." << endl;
        return branchdb::make_response(404, false, "[EXPIRE] Key : " + key + " not found.", monostate{});
    }

}