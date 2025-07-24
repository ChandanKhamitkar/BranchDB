#include <iostream>
#include <branchdb/db/database.h>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleTTL(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() >= 1)
        {
            string key = args[0];

            if (args.size() == 1)
            {
                db.ttl(key);
            }
            else if (args.size() > 1)
            {
                cout << "ERROR: Invalid TTL command format: Too many arguments passed!, Usage: TTL <key>" << endl;
            }
        }
        else
        {
            cout << "ERROR: TTL command atleast requires <key>, Usage: TTL <key>" << endl;
        }
    }
}