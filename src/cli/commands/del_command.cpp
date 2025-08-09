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
    branchdb::ResponseMetaData handleDEL(branchdb::Database &db, const string &auth_token, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                return db.del(auth_token, key);
            }
            else if (args.size() > 1)
            {
                string err_res = "Invalid DEL command format: Too many arguments passed!, Usage: DEL <key>";
                cout << "ERROR: " << err_res << endl;
                return branchdb::make_response(400, false, "[DEL] " + err_res, monostate{});
            }
        }
        string err_res = "DEL command atleast requires <key>, Usage: DEL <key>";
        cout << "ERROR: " << err_res << endl;
        return branchdb::make_response(400, false, "[DEL] " + err_res, monostate{});
    }
}