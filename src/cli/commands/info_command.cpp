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
    void handleINFO(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() == 0)
        {
            db.info();
        }
        else
        {
            cout << "ERROR: Invalid INFO command usage, Valid Usage: INFO" << endl;
        }
    }
}