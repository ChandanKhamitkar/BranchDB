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
#include <iostream>
#include <chrono>

using namespace std;
using namespace chrono;

namespace branchdb
{

    // Constructor
    Database::Database() : log_file_out_(LOG_FILE_NAME, ios::out | ios::app | ios::binary)
    {
        if (!log_file_out_.is_open())
        {
            throw runtime_error("Failed to open log file for writing: " + LOG_FILE_NAME);
        }
        cout << R"(
 ____                       _       _____  ____  
|  _ \                     | |     |  __ \|  _ \ 
| |_) |_ __ __ _ _ __   ___| |__   | |  | | |_) |
|  _ <| '__/ _` | '_ \ / __| '_ \  | |  | |  _ < 
| |_) | | | (_| | | | | (__| | | | | |__| | |_) |
|____/|_|  \__,_|_| |_|\___|_| |_| |_____/|____/ 
                                                                                                
)" << endl;
        cout << "Branch DB initialized. Attempting recovery from..." << endl;

        start_time_ = steady_clock::now();
        load_auth_tokens_from_file();
        load_from_log();
        cout << "[OK] Recovery complete. Database contains." << endl
             << endl;

        // Start TTL cleanup thread
        ttl_cleanup_thread_ = make_unique<thread>(&Database::ttl_cleanup_loop, this);
    }

    // Destructor
    Database::~Database()
    {
        // Stop and join TTL cleanup thread
        stop_ttl_cleanup_ = true;
        if (ttl_cleanup_thread_ && ttl_cleanup_thread_->joinable())
        {
            ttl_cleanup_thread_->join();
        }

        // close output stream for log file
        if (log_file_out_.is_open())
        {
            log_file_out_.close();
        }
        cout << "BranchDB shut down." << endl;
    }

    // Internal SET
    void Database::internal_set(const string &auth_token, const string &key, const ValueMetaData &metadata)
    {
        if (!metadata.is_expired())
        {
            data_[auth_token][key] = metadata;
        }
    }

    // Internal GET
    bool Database::internal_del(const string &auth_token, const string &key)
    {
        if (data_.find(auth_token) != data_.end())
        {
            return data_.at(auth_token).erase(key) > 0;
        }
        return false;
    }

}