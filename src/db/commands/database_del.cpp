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
    branchdb::ResponseMetaData Database::del(const string &auth_token, const string &key)
    {
        unique_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        if (!is_recovering_)
        {
            try
            {
                log_file_out_.put(DEL_OP);
                write_string_to_log(log_file_out_, auth_token);
                write_string_to_log(log_file_out_, key);
                log_file_out_.flush();
            }
            catch (const runtime_error &e)
            {
                cerr << "ERROR: Failed to log DEL operation for key '" << key << "': " << e.what() << endl;
                return branchdb::make_response(500, false, "[DEL] Key : " + key + " operation failed " + e.what(), monostate{});
            }
        }

        bool was_deleted = internal_del(auth_token, key);
        if (was_deleted)
        {
            cout << "[OK] DEL: key " << key << " deleted successfully." << endl;
            return branchdb::make_response(200, true, "[DEL] Key : " + key + " deleted successfully.", monostate{});
        }
        else
        {
            // Cannot Delete - Key doesn't exists
            cout << "[X] DEL: key " << key << " cannot delete, cause key doesn't exists.`" << endl;
        }
        return branchdb::make_response(404, false, "[DEL] Key : " + key + " not found.", monostate{});
    }

}
