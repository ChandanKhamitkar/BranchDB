#include "database.h";
#include <iostream>
#include <chrono>
#include <optional>

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
        data_[key] = ValueMetaData(value, ttl_duration);
        cout << "✅SET" << key << " -> " << value << " (TTL: " << ttl_duration.count() << "s)" << endl;
        return true;
    }

    // GET - Logic
    optional<string> Database::get(const string &key)
    {
        auto it = data_.find(key);

        // Key not found
        if (it == data_.end())
        {
            cout << "❌GET: key " << key << " not found." << endl;
            return nullopt;
        }

        // if key expired
        if (it->second.is_expired())
        {
            cout << "❌GET: key " << key << " found but expired. Deleting" << endl;
            data_.erase(it);
            return nullopt;
        }

        // Key found
        cout << "✅GET: key " << key << " -> " << it->second.value << endl;
        return it->second.value;
    }

    // DEL - Logic
    bool Database::del(const string &key)
    {
        size_t erased_count = data_.erase(key);

        // Delete key
        if (erased_count > 0)
        {
            cout << "✅DEL: key " << key << " deleted successfully." << endl;
            return true;
        }

        // Cannot Delete - Key doesn't exists
        cout << "❌DEL: key " << key << " cannot delete, cause key doesn't exists.`" << endl;
        return false;
    }

    // Exists - Logic
    bool Database::exists(const string &key)
    {
        auto it = data_.find(key);

        // Key Not Found
        if (it == data_.end())
        {
            cout << "❌EXISTS: key " << key << " not found." << endl;
            return false;
        }

        // Key expired
        if (it->second.is_expired())
        {
            cout << "❌EXISTS: key " << key << " found but expired. Deleting" << endl;
            data_.erase(it);
            return false;
        }

        // Key Exists
        cout << "✅EXISTS: key " << key << " exists." << endl;
        return true;
    }

    // TTL - Logic
    long long Database::ttl(const string &key)
    {
        auto it = data_.find(key);

        // Key Not Found
        if (it == data_.end())
        {
            cout << "❌TTL: key " << key << " not found." << endl;
            return -2; // -2 indicates key not found
        }

        // Key expired
        if (it->second.is_expired())
        {
            cout << "❌TTL: key " << key << " found but expired. Deleting" << endl;
            data_.erase(it);
            return false;
        }

        long long remaining = it->second.remaining_ttl_seconds();
        cout << "✅TTL: key " << key << " has" << remaining << " seconds remaining." << endl;
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
            cout << "✅Expire: key " << key << " TTL set to " << ttl_duration.count() << "s." << endl;
        }

        // key not found
        else
        {
            cout << "❌EXPIRE: Key '" << key << "' not found." << endl;
        }
    }

    // Persists - Logic
    void Database::persist(const string &key)
    {
        auto it = data_.find(key);

        // key found
        if (it != data_.end())
        {
            it->second.ttl_duration = seconds(0);
            cout << "✅PERSIST: key " << key << " TTL removed." << endl;
        }
        else
        {
            cout << "❌PERSIST: key " << key << " not found." << endl;
        }
    }
}