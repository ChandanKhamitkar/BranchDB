#include "branchdb/helper/enum_parser.h"
#include <iostream>
#include <unordered_map>
#include <string>
#include <optional>

using namespace std;

namespace helper
{
    unordered_map<CommandEnums, string> command_enum_map = {
        {EXIT, "EXIT"},
        {TEST, "TEST"},
        {HELP, "HELP"},
        {SET, "SET"},
        {GET, "GET"},
        {DEL, "DEL"},
        {EXISTS, "EXISTS"},
        {TTL, "TTL"},
        {EXPIRE, "EXPIRE"},
        {PERSIST, "PERSIST"},
        {GETALL, "GETALL"},
        {FLUSH, "FLUSH"},
        {INFO, "INFO"},
    };
    unordered_map<string, CommandEnums> string_command_map = {
        {"EXIT", EXIT},
        {"TEST", TEST},
        {"HELP", HELP},
        {"SET", SET},
        {"GET", GET},
        {"DEL", DEL},
        {"EXISTS", EXISTS},
        {"TTL", TTL},
        {"EXPIRE", EXPIRE},
        {"PERSIST", PERSIST},
        {"GETALL", GETALL},
        {"FLUSH", FLUSH},
        {"INFO", INFO},
    };

    string CmdEnumToString(CommandEnums cmd)
    {
        return command_enum_map[cmd];
    }

    optional<CommandEnums> CmdStringToEnum(const string &cmdStr)
    {
        auto it = string_command_map.find(cmdStr);
        if (it != string_command_map.end())
        {
            return it->second;
        }
        return nullopt;
    }

}