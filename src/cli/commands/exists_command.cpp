#include <iostream>
#include <branchdb/db/database.h>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleEXISTS(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                db.exists(key);
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid EXISTS command format: Too many arguments passed!, Usage: EXISTS <key>" << endl;
            }
        }
        else
        {
            cout << "ERROR: EXISTS command atleast requires <key>, Usage: EXISTS <key>" << endl;
        }
    }
}