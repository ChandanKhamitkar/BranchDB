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
#include <optional>
#include <mutex>
#include <filesystem>

using namespace std;

namespace branchdb
{
    // Write String To Log 
    void Database::write_string_to_log(ostream &os, const string &s)
    {
        uint32_t len = static_cast<uint32_t>(s.length());
        os.write(reinterpret_cast<const char *>(&len), sizeof(len));
        os.write(s.data(), len);
        if (!os.good())
        {
            throw runtime_error("Error writing string to log file.");
        }
    }

    // Read the input stream into a string format.
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

    // Log recovery Method
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
                optional<string> stored_auth_token = read_string_from_log(log_file_in);
                optional<string> key_opt = read_string_from_log(log_file_in);
                if (!key_opt || !stored_auth_token)
                {
                    cerr << "ERROR: Corrupted log entry (missing key) or (missing auth_token) EOF while reading opp: " << endl;
                    break;
                }

                string user_key = *stored_auth_token;
                string key = *key_opt;
                if (op_code == SET_OP)
                {
                    optional<ValueMetaData> metadata_opt = ValueMetaData::from_binary(log_file_in);
                    if (!metadata_opt)
                    {
                        cerr << "ERROR: Corrupted log entry (missing metadata for SET op) for key: " << key << endl;
                        break;
                    }

                    internal_set(user_key, key, *metadata_opt);
                }
                else if (op_code == DEL_OP)
                {
                    internal_del(user_key, key);
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

    // Log Compaction Method
    void Database::compact_log()
    {
        unique_lock<shared_mutex> lock(data_mutex_);

        string temp_log_file = LOG_FILE_NAME + ".tmp";
        ofstream temp_log_out(temp_log_file, ios::out | ios::binary);

        if (!temp_log_out.is_open())
        {
            cerr << "[LOG] ERROR: Failed to open temporary log file for compaction." << endl;
            return;
        }

        try
        {
            for (const auto &[auth_token, user_data] : data_)
            {
                for (const auto &[key, metadata] : user_data)
                {
                    if (!metadata.is_expired())
                    {
                        log_file_out_.put(SET_OP);
                        write_string_to_log(temp_log_out, auth_token);
                        write_string_to_log(temp_log_out, key);
                        metadata.to_binary(temp_log_out);
                    }
                }
            }

            temp_log_out.close();
            log_file_out_.close();
            filesystem::rename(temp_log_file, LOG_FILE_NAME);
            log_file_out_.open(LOG_FILE_NAME, ios::out | ios::app | ios::binary);
        }
        catch (const runtime_error &e)
        {
            cerr << "[LOG] FATAL ERROR during log compaction: " << e.what() << endl;
            log_file_out_.open(LOG_FILE_NAME, ios::out | ios::app | ios::binary);
        }
    }

}