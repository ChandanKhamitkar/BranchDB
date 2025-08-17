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
#include <iostream>
#include <random>
#include <sstream>

using namespace std;

namespace branchdb
{
    // Load Auth Tokens
    void Database::load_auth_tokens_from_file()
    {
        ifstream file(AUTH_FILE_NAME);
        if (!file.is_open())
        {
            cerr << "[AUTH] WARNING: '" << "' not found. No auth tokens will be loaded." << endl;
            return;
        }

        string line;
        while (getline(file, line))
        {
            size_t delimPos = line.find(':');
            if (delimPos == string::npos)
                continue;

            string username = line.substr(0, delimPos);
            string token = line.substr(delimPos + 1);

            username_to_token_[username] = token;
            token_to_username_[token] = username;
        }
        file.close();
    }

    // Generates a new hex token
    string Database::generate_new_auth_token()
    {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> distrib(0, 255);

        stringstream ss;
        ss << hex;
        for (int i = 0; i < 32; ++i)
        {
            int val = distrib(gen);
            if (val < 16)
            {
                ss << "0";
            }
            ss << val;
        }
        return ss.str();
    }

    // Returns stored token based on username input
    string Database::get_stored_token(const string &username)
    {
        auto it = username_to_token_.find(username);
        if (it != username_to_token_.end())
        {
            return it->second;
        }
        return "";
    }

    // Stores token to hash map.
    void Database::add_auth_token(const string &username, const string &token)
    {
        username_to_token_[username] = token;
        token_to_username_[token] = username;
        ofstream file(AUTH_FILE_NAME, ios::app);
        if (file.is_open())
        {
            file << username << ":" << token << endl;
            file.close();
        }
    }

    // New token validation
    bool Database::is_valid_auth_token(const string &token) const
    {
        return token_to_username_.find(token) != token_to_username_.end();
    }

    // Check if username exists
    bool Database::username_exists(const string &username) const
    {
        return username_to_token_.find(username) != username_to_token_.end();
    }

}