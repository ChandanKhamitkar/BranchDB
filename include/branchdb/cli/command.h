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
}

#endif