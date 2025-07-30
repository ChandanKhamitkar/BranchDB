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

#include <iostream>
#include <branchdb/db/database.h>
#include <branchdb/helper/helper.h>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleSET(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 2)
        {
            string key = args[0];
            string value = args[1];
            seconds ttl_duration = seconds(0);
            if (args.size() >= 4 && (args[2] == "EX" || args[2] == "ex"))
            {
                long long ttl_val = helper::is_valid_seconds(args[3]);
                if (ttl_val > 0)
                {
                    ttl_duration = seconds(ttl_val);
                }
                else
                {
                    cout << "ERROR: Invalid TTL value provided, must be a non-negative integer." << endl;
                    return;
                }
            }
            else if (args.size() > 2)
            {
                cout << "ERROR: Invalid SET command format, Use SET <key> <value> EX <seconds>" << endl;
                return;
            }
            db.set(key, value, ttl_duration);
        }
        else
        {
            cout << "ERROR: SET command atleast requires <key> and <value>, Usage: SET <key> <value> EX <seconds>" << endl;
        }
    }
}