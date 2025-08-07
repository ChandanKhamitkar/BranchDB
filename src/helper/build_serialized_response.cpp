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
#include <sstream>
#include <branchdb/db/response_metadata.h>

using namespace std;

namespace helper
{
    string build_serialized_response(branchdb::ResponseMetaData &response_obj)
    {
        stringstream ss;
        response_obj.to_binary(ss);
        string serialized_response = ss.str();
        serialized_response += '\n';
        return serialized_response;
    }
} // namespace helper
