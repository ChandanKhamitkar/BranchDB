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

#ifndef BRANCHDB_RESPONSE_METADATA_H
#define BRANCHDB_RESPONSE_METADATA_H

#include <string>
#include <optional>
#include <variant>
#include <vector>

using namespace std;
namespace branchdb
{

    using PayloadTypes = variant<
        monostate,
        string,
        vector<string>
    >;

    struct ResponseMetaData
    {
        size_t status_code;
        bool success;
        string message;
        PayloadTypes res_data;

        // initialize constructor
        ResponseMetaData(const size_t &status_code, bool success,
                         const string &message = "", PayloadTypes res_data = monostate{})
            : status_code(status_code), success(success), message(message), res_data(res_data) {}

        // Default Constructor
        ResponseMetaData() = default;

        // Serialization - Data -> Binary Stream
        void to_binary(ostream &os) const;
    };
    inline ResponseMetaData make_response(
        size_t status_code,
        bool success,
        const string &message,
        PayloadTypes res_data)
    {
        return ResponseMetaData(status_code, success, message, res_data);
    }
}
#endif