#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <optional>
#include "../Logger/Logger.h"
#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/SQLCommandCreator.h"
#include "PreCompiledFunctions.h"
#include "Grammar.h"
#include <functional>

class Parser{
    public:
    Parser(Logger& _logger):logger(_logger){}
        std::vector<std::unique_ptr<SQLCommand>> convertTokensIntoCommands(std::vector<Grammar::Token>& tokens);

        void sortCommands(
            std::vector<std::unique_ptr<SQLCommand>>& commands);
    private:
        Logger& logger;
        SQLCommandCreator sqlCreator;
        void precompileTokens(std::vector<Grammar::Token>& tokens);
        std::optional<std::function<void(std::vector<Grammar::Token>&,Logger&)>>  isPrecompileTime(const Grammar::Token& token);
        std::vector<std::unique_ptr<SQLCommand>> initializeSqlCommands(std::vector<Grammar::Token>& tokens);
};