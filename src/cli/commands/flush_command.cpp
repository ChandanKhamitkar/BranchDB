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

    // Confirmation Codes
    enum ConfirmationCode : char
    {
        YES = 'y',
        NO = 'n',
    };

    branchdb::ResponseMetaData handleFLUSH(branchdb::Database &db, const string &auth_token, vector<string> &args)
    {
        // if (args.size() == 0)
        // {
        //     string confirm;
        //     cout << "Are you sure to DELETE ALL keys? Type (y/n)" << endl;
        //     cin >> confirm;
        //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //     helper::trim_whitespace(confirm);

        //     if (!confirm.empty())
        //     {
        //         char response = tolower(confirm[0]);
        //         if (response == ConfirmationCode::YES)
        //         {
        //             cout << "Flushing all keys..." << endl;
        //             return db.flush(auth_token);
        //         }
        //         else if (response == ConfirmationCode::NO)
        //         {
        //             string res = "User denied flushing, Aborted.";
        //             cout << res << endl;
        //             return branchdb::make_response(200, true, "[FLUSH] " + res, monostate{});
        //         }
        //         else
        //         {
        //             string res = "Invalid confirmation received. Type only (y/n).";
        //             cout << res << endl;
        //             return branchdb::make_response(400, false, "[FLUSH] " + res, monostate{});
        //         }
        //     }
        //     else
        //     {
        //         string res = "Confirmation didn't received. Aborted.";
        //         cout << res << endl;
        //         return branchdb::make_response(400, false, "[FLUSH] " + res, monostate{});
        //     }
        // }
        if (args.size() >= 1)
        {
            string cmd = args[0];
            helper::trim_whitespace(cmd);
            string upper_cmd;
            for (char c : cmd)
            {
                upper_cmd += toupper(c);
            }

            if (args.size() == 1 && upper_cmd == "FORCE")
            {
                cout << "Flushing all keys..." << endl;
                return db.flush(auth_token);
            }
            else if (args.size() > 1)
            {
                string err_res = "Invalid FLUSH command format: Too many arguments passed!, Usage: FLUSH or FLUSH FORCE";
                cout << "ERROR: " << err_res << endl;
                return branchdb::make_response(400, false, "[FLUSH] " + err_res, monostate{});
            }
        }
        string err_res = "Invalid FLUSH command usage, Usage: FLUSH or FLUSH FORCE";
        cout << "ERROR: " << err_res << endl;
        return branchdb::make_response(400, false, "[FLUSH] " + err_res, monostate{});
    }
}