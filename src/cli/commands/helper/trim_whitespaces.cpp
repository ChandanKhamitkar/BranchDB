#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

namespace helper
{
    void trim_whitespace(string &str)
    {
        // Remove leading whitespace
        str.erase(str.begin(), find_if(str.begin(), str.end(), [](unsigned char ch) { return !isspace(ch); }));
    
        // Remove trailing whitespace
        str.erase(find_if(str.rbegin(), str.rend(), [](unsigned char ch) { return !isspace(ch); }).base(), str.end());
    }
} // namespace helper
