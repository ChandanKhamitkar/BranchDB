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

#ifndef BRANCHDB_MAIN_TEST_H
#define BRANCHDB_MAIN_TEST_H

#include <branchdb/db/database.h>

namespace test
{
    void testDB(branchdb::Database &db);
}

#endif