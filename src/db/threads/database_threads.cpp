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

#include "branchdb/db/database.h"
#include <mutex>

namespace branchdb
{
    // TTL Cleanup
    void Database::ttl_cleanup_loop()
    {
        while (!stop_ttl_cleanup_)
        {
            this_thread::sleep_for(TTL_SCAN_INTERVAL_);
            if (stop_ttl_cleanup_)
                break;

            vector<pair<string, string>> keys_to_delete;

            // acquire Read lock by 'shared_lock' - allows multiple readers or single writer
            {
                shared_lock<shared_mutex> lock(data_mutex_);
                for (const auto &outer_pair : data_)
                {
                    for (const auto &inner_pair : outer_pair.second)
                    {
                        if (inner_pair.second.is_expired())
                        {
                            keys_to_delete.push_back({outer_pair.first, inner_pair.first});
                        }
                    }
                }
            } // Release Read lock

            // acquire Write lock by 'unique_lock'
            if (!keys_to_delete.empty())
            {
                unique_lock<shared_mutex> lock(data_mutex_);
                for (const auto &[auth_key, key] : keys_to_delete)
                {
                    internal_del(auth_key, key);
                }

                // Deallocate occupied space
                keys_to_delete.clear();
                keys_to_delete.shrink_to_fit();
            }
        }
    }

} // namespace branchdb
