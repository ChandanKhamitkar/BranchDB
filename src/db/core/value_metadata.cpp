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

#include "branchdb/db/value_metadata.h";
#include <string>
#include <chrono>
#include <stdexcept>
#include <limits>
#include <ostream>
#include <istream>
#include <optional>

using namespace std;
using namespace chrono;

namespace branchdb
{   

    // 'const' is being used cause -> in below methods we are just reading data, not modifying it.

    // check IF key EXPIRED : Method
    bool ValueMetaData::is_expired() const
    {
        if (ttl_duration.count() == 0)
            return false; // if TTL = 0, the Key never expires
        return (steady_clock::now() - creation_time) >= ttl_duration;
    }

    // get remaining TTL in seconds : Method
    long long ValueMetaData::remaining_ttl_seconds() const
    {
        if (ttl_duration.count() == 0)
            return -1; // no expiry
        auto elapsed = steady_clock::now() - creation_time;
        auto remaining = ttl_duration - elapsed;
        if (remaining.count() <= 0)
            return 0;
        return duration_cast<seconds>(remaining).count();
    }

    // Serialization - Data -> Binary Stream
    void ValueMetaData::to_binary(ostream &os) const
    {
        long long ttl_val = ttl_duration.count();
        os.write(reinterpret_cast<const char *>(&ttl_val), sizeof(ttl_val));
        
        long long creation_time_ticks = creation_time.time_since_epoch().count();
        os.write(reinterpret_cast<const char *>(&creation_time_ticks), sizeof(creation_time_ticks));
        
        uint32_t value_len = static_cast<uint32_t>(value.length());
        os.write(reinterpret_cast<const char *>(&value_len), sizeof(value_len));
        
        os.write(value.data(), value_len);
        
        if (!os.good())
        {
            throw std::runtime_error("Error writing ValueMetadata to binary stream.");
        }
    }
    
    // Deserialization - Binary Stream -> Data
    optional<ValueMetaData>  ValueMetaData::from_binary(istream& is) {
        if(!is.good() || is.peek() == EOF) {
            return nullopt;
        }

        ValueMetaData temp_data("", seconds(0));

        // TTL
        long long ttl_val;
        is.read(reinterpret_cast<char*>(&ttl_val), sizeof(ttl_val));
        if(!is.good()) return nullopt;
        temp_data.ttl_duration = seconds(ttl_val);
        
        
        // Creation Time
        long long creation_time_ticks;
        is.read(reinterpret_cast<char*>(&creation_time_ticks), sizeof(creation_time_ticks));
        if(!is.good()) return nullopt;
        temp_data.creation_time = steady_clock::time_point(steady_clock::duration(creation_time_ticks));
        
        // Value Length
        uint32_t value_len;
        is.read(reinterpret_cast<char*>(&value_len), sizeof(value_len));
        if(!is.good()) return nullopt;
        
        // Value Data
        if(value_len > is.rdbuf()->in_avail()) return nullopt;
        temp_data.value.resize(value_len);
        is.read(&temp_data.value[0], value_len);
        if(!is.good()) return nullopt;

        return temp_data;
    }
}