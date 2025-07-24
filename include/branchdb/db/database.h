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

using namespace std;
using namespace chrono;

namespace branchdb
{
    // OP codes
    enum LogOperation : char {
        SET_OP = 'S',
        DEL_OP = 'D',
    };

    const string LOG_FILE_NAME = "branchdb.log";
    class Database {
        public:
            Database();
            ~Database();

            // SET Method
            bool set(const string& key, const string& value, seconds ttl_duration = seconds(0));

            // GET Method
            optional<string> get(const string& key);

            // DEL Method
            bool del(const string& key);

            // Exists Method : Checks if a key exists
            bool exists(const string& key);

            // TTL Method : Returns the remaining time
            long long ttl(const string& key);

            // expire Method : Sets a new TTL for an existing key.
            bool expire(const string& key, seconds ttl_duration);

            // persist Method : Removes the TTL of a key.
            void persist(const string& key);

        private:
            // Core key-value store
            unordered_map<string, ValueMetaData> data_;

            // writing to log
            ofstream log_file_out_;
            bool is_recovering_ = false;

            // internal SET 
            void internal_set(const string& key, const ValueMetaData& metadata);
            bool internal_del(const string& key);

            // Load from log file
            void load_from_log();

            void write_string_to_log(ostream& os,const string& s);
            optional<string> read_string_from_log(istream& is);
    };
} // namespace branchdb

#endif