#include <iostream>
#include <chrono>
#include <optional>
#include "branchdb/database.h";

using namespace std;
using namespace chrono;

namespace branchdb
{
    Database::Database()
    {
        cout << "Branch DB initialized." << endl;
    }

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
        if(remaining == -1){
            cout << "[OK] TTL: key " << key << " has no expiry" << endl;
        }
        else {
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