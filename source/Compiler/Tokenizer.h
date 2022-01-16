#pragma once
#include <vector>
#include <memory>
#include <string>
#include <algorithm>
#include <optional>

#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/SQLCommandCreator.h"

#define DELIMITER ' '
#define DELIMITER_SIZE 1

class Tokenizer{
    public:
        std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> tokenizeInputString(std::string& inputStr);
    private:
        std::vector<std::string> splitLongStringIntoAWords(std::string inputStr);
        std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> initializeSQLCommands(std::vector<std::string>& words);
        SQLCommandCreator sqlCreator;
};
