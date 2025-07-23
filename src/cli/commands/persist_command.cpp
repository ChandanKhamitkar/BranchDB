#include <iostream>
#include <branchdb/database.h>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handlePERSIST(branchdb::Database& db, vector<string>& args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                db.persist(key);
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid PERSIST command format: Too many arguments passed!, Usage: PERSIST <key>" << endl;
            }
        }
        else
        {
            cout << "ERROR: PERSIST command atleast requires <key>, Usage: PERSIST <key>" << endl;
        }
    }
}