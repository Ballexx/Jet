#include "utils/common.hpp"

#include <algorithm>
#include <fstream>
#include <sstream>

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

std::string read_file(std::string path){
    std::ifstream file(path);

    if (file) {
        std::stringstream buffer;
        buffer << file.rdbuf();
        std::string content = buffer.str();
        return content;
    }
    else{
        std::cerr << "Failed to open file.\n";
    }
}