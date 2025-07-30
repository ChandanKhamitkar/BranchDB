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

#ifndef BRANCHDB_DATABASE_H
#define BRANCHDB_DATABASE_H

#include <string>
#include <unordered_map>
#include <chrono>
#include "value_metadata.h"
#include <optional>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <shared_mutex>

using namespace std;
using namespace chrono;

namespace branchdb
{
    // OP codes
    enum LogOperation : char
    {
        SET_OP = 'S',
        DEL_OP = 'D',
    };

    const string LOG_FILE_NAME = "branchdb.log";
    class Database
    {
    public:
        Database();
        ~Database();

        // SET Method
        bool set(const string &key, const string &value, seconds ttl_duration = seconds(0));

        // GET Method
        optional<string> get(const string &key);

        // DEL Method
        bool del(const string &key);

        // Exists Method : Checks if a key exists
        bool exists(const string &key);

        // TTL Method : Returns the remaining time
        long long ttl(const string &key);

        // expire Method : Sets a new TTL for an existing key.
        bool expire(const string &key, seconds ttl_duration);

        // persist Method : Removes the TTL of a key.
        void persist(const string &key);

        // GETALL Method: logs all keys
        void Database::getall();

        // GETALL Method: logs all keys
        void Database::flush();

        // INFO: Says about ( uptime, Number of keys, etc..)
        void Database::info();

    private:
        // Core key-value store
        unordered_map<string, ValueMetaData> data_;

        // Mutex
        shared_mutex data_mutex_;
        unique_ptr<thread> ttl_cleanup_thread_; // with this we can dynamically create threads
        atomic<bool> stop_ttl_cleanup_ = false; // thread safe boolean flag, which can be shared b/w multiple threads.
        const seconds TTL_SCAN_INTERVAL_ = seconds(5);

        // writing to log
        ofstream log_file_out_;
        bool is_recovering_ = false;

        steady_clock::time_point start_time_;

        // internal SET
        void internal_set(const string &key, const ValueMetaData &metadata);
        bool internal_del(const string &key);

        // Load from log file
        void load_from_log();

        void write_string_to_log(ostream &os, const string &s);
        optional<string> read_string_from_log(istream &is);

        // TTL Cleanup
        void ttl_cleanup_loop();
    };
} // namespace branchdb


#endif