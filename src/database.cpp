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
#include <fstream>
#include <optional>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <mutex>

using namespace std;
using namespace chrono;

namespace branchdb
{
    // Private Operations
    void Database::write_string_to_log(ostream &os, const string &s)
    {
        uint32_t len = static_cast<uint32_t>(s.length());
        os.write(reinterpret_cast<const char *>(&len), sizeof(len));
        os.write(s.data(), len);
        if (!os.good())
        {
            throw std::runtime_error("Error writing string to log file.");
        }
    }

    optional<string> Database::read_string_from_log(istream &is)
    {
        uint32_t len;
        is.read(reinterpret_cast<char *>(&len), sizeof(len));
        if (!is.good())
            return nullopt;

        const uint32_t MAX_READ_LEN = 1024 * 1024; // 1MB
        if (len > MAX_READ_LEN)
        {
            cerr << "WARNING: Corrupted log entry detected (string length too large: " << len << ")." << endl;
            return nullopt;
        }

        string s;
        s.resize(len);
        is.read(&s[0], len);
        if (!is.good())
            return nullopt;

        return s;
    }

    // 📍--- [Private] Internal SET | DEL operation ---
    void Database::internal_set(const string &key, const ValueMetaData &metadata)
    {
        if(!metadata.is_expired()) {
            data_[key] = metadata;
        }
    }

    bool Database::internal_del(const string &key)
    {
        return data_.erase(key) > 0;
    }

    // --- Database Constructor & Deconstructor
    // ios::out - opens file for writing
    // ios::app - opens file for writing - appends new data at end
    // ios::binary - opens file in binary mode
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
        load_from_log();
        cout << "[OK] Recovery complete. Database contains."<< endl
             << endl;

        // --- Start TTL cleanup thread ---
        ttl_cleanup_thread_ = make_unique<thread>(&Database::ttl_cleanup_loop, this);
    }

    Database::~Database()
    {
        // --- Stop and join TTL cleanup thread ---
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
        cout << "Branch DB shut down." << endl;
    }

    // --- Log recovery Method ---
    void Database::load_from_log()
    {
        is_recovering_ = true;

        ifstream log_file_in(LOG_FILE_NAME, ios::in | ios::binary);
        if (!log_file_in.is_open())
        {
            cerr << "WARNING: Log file '" << LOG_FILE_NAME << "' not found or could not be opened for reading. Starting with empty database." << endl;
            is_recovering_ = false;
            return;
        }

        char op_code;
        while (log_file_in.read(&op_code, sizeof(op_code)))
        {
            try
            {
                optional<string> key_opt = read_string_from_log(log_file_in);
                if (!key_opt)
                {
                    cerr << "ERROR: Corrupted log entry (missing key) or EOF while reading opp: " << op_code << endl;
                    break;
                }

                string key = *key_opt;
                if (op_code == SET_OP)
                {
                    optional<ValueMetaData> metadata_opt = ValueMetaData::from_binary(log_file_in);
                    if (!metadata_opt)
                    {
                        cerr << "ERROR: Corrupted log entry (missing metadata for SET op) for key: " << key << endl;
                        break;
                    }

                    internal_set(key, *metadata_opt);
                }
                else if (op_code == DEL_OP)
                {
                    internal_del(key);
                }
                else
                {
                    cerr << "ERROR: Unknown op_code '" << op_code << "' in log file. Corrupted log?" << endl;
                    break;
                }
            }
            catch (const runtime_error &e)
            {
                cerr << "FATAL ERROR during log recovery: " << e.what() << ". Log may be corrupted. Stopping recovery." << endl;
                break;
            }
        }
        log_file_in.close();
        is_recovering_ = false;
    }

    // --- TTL Cleanup ---
    void Database::ttl_cleanup_loop()
    {
        // cout << "TTL cleanup loop started. Scanning every " << TTL_SCAN_INTERVAL_.count() << " seconds." << endl;

        while (!stop_ttl_cleanup_)
        {
            this_thread::sleep_for(TTL_SCAN_INTERVAL_);
            if (stop_ttl_cleanup_)
                break;

            vector<string> keys_to_delete;

            // acquire Read lock by 'shared_lock' - allows multiple readers or single writer
            {
                shared_lock<shared_mutex> lock(data_mutex_);
                for (const auto &pair : data_)
                {
                    if (pair.second.is_expired())
                    {
                        keys_to_delete.push_back(pair.first);
                    }
                }
            } // Release Read lock

            // acquire Write lock by 'unique_lock'
            if (!keys_to_delete.empty())
            {
                unique_lock<shared_mutex> lock(data_mutex_);
                for (const string &key : keys_to_delete)
                {
                    internal_del(key);
                    // cout << "[TTL BG Cleaner] Expired key '" << key << "' removed from memory." << endl;
                }

                // Deallocate occupied space
                keys_to_delete.clear();
                keys_to_delete.shrink_to_fit();
            }
        }
        cout << "TTL cleanup thread stopped." << std::endl;
    }

    // 📍--- Public Operations | CLI Commands Logics ---

    // SET - Logic
    bool Database::set(const string &key, const string &value, seconds ttl_duration)
    {
        ValueMetaData metadata(value, ttl_duration);
        unique_lock<shared_mutex> lock(data_mutex_);

        if (!is_recovering_)
        {
            try
            {
                log_file_out_.put(SET_OP);
                write_string_to_log(log_file_out_, key);
                metadata.to_binary(log_file_out_);
                log_file_out_.flush(); // writing data to disk immediately
            }
            catch (const runtime_error &e)
            {
                cerr << "ERROR: Failed to log SET operation for key '" << key << "': " << e.what() << endl;
                return false;
            }
        }
        internal_set(key, metadata);
        cout << "[OK] SET: key " << key << " -> " << value << " (TTL: " << ttl_duration.count() << "s)" << endl;
        return true;
    }

    // GET - Logic
    optional<string> Database::get(const string &key)
    {
        shared_lock<shared_mutex> lock(data_mutex_);
        auto it = data_.find(key);

        // Key not found
        if (it == data_.end())
        {
            cout << "[X] GET: key " << key << " not found." << endl;
            return nullopt;
        }

        // if key expired
        if (it->second.is_expired())
        {
            cout << "[X] GET: key " << key << " found but expired. Deleting" << endl;
            return nullopt;
        }

        // Key found
        cout << "[OK] GET: key " << key << " -> " << it->second.value << endl;
        return it->second.value;
    }

    // DEL - Logic
    bool Database::del(const string &key)
    {
        unique_lock<shared_mutex> lock(data_mutex_);
        if (!is_recovering_)
        {
            try
            {
                log_file_out_.put(DEL_OP);
                write_string_to_log(log_file_out_, key);
                log_file_out_.flush();
            }
            catch (const runtime_error &e)
            {
                cerr << "ERROR: Failed to log DEL operation for key '" << key << "': " << e.what() << endl;
                return false;
            }
        }

        bool was_deleted = internal_del(key);
        if (was_deleted)
        {
            cout << "[OK] DEL: key " << key << " deleted successfully." << endl;
        }
        else
        {
            // Cannot Delete - Key doesn't exists
            cout << "[X] DEL: key " << key << " cannot delete, cause key doesn't exists.`" << endl;
        }
        return was_deleted;
    }

    // Exists - Logic
    bool Database::exists(const string &key)
    {
        shared_lock<shared_mutex> lock(data_mutex_);
        auto it = data_.find(key);

        // Key Not Found
        if (it == data_.end())
        {
            cout << "[X] EXISTS: key " << key << " not found." << endl;
            return false;
        }

        // Key expired
        if (it->second.is_expired())
        {
            return false;
        }

        // Key Exists
        cout << "[OK] EXISTS: key " << key << " exists." << endl;
        return true;
    }

    // TTL - Logic
    long long Database::ttl(const string &key)
    {
        shared_lock<shared_mutex> lock(data_mutex_);
        auto it = data_.find(key);

        // Key Not Found
        if (it == data_.end())
        {
            cout << "[X] TTL: key " << key << " not found." << endl;
            return -2; // -2 indicates key not found
        }

        // Key expired
        if (it->second.is_expired())
        {
            return 0;
        }

        long long remaining = it->second.remaining_ttl_seconds();
        // Persist Key
        if (remaining == -1)
        {
            cout << "[OK] TTL: key " << key << " has no expiry" << endl;
        }
        else
        {
            cout << "[OK] TTL: key " << key << " has " << remaining << " seconds remaining." << endl;
        }
        return remaining;
    }

    // Expire - Logic
    bool Database::expire(const string &key, seconds ttl_duration)
    {
        unique_lock<shared_mutex> lock(data_mutex_);
        auto it = data_.find(key);

        // Key found
        if (it != data_.end())
        {
            ValueMetaData new_metadata(it->second.value, ttl_duration);
            if (!is_recovering_)
            {
                try
                {
                    log_file_out_.put(SET_OP);
                    write_string_to_log(log_file_out_, key);
                    new_metadata.to_binary(log_file_out_);
                    log_file_out_.flush();
                }
                catch (const runtime_error &e)
                {
                    cerr << "ERROR: Failed to log EXPIRE operation for key '" << key << "': " << e.what() << endl;
                    return false;
                }
            }
            internal_set(key, new_metadata);
            cout << "[OK] Expire: key " << key << " TTL set to " << ttl_duration.count() << "s." << endl;
            return true;
        }

        // key not found
        cout << "[X] EXPIRE: Key '" << key << "' not found." << endl;
        return false;
    }

    // Persists - Logic
    void Database::persist(const string &key)
    {
        unique_lock<shared_mutex> lock(data_mutex_);
        auto it = data_.find(key);

        // key found
        if (it != data_.end())
        {
            ValueMetaData new_metadata(it->second.value, seconds(0));
            // Add to logs
            if (!is_recovering_)
            {
                try
                {
                    log_file_out_.put(SET_OP);
                    write_string_to_log(log_file_out_, key);
                    new_metadata.to_binary(log_file_out_);
                    log_file_out_.flush();
                }
                catch (const runtime_error &e)
                {
                    cerr << "ERROR: Failed to log PERSIST operation for key '" << key << "': " << e.what() << endl;
                    return;
                }

                internal_set(key, new_metadata);
                cout << "[OK] PERSIST: key " << key << " TTL removed." << endl;
            }
        }
        else
        {
            cout << "[X] PERSIST: key " << key << " not found." << endl;
        }
    }

    // GETALL - Logic
    void Database::getall()
    {
        shared_lock<shared_mutex> lock(data_mutex_);
        if (data_.empty())
        {
            cout << "DB is empty | No keys exists." << endl;
            return;
        }

        cout << "Logging ALL keys: " << endl;
        for (auto &[key, _] : data_)
        {
            if (_.is_expired())
            {
                cout << key << " (expired)." << endl;
            }
            else
                cout << key << endl;
        }
        cout << "Total keys count: " << data_.size() << endl;

        return;
    }

    // FLUSH - Logic
    void Database::flush()
    {
        unique_lock<shared_mutex> lock(data_mutex_);

        if (data_.empty())
        {
            cout << "Zero keys exists to FLUSH." << endl;
            return;
        }

        if (!is_recovering_)
        {
            try
            {
                for (const auto &[key, _] : data_)
                {
                    log_file_out_.put(DEL_OP);
                    write_string_to_log(log_file_out_, key);
                }
                log_file_out_.flush();
            }
            catch (const runtime_error &e)
            {
                cerr << "ERROR: Failed to log FLUSH operation. " << e.what() << endl;
                return;
            }
        }

        size_t deleted_count = data_.size();
        data_.clear();

        cout << "[OK] FLUSH: " << deleted_count << " key(s) deleted." << endl;
        return;
    }

    // INFO - Logic
    void Database::info()
    {
        shared_lock<shared_mutex> lock(data_mutex_);
        size_t data_size = data_.size();

        auto uptime_duration = steady_clock::now() - start_time_;
        auto uptime_seconds = duration_cast<seconds>(uptime_duration).count();

        cout << "--- Branch DB Info ---" << endl;
        cout << "Total Keys: " << data_size << endl;
        cout << "Uptime: " << uptime_seconds << " seconds" << endl;
        cout << "TTL Scan Interval: " << TTL_SCAN_INTERVAL_.count() << " seconds" << endl;
        cout << "-------------------------" << endl;
    }
}