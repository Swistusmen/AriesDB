#pragma once
#include "Tokenizer.h"
#include "Parser.h"
#include "../SQLCommands/ExecutionType.h"

//responsible for semantic analysis

class Compiler
{
public:
    Compiler(Logger& _logger):tokenizer(_logger),parser(_logger){};
    std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType> compile(std::string &);

private:
    Tokenizer tokenizer;
    Parser parser;
};