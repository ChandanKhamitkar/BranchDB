#include <branchdb/db/database.h>
#include <branchdb/cli/start_cli.h>

using namespace std;
using namespace chrono;

int main()
{
    branchdb::Database db;
    cli::startCLI(db);
    return 0;
}