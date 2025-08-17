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

#include <string>
#include <chrono>
#include <stdexcept>
#include <limits>
#include <ostream>
#include <istream>
#include <optional>
#include "branchdb/db/response_metadata.h"

using namespace std;
using namespace chrono;

namespace branchdb
{
    // Serialization - Data -> Binary Stream
    void ResponseMetaData::to_binary(ostream &os) const
    {
        int32_t status_code_int = static_cast<int32_t>(status_code);
        os.write(reinterpret_cast<const char *>(&status_code_int), sizeof(status_code_int));

        uint8_t success_flag = success ? 1 : 0;
        os.write(reinterpret_cast<const char *>(&success_flag), sizeof(success_flag));

        uint32_t message_len = static_cast<uint32_t>(message.length());
        os.write(reinterpret_cast<const char *>(&message_len), sizeof(message_len));
        os.write(message.data(), message_len);

        uint8_t payload_type = static_cast<uint8_t>(res_data.index());
        os.write(reinterpret_cast<const char *>(&payload_type), sizeof(payload_type));

        if (holds_alternative<monostate>(res_data))
        {
            uint32_t payload_len = 0;
            os.write(reinterpret_cast<const char *>(&payload_len), sizeof(payload_len));
        }
        else if (holds_alternative<string>(res_data))
        {
            const string &payload_str = get<string>(res_data);
            uint32_t payload_len = static_cast<uint32_t>(payload_str.length());
            os.write(reinterpret_cast<const char *>(&payload_len), sizeof(payload_len));
            os.write(payload_str.data(), payload_len);
        }
        else if (holds_alternative<vector<string>>(res_data))
        {
            const vector<string> &payload_vector = get<vector<string>>(res_data);
            uint32_t payload_len = static_cast<uint32_t>(payload_vector.size());
            os.write(reinterpret_cast<const char *>(&payload_len), sizeof(payload_len));

            for (const string &s : payload_vector)
            {
                uint32_t string_len = static_cast<uint32_t>(s.length());
                os.write(reinterpret_cast<const char *>(&string_len), sizeof(string_len));
                os.write(s.data(), string_len);
            }
        }

        if (!os.good())
        {
            throw std::runtime_error("Error writing ResponseMetaData to binary stream.");
        }
    }
}