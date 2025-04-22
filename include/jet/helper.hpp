#pragma once
#include <vector>
#include <string>
std::vector<std::string> split(const std::string& s, const std::string& delimiter);
std::string str_to_lower(std::string str);
std::string str_to_upper(std::string str);
bool is_method_valid(std::string method);