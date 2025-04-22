#include "utils/common.hpp"

#include <algorithm>

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    std::string str = s;
    size_t pos = 0;
    std::string token;

    while ((pos = str.find(delimiter)) != std::string::npos) {
        token = str.substr(0, pos);
        tokens.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    tokens.push_back(str);

    return tokens;
}

std::string str_to_lower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

std::string str_to_upper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

bool is_method_valid(std::string method) {
    method = str_to_upper(method);

    static std::string methods[9] = {
        "GET", "HEAD", "POST", "PUT", "DELETE",
        "CONNECT", "OPTIONS", "TRACE", "PATCH"
    };

    for (int i = 0; i < 9; ++i) {
        if (method == methods[i]) {
            return true;
        }
    }
    return false;
}