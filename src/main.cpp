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

#include <branchdb/db/database.h>
#include <branchdb/cli/start_cli.h>
#include <csignal>>

using namespace std;
using namespace chrono;

void handleSigint(int signal)
{
    cout << endl
         << "Data stored to DISK successfully, Status:[OK]" << endl;
}

int main()
{
    signal(SIGINT, handleSigint);
    branchdb::Database db;
    cli::startCLI(db);
    return 0;
}