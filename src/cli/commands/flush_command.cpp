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

    void handleFLUSH(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() == 0)
        {
            string confirm;
            cout << "Are you sure to DELETE ALL keys? Type (y/n)" << endl;
            cin >> confirm;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            helper::trim_whitespace(confirm);

            if (!confirm.empty())
            {
                char response = tolower(confirm[0]);
                if (response == ConfirmationCode::YES)
                {
                    cout << "Flushing all keys..." << endl;
                    db.flush();
                }
                else if (response == ConfirmationCode::NO)
                {
                    cout << "User denied flushing, Aborted." << endl;
                    return;
                }
                else
                {
                    cout << "Invalid confirmation received. Type only (y/n)." << endl;
                    return;
                }
            }
            else
            {
                cout << "Confirmation didn't received. Aborted." << endl;
                return;
            }
        }
        else if (args.size() >= 1)
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
                db.flush();
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid FLUSH command format: Too many arguments passed!, Usage: FLUSH or FLUSH FORCE" << endl;
            }
        }
        else
        {
            cout << "ERROR: Invalid FLUSH command usage, Usage: FLUSH or FLUSH FORCE" << endl;
        }
    }
}