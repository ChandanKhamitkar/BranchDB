#include <iostream>
#include <chrono>
#include <fstream>
#include <optional>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include "branchdb/db/database.h";
#include "branchdb/db/value_metadata.h";

using namespace std;
using namespace chrono;

namespace branchdb
{
    // Private Operations
    void Database::write_string_to_log(ostream &os, string &s)
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

    // --- [Private] Internal SET | DEL operation ---
    void Database::internal_set(const string &key, const ValueMetaData &metadata)
    {
        data_[key] = metadata;
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
        cout << "Branch DB initialized. Attempting recovery from " << LOG_FILE_NAME << "..." << endl;
        load_from_log();
        cout << "Recovery complete. Database contains " << data_.size() << " keys." << endl;
    }

    Database::~Database()
    {
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

    // --- Public Operations | CLI Commands Logics ---

    // SET - Logic
    bool Database::set(const string &key, const string &value, seconds ttl_duration)
    {   
        data_.insert_or_assign(key, ValueMetaData(value, ttl_duration));
        cout << "[OK] SET: key " << key << " -> " << value << " (TTL: " << ttl_duration.count() << "s)" << endl;
        return true;
    }

    // GET - Logic
    optional<string> Database::get(const string &key)
    {
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
            data_.erase(it);
            return nullopt;
        }

        // Key found
        cout << "[OK] GET: key " << key << " -> " << it->second.value << endl;
        return it->second.value;
    }

    // DEL - Logic
    bool Database::del(const string &key)
    {
        size_t erased_count = data_.erase(key);

        // Delete key
        if (erased_count > 0)
        {
            cout << "[OK] DEL: key " << key << " deleted successfully." << endl;
            return true;
        }

        // Cannot Delete - Key doesn't exists
        cout << "[X] DEL: key " << key << " cannot delete, cause key doesn't exists.`" << endl;
        return false;
    }

    // Exists - Logic
    bool Database::exists(const string &key)
    {
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
            cout << "[X] EXISTS: key " << key << " found but expired. Deleting" << endl;
            data_.erase(it);
            return false;
        }

        // Key Exists
        cout << "[OK] EXISTS: key " << key << " exists." << endl;
        return true;
    }

    // TTL - Logic
    long long Database::ttl(const string &key)
    {
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
            cout << "[X] TTL: key " << key << " found but expired. Deleting" << endl;
            data_.erase(it);
            return false;
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
        auto it = data_.find(key);

        // Key found
        if (it != data_.end())
        {
            it->second.creation_time = steady_clock::now();
            it->second.ttl_duration = ttl_duration;
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
        auto it = data_.find(key);

        // key found
        if (it != data_.end())
        {
            it->second.ttl_duration = seconds(0);
            cout << "[OK] PERSIST: key " << key << " TTL removed." << endl;
        }
        else
        {
            cout << "[X] PERSIST: key " << key << " not found." << endl;
        }
    }
}