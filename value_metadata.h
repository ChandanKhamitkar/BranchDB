#ifndef BRANCHDB_VALUE_METADATA_H
#define BRANCHDB_VALUE_METADATA_H

#include <string>
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
        bool is_expired() const {
            if(ttl_duration.count() == 0) return false; // if TTL = 0, the Key never expires
            return (steady_clock::now() - creation_time) >= ttl_duration;
        }

        // get remaining TTL in seconds : Method
        long long remaining_ttl_seconds() const {
            if(ttl_duration.count() == 0) return -1; // no expiry
            auto elapsed = steady_clock::now() - creation_time;
            auto remaining = ttl_duration - elapsed;
            if(remaining.count() <= 0) return 0;
            return duration_cast<seconds>(remaining).count();
        }
    };

}
#endif