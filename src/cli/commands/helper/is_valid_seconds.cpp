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

#include <iostream>
#include <string>

using namespace std;

namespace helper
{
    long long is_valid_seconds(const string &s)
    {
        try
        {
            return stoll(s);
        }
        catch (const std::exception &e)
        {
            return -1;
        }
    }
} // namespace helper
