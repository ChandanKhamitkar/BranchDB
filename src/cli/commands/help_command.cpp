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
    branchdb::ResponseMetaData handleHELP(vector<string> &args)
    {
        if (args.size() == 0)
        {

            string res =
                "\n--- Branch DB Commands ---\n"
                "SET <key> <value> EX <seconds> | ( Sets a key-value as provided & expiry [optional]. )\n"
                "GET <key> | ( Retrives value for the key provided. )\n"
                "GETALL | ( Logs list of keys exists. )\n"
                "DEL <key> | ( Discards key-value pair. )\n"
                "EXISTS <key> | ( Checks if a key exists. )\n"
                "TTL <key> | ( Returns the remaining time. )\n"
                "EXPIRE <key> EX <seconds> | ( Update TTL for an existing key. )\n"
                "PERSIST <key> | ( Removes the TTL of a key & sets TTL = 0 )\n"
                "FLUSH | ( Asks confirmation before deleting all keys. )\n"
                "FLUSH FORCE | ( Delete all keys directly. )\n"
                "EXIT\n"
                "-------------------------\n\n";

            cout << res;
            return branchdb::make_response(200, true, "[HELP]\n " + res);
        }
        else
        {
            string err_res = "Invalid HELP command usage, Valid Usage: HELP";
            cout << "ERROR: " << err_res << endl;
            return branchdb::make_response(200, true, "[HELP] " + err_res);
        }
    }
}