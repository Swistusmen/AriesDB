#pragma once
#include "Tokenizer.h"
#include "Parser.h"
#include "../SQLCommands/ExecutionType.h"
#include "../SQLCommands/Commands.h"

//responsible for semantic analysis

class Compiler
{
public:
    Compiler(Logger& _logger):tokenizer(_logger),parser(_logger){};
    std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType> compile(std::string &);

private:
    Commands::ExecutionType deductExecutionType(const std::vector<std::unique_ptr<SQLCommand>>& _commands);
    commandToExecute&& pack(std::vector<std::unique_ptr<SQLCommand>>&& commands,const Commands::ExecutionType type);

    Tokenizer tokenizer;
    Parser parser;
};