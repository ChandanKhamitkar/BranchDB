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
#include <branchdb/db/response_metadata.h>
#include <vector>
#include <string>

namespace command
{
    branchdb::ResponseMetaData handleSET(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleGET(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleDEL(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleEXISTS(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleTTL(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleEXPIRE(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handlePERSIST(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleGET_ALL(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleFLUSH(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleINFO(branchdb::Database &db, vector<string> &args);
    branchdb::ResponseMetaData handleHELP(vector<string> &args);
}

#endif