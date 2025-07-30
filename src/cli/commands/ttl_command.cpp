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

using namespace std;
using namespace chrono;

namespace command
{
    void handleTTL(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                db.ttl(key);
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid TTL command format: Too many arguments passed!, Usage: TTL <key>" << endl;
            }
        }
        else
        {
            cout << "ERROR: TTL command atleast requires <key>, Usage: TTL <key>" << endl;
        }
    }
}