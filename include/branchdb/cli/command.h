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

#ifndef BRANCHDB_COMMAND_H
#define BRANCHDB_COMMAND_H

#include <branchdb/db/database.h>
#include <vector>
#include <string>

namespace command
{
    void handleSET(branchdb::Database &db, vector<string> &args);
    void handleGET(branchdb::Database &db, vector<string> &args);
    void handleDEL(branchdb::Database &db, vector<string> &args);
    void handleEXISTS(branchdb::Database &db, vector<string> &args);
    void handleTTL(branchdb::Database &db, vector<string> &args);
    void handleEXPIRE(branchdb::Database &db, vector<string> &args);
    void handlePERSIST(branchdb::Database &db, vector<string> &args);
    void handleGET_ALL(branchdb::Database &db, vector<string> &args);
    void handleFLUSH(branchdb::Database &db, vector<string> &args);
    void handleINFO(branchdb::Database &db, vector<string> &args);
    void handleHELP(vector<string> &args);
}

#endif