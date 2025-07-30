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
#include <thread>
#include <chrono>
#include <optional>
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
                continue;
            }

            switch (cmdEnumOpt.value())
            {
            case helper::CommandEnums::EXIT:
                cout << "Exiting BranchDB CLI. GoodBye!" << endl;
                return;
            case helper::CommandEnums::TEST:
                test::testDB(db);
                break;
            case helper::CommandEnums::HELP:
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
            cin.clear();
        }
    }
}