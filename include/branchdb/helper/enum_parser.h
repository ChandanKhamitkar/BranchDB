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

#ifndef BRANCH_DB_CMD_ENUM_PARSER
#define BRANCH_DB_CMD_ENUM_PARSER

#include <string>
#include <optional>
using namespace std;

namespace helper
{

    // ENUM for LIST OF COMMANDS
    enum CommandEnums
    {
        EXIT,
        TEST,
        HELP,
        SET,
        GET,
        DEL,
        EXISTS,
        TTL,
        EXPIRE,
        PERSIST,
        GETALL,
        FLUSH,
        INFO
    };

    string CmdEnumToString(CommandEnums cmd);
    optional<CommandEnums> CmdStringToEnum(const string &cmdStr);

} // namespace helper

#endif