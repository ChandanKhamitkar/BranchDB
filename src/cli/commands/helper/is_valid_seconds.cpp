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
