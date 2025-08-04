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
#include <sstream>
#include <vector>
#include <string>

using namespace std;

namespace helper
{
    void command_parser(branchdb::Database &db, string& cmd_line)
    {
        helper::trim_whitespace(cmd_line);

        stringstream ss(cmd_line);
        string command_str;
        ss >> command_str; // First word of Command

        // convert to Upper Case
        for (char &ch : command_str)
        {
            ch = static_cast<char>(toupper(ch));
        }

        // rest Args
        vector<string> args;
        string arg;

        while (ss >> arg)
        {
            args.push_back(arg);
        }

        auto cmdEnumOpt = helper::CmdStringToEnum(command_str);

        if (!cmdEnumOpt.has_value())
        {
            cout << "[X] Command not allowed: " << command_str << " | Type 'HELP' for list of commands." << endl;
            return;
        }

        switch (cmdEnumOpt.value())
        {
        case helper::CommandEnums::EXIT:
            cout << "Exiting BranchDB CLI. GoodBye!" << endl;
            exit(0);
        case helper::CommandEnums::TEST:
            test::testDB(db);
            break;
        case helper::CommandEnums::HELP:
            command::handleHELP(args);
            break;
        case helper::CommandEnums::SET:
            command::handleSET(db, args);
            break;
        case helper::CommandEnums::GET:
            command::handleGET(db, args);
            break;
        case helper::CommandEnums::DEL:
            command::handleDEL(db, args);
            break;
        case helper::CommandEnums::EXISTS:
            command::handleEXISTS(db, args);
            break;
        case helper::CommandEnums::TTL:
            command::handleTTL(db, args);
            break;
        case helper::CommandEnums::EXPIRE:
            command::handleEXPIRE(db, args);
            break;
        case helper::CommandEnums::PERSIST:
            command::handlePERSIST(db, args);
            break;
        case helper::CommandEnums::GETALL:
            command::handleGET_ALL(db, args);
            break;
        case helper::CommandEnums::FLUSH:
            command::handleFLUSH(db, args);
            break;
        case helper::CommandEnums::INFO:
            command::handleINFO(db, args);
            break;
        default:
            cout << "[X] Invalid command: " << command_str << " | Type 'HELP' for list of commands." << endl;
            break;
        }
    }

}