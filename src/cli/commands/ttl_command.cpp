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
#include <vector>
#include <branchdb/db/response_metadata.h>

using namespace std;
using namespace chrono;

namespace command
{
    branchdb::ResponseMetaData handleTTL(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                return db.ttl(key);
            }
            else if (args.size() > 1)
            {
                string err_res = "Invalid TTL command format: Too many arguments passed!, Usage: TTL <key>";
                cout << "ERROR: " << err_res << endl;
                return branchdb::make_response(400, false, "[TTL] " + err_res, monostate{});
            }
        }
        else
        {
            string err_res = "TTL command atleast requires <key>, Usage: TTL <key>";
            cout << "ERROR: " << err_res << endl;
            return branchdb::make_response(400, false, "[TTL] " + err_res, monostate{});
        }
    }
}