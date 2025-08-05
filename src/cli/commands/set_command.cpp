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
#include <branchdb/db/response_metadata.h>

using namespace std;
using namespace chrono;

namespace command
{
    branchdb::ResponseMetaData handleSET(branchdb::Database &db, vector<string> &args)
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
                    string err_res = "Invalid TTL value provided, must be a non-negative integer.";
                    cout << "ERROR: " << err_res << endl;
                    return branchdb::make_response(400, false, "[SET] " + err_res);
                }
            }
            else if (args.size() > 2)
            {   
                string err_res = "Invalid SET command format, Use SET <key> <value> EX <seconds>";
                cout << "ERROR: " << err_res << endl;
                return branchdb::make_response(400, false, "[SET] " + err_res);
            }
            
            return db.set(key, value, ttl_duration);
        }
        else
        {   
            string err_res = "SET command atleast requires <key> and <value>, Usage: SET <key> <value> EX <seconds>";
            cout << "ERROR: " << err_res << endl;
            return branchdb::make_response(400, false, "[SET] " + err_res);
        }
    }
}