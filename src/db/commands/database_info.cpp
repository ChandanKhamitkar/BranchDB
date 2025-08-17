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
    branchdb::ResponseMetaData Database::info(const string &auth_token)
    {
        shared_lock<shared_mutex> lock(data_mutex_);

        if (data_.find(auth_token) == data_.end())
        {
            return branchdb::make_response(401, false, "[AUTH] Invalid auth token.", monostate{});
        }

        size_t data_size = data_.at(auth_token).size();
        ;

        auto uptime_duration = steady_clock::now() - start_time_;
        auto uptime_seconds = duration_cast<seconds>(uptime_duration).count();

        cout << "--- Branch DB Info ---" << endl;
        cout << "Total Keys: " << data_size << endl;
        cout << "Uptime: " << uptime_seconds << " seconds" << endl;
        cout << "TTL Scan Interval: " << TTL_SCAN_INTERVAL_.count() << " seconds" << endl;
        cout << "-------------------------" << endl;
        return branchdb::make_response(200, true, "[INFO] executed successfully.", monostate{});
    }
}