#include <iostream>
#include <branchdb/db/database.h>
#include <vector>

using namespace std;
using namespace chrono;

namespace command
{
    void handleINFO(branchdb::Database &db, vector<string> &args)
    {
        if (args.size() == 0)
        {
            db.info();
        }
        else
        {
            cout << "ERROR: Invalid INFO command usage, Valid Usage: INFO" << endl;
        }
    }
}