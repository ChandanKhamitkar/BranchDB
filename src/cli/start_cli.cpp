#include <iostream>
#include <branchdb/database.h>
#include <branchdb/test/main_test.h>
#include <branchdb/cli/command.h>
#include <thread>
#include <chrono>
#include <optional>
#include <sstream>
#include <vector>

using namespace std;
using namespace chrono;

namespace cli
{
    void startCLI(branchdb::Database& db)
    {
        cout << "BranchDB CLI. Type 'EXIT' to quit." << endl;

        string cmd_line;
        while (true)
        {
            cout << "> ";
            getline(cin, cmd_line);
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

            if (command_str == "EXIT")
            {
                cout << "Exiting BranchDB CLI. GoodBye!" << endl;
                break;
            }
            else if (command_str == "TEST")
            {
                test::testDB(db);
            }
            else if (command_str == "HELP")
            {
                cout << endl << "--- Branch DB Commands ---" << endl;
                cout << "SET <key> <value> EX <seconds> | ( Sets a key-value as provided & expiry [optional]. )" << endl;
                cout << "GET <key> | ( Retrives value for the key provided. )" << endl;
                cout << "DEL <key> | ( Discards key-value pair. )" << endl;
                cout << "EXISTS <key> | ( Checks if a key exists. )" << endl;
                cout << "TTL <key> | ( Returns the remaining time. )" << endl;
                cout << "EXPIRE <key> EX <seconds> | ( Update TTL for an existing key. )" << endl;
                cout << "PERSIST <key> | ( Removes the TTL of a key & sets TTL = 0 )" << endl;
                cout << "EXIT" << endl;
                cout << "-------------------------" << endl << endl;
            }
            else if (command_str == "SET")
            {
                command::handleSET(db, args);
            }
            else if (command_str == "GET")
            {
                command::handleGET(db, args);
            }
            else if (command_str == "DEL")
            {
                command::handleDEL(db, args);
            }
            else if (command_str == "EXISTS")
            {
                command::handleEXISTS(db, args);
            }
            else if (command_str == "TTL")
            {
                command::handleTTL(db, args);
            }
            else if (command_str == "EXPIRE")
            {
                command::handleEXPIRE(db, args);
            }
            else if (command_str == "PERSIST")
            {
                command::handlePERSIST(db, args);
            }
            else
            {
                cout << "[X] Command not allowed: " << command_str <<  " | Type 'HELP' for list of commands." << endl;
            }

            cin.clear();
        }
    }
}