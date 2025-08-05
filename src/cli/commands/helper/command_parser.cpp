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
    branchdb::ResponseMetaData command_parser(branchdb::Database &db, string &cmd_line)
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
            return branchdb::make_response(400, false, "Invalid command: " + command_str + " | Type 'HELP' for list of commands.");
        }

        switch (cmdEnumOpt.value())
        {
        case helper::CommandEnums::EXIT:
            cout << "Exiting BranchDB CLI. GoodBye!" << endl;
            return branchdb::make_response(200, true, "Exiting BranchDB CLI. GoodBye!");
            // exit(0);
        case helper::CommandEnums::TEST:
            test::testDB(db);
            return branchdb::make_response(200, true, "DONE with testing DB");
        case helper::CommandEnums::HELP:
            return command::handleHELP(args);
            break;
        case helper::CommandEnums::SET:
            return command::handleSET(db, args);
            break;
        case helper::CommandEnums::GET:
            return command::handleGET(db, args);
            break;
        case helper::CommandEnums::DEL:
            return command::handleDEL(db, args);
            break;
        case helper::CommandEnums::EXISTS:
            return command::handleEXISTS(db, args);
            break;
        case helper::CommandEnums::TTL:
            return command::handleTTL(db, args);
            break;
        case helper::CommandEnums::EXPIRE:
            return command::handleEXPIRE(db, args);
            break;
        case helper::CommandEnums::PERSIST:
            return command::handlePERSIST(db, args);
            break;
        case helper::CommandEnums::GETALL:
            return command::handleGET_ALL(db, args);
            break;
        case helper::CommandEnums::FLUSH:
            return command::handleFLUSH(db, args);
            break;
        case helper::CommandEnums::INFO:
            return command::handleINFO(db, args);
            break;
        default:
            cout << "[X] Invalid command: " << command_str << " | Type 'HELP' for list of commands." << endl;
            return branchdb::make_response(400, false, "Invalid command: " + command_str + " | Type 'HELP' for list of commands.");
        }
    }

}