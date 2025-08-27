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
#include <unordered_set>
#include <chrono>
#include "value_metadata.h"
#include <optional>
#include <fstream>
#include <iostream>
#include <memory>
#include <thread>
#include <atomic>
#include <shared_mutex>
#include "response_metadata.h"
#include <list>

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
    const string AUTH_FILE_NAME = "auth_config.config";
    class Database
    {
    public:
        Database();
        ~Database();

        // Validating Authenticate Token
        bool is_valid_auth_token(const string &token) const;

        // Generate a new token and return it.
        string generate_new_auth_token();

        // Store the new token to .config file
        void add_auth_token(const string &username, const string &token);

        // Retrive the token from hashmap.
        string get_stored_token(const string &username);

        // Check if Username exists
        bool username_exists(const string &username) const;

        // SET Method
        branchdb::ResponseMetaData set(const string &auth_token, const string &key, const string &value, seconds ttl_duration = seconds(0));

        // GET Method
        branchdb::ResponseMetaData get(const string &auth_token, const string &key);

        // DEL Method
        branchdb::ResponseMetaData del(const string &auth_token, const string &key);

        // Exists Method : Checks if a key exists
        branchdb::ResponseMetaData exists(const string &auth_token, const string &key);

        // TTL Method : Returns the remaining time
        branchdb::ResponseMetaData ttl(const string &auth_token, const string &key);

        // expire Method : Sets a new TTL for an existing key.
        branchdb::ResponseMetaData expire(const string &auth_token, const string &key, seconds ttl_duration);

        // persist Method : Removes the TTL of a key.
        branchdb::ResponseMetaData persist(const string &auth_token, const string &key);

        // GETALL Method: logs all keys
        branchdb::ResponseMetaData getall(const string &auth_token);

        // GETALL Method: logs all keys
        branchdb::ResponseMetaData flush(const string &auth_token);

        // INFO: Says about ( uptime, Number of keys, etc..)
        branchdb::ResponseMetaData info(const string &auth_token);

    private:
        // Core key-value store
        unordered_map<string, unordered_map<string, ValueMetaData>> data_;

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
        void internal_set(const string &auth_token, const string &key, const ValueMetaData &metadata);
        bool internal_del(const string &auth_token, const string &key);

        // Load from log file
        void load_from_log();

        void write_string_to_log(ostream &os, const string &s);
        optional<string> read_string_from_log(istream &is);

        // TTL Cleanup
        void ttl_cleanup_loop();

        unordered_map<string, string> username_to_token_;
        unordered_map<string, string> token_to_username_;

        // Recover/Load the tokens from config file to Interactable Hashmap
        void load_auth_tokens_from_file();

        // Compact Log - Avoid indefinite growing log file
        void compact_log();

        // LRU 
        list<string> lru_list_;
        unordered_map<string, list<string>::iterator> lru_map_;
        size_t lru_cache_capacity = 10000;
    };
} // namespace branchdb

#endif