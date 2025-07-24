#include <iostream>
#include <branchdb/db/database.h>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleDEL(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                db.del(key);
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid DEL command format: Too many arguments passed!, Usage: DEL <key>" << endl;
            }
        }
        else
        {
            cout << "ERROR: DEL command atleast requires <key>, Usage: DEL <key>" << endl;
        }
    }
}