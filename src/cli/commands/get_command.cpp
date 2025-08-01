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
#include <optional>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleGET(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                optional<string> value = db.get(key);
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid GET command format: Too many arguments passed!, Usage: GET <key>" << endl;
            }
        }
        else
        {
            cout << "ERROR: GET command atleast requires <key>, Usage: GET <key>" << endl;
        }
    }
}