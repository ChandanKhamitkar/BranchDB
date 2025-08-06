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
#include <vector>
#include <branchdb/db/response_metadata.h>

using namespace std;
using namespace chrono;

namespace command
{
    branchdb::ResponseMetaData handleEXPIRE(branchdb::Database &db, vector<string> &args)
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
                    string err_res = "Invalid TTL value provided, must be a non-negative integer.";
                    cout << "ERROR: " << err_res << endl;
                    return branchdb::make_response(400, false, "[EXPIRE] " + err_res, monostate{});
                }
                
                return db.expire(key, ttl_duration);
            }
            else
            {
                string err_res = "Invalid EXPIRE command format: Too many arguments passed!, Usage: EXPIRE <key> EX <seconds>";
                cout << "ERROR: " << err_res << endl;
                return branchdb::make_response(400, false, "[EXPIRE] " + err_res, monostate{});
            }
        }
        else
        {
            string err_res = "EXPIRE command atleast requires <key>, Usage: EXPIRE <key> EX <seconds>";
            cout << "ERROR: " << err_res << endl;
            return branchdb::make_response(400, false, "[EXPIRE] " + err_res, monostate{});
        }
    }
}