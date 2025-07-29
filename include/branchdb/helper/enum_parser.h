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