#include <iostream>
#include <branchdb/database.h>
#include <branchdb/helper/helper.h>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleEXPIRE(branchdb::Database& db, vector<string> &args)
    {
        // EXPIRE x EX 40
        if (args.size() >= 3)
        {
            string key = args[0];
            seconds ttl_duration = seconds(0);

            if (args[1] == "EX")
            {
                long long ttl_val = helper::is_valid_seconds(args[2]);
                if (ttl_val > 0)
                {
                    ttl_duration = seconds(ttl_val);
                }
                else
                {
                    cout << "ERROR: Invalid TTL value provided, must be a non-negative integer." << endl;
                    return;
                }

                db.expire(key, ttl_duration);
            }
            else
            {
                cout << "ERROR: Invalid EXPIRE command format: Too many arguments passed!, Usage: EXPIRE <key> EX <seconds>" << endl;
            }
        }
        else
        {
            cout << "ERROR: EXPIRE command atleast requires <key>, Usage: EXPIRE <key> EX <seconds>" << endl;
        }
    }
}