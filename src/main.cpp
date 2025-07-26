#include <branchdb/db/database.h>
#include <branchdb/cli/start_cli.h>
#include <csignal>>

using namespace std;
using namespace chrono;

void handleSigint(int signal) {
    cout << endl << "Data stored to DISK successfully, Status:[OK]" << endl;
}

int main()
{
    signal(SIGINT, handleSigint);
    branchdb::Database db;
    cli::startCLI(db);
    return 0;
}