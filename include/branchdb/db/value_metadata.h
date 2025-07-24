#ifndef BRANCHDB_VALUE_METADATA_H
#define BRANCHDB_VALUE_METADATA_H

#include <string>
#include <optional>
#include <chrono> // helps to work with time

using namespace std;
using namespace chrono;
namespace branchdb
{
    struct ValueMetaData
    {
        string value;
        steady_clock::time_point creation_time;
        seconds ttl_duration;

        // initialize constructor
        ValueMetaData(const string& val, seconds ttl = seconds(0)) : value(val), creation_time(steady_clock::now()), ttl_duration(ttl) {}

        // check IF key EXPIRED : Method
        bool is_expired() const;

        // get remaining TTL in seconds : Method
        long long remaining_ttl_seconds() const;

        // Serialization - Data -> Binary Stream
        void to_binary(ostream& os) const;

        // Deserialization - Binary Stream -> Data
        optional<ValueMetaData>  from_binary(istream& is) const;
    };

}
#endif