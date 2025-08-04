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
#include <branchdb/test/main_test.h>
#include <branchdb/cli/command.h>
#include <branchdb/helper/enum_parser.h>
#include <branchdb/helper/helper.h>
#include <chrono>
#include <sstream>
#include <vector>
#include <string>

using namespace std;
using namespace chrono;

namespace cli
{
    void startCLI(branchdb::Database &db)
    {
        cout << "BranchDB CLI. Type 'EXIT' to quit." << endl;

        string cmd_line;
        while (true)
        {
            cout << "> ";
            getline(cin, cmd_line);
            helper::command_parser(db, cmd_line);
            cin.clear();
        }
    }
}