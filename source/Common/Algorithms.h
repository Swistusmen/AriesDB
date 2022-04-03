#pragma once
#include <string>
#include <vector>
#include <algorithm>

std::array<std::string,2> getTableNameAndColumnNameFromArgument(const std::string& argument);

std::vector<std::string> splitString(const std::string& arg,char splitter);