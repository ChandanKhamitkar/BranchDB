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
    branchdb::ResponseMetaData Database::set(const string &auth_token, const string &key, const string &value, seconds ttl_duration)
    {
        unique_lock<shared_mutex> lock(data_mutex_);
        ValueMetaData metadata(value, ttl_duration);
        if (!is_recovering_)
        {
            try
            {
                log_file_out_.put(SET_OP);
                write_string_to_log(log_file_out_, auth_token);
                write_string_to_log(log_file_out_, key);
                metadata.to_binary(log_file_out_);
                log_file_out_.flush(); // writing data to disk immediately
            }
            catch (const runtime_error &e)
            {
                cerr << "ERROR: Failed to log SET operation for key '" << key << "': " << e.what() << endl;
                return branchdb::make_response(500, false, "[SET] Key : " + key + " operation for failed " + e.what(), monostate{});
            }
        }
        internal_set(auth_token, key, metadata);
        // cout << "[OK] SET: key " << key << " -> " << value << " (TTL: " << ttl_duration.count() << "s)" << endl;
        cout << "[OK]" << endl;
        return branchdb::make_response(200, true, "[SET] Key : " + key + " stored successfully.", monostate{});
    }

}