#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <optional>

#include "../SQLCommands/SQLCommand.h"
#include "../Logger/Logger.h"
#include "Grammar.h"

namespace Delimiters
{
    constexpr char DELIMITER_1 = ' ';
    constexpr char DELIMITER_2 =',';
    const std::string UNWANTED = "";
    constexpr int DELIMITER_SIZE = 1;
}

//responsible for lexical analysis

class Tokenizer
{
public:
    Tokenizer(Logger& _logger):logger(_logger){};
    std::vector<Grammar::Token> tokenizeInputString(const std::string &inputStr);

private:
    std::vector<std::string> splitLongStringIntoAWords(std::string inputStr);
    std::vector<Grammar::Token> convertWordsIntoTokens(const std::vector<std::string>& words);
    Logger& logger;
};
