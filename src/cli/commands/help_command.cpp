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
    void handleHELP(vector<string> &args)
    {
        if (args.size() == 0)
        {
            cout << endl
                 << "--- Branch DB Commands ---" << endl;
            cout << "SET <key> <value> EX <seconds> | ( Sets a key-value as provided & expiry [optional]. )" << endl;
            cout << "GET <key> | ( Retrives value for the key provided. )" << endl;
            cout << "GETALL | ( Logs list of keys exists. )" << endl;
            cout << "DEL <key> | ( Discards key-value pair. )" << endl;
            cout << "EXISTS <key> | ( Checks if a key exists. )" << endl;
            cout << "TTL <key> | ( Returns the remaining time. )" << endl;
            cout << "EXPIRE <key> EX <seconds> | ( Update TTL for an existing key. )" << endl;
            cout << "PERSIST <key> | ( Removes the TTL of a key & sets TTL = 0 )" << endl;
            cout << "FLUSH | ( Asks confirmation before deleting all keys. )" << endl;
            cout << "FLUSH FORCE | ( Delete all keys directly. )" << endl;
            cout << "EXIT" << endl;
            cout << "-------------------------" << endl
                 << endl;
        }
        else
        {
            cout << "ERROR: Invalid HELP command usage, Valid Usage: HELP" << endl;
        }
    }
}