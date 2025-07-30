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

#ifndef BRANCHDB_HELPER_H
#define BRANCHDB_HELPER_H

#include <string>

namespace helper
{
    long long is_valid_seconds(const string& s);
    void trim_whitespace(string &str);
} // namespace helper


#endif