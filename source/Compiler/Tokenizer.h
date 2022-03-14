#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <optional>

#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/SQLCommandCreator.h"

namespace Delimiters
{
    constexpr char DELIMITER_1 = ' ';
    constexpr char DELIMITER_2 =',';
    const std::string UNWANTED = "";
    constexpr int DELIMITER_SIZE = 1;
}

class Tokenizer
{
public:
    std::vector<std::unique_ptr<SQLCommand>> tokenizeInputString(const std::string &inputStr);

private:
    std::vector<std::string> splitLongStringIntoAWords(std::string inputStr);
    std::vector<std::unique_ptr<SQLCommand>> initializeSQLCommands(std::vector<std::string> &words);
    SQLCommandCreator sqlCreator;
};
