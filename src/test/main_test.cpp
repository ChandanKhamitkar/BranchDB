#include <iostream>
#include <branchdb/database.h>
#include <thread>
#include <chrono>
#include <optional>

using namespace std;
using namespace chrono;

namespace test
{
    void testDB(branchdb::Database& db)
    {
        // Test SET key
        cout << "Running Tests on BranchDB using defined operations..." << endl;
        cout << "-------------------------" << endl;
        db.set("1", "Sidharth");
        db.set("20", "Chandan", seconds(3));
        optional<string> val = db.get("1");
        cout << endl;

        // Check for key that doesn't exists
        optional<string> val2 = db.get("2");
        cout << endl;

        // Process DEL
        db.set("3", "Trio here");
        db.del("3");
        cout << endl;

        // pause thread for 3 seconds
        cout << "Thread sleeping for 3 seconds." << endl;
        this_thread::sleep_for(seconds(3));
        cout << endl;

        // check if key EXISTS
        db.exists("1");
        db.exists("2");
        db.exists("20");
        cout << endl;

        // TTL
        db.ttl("1");
        db.ttl("20");
        cout << endl;

        // expire
        db.expire("20", seconds(40));
        cout << endl;

        // persists
        db.persist("20");
        cout << endl;
        cout << "-------------------------" << endl;
    }
}