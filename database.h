#ifndef BRANCHDB_DATABASE_H
#define BRANCHDB_DATABASE_H

#include <string>
#include <unordered_map>
#include <chrono>
#include "value_metadata.h"
#include <optional>

using namespace std;
using namespace chrono;

namespace branchdb
{
    class Database {
        public:
            Database();

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
            bool persist(const string& key);

        private:
            // Core key-value store
            unordered_map<string, ValueMetaData> data_;
    };
} // namespace branchdb
#endif