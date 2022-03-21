#pragma once
#include "Tokenizer.h"
#include "Parser.h"

class Compiler
{
public:
    Compiler(Logger& _logger):tokenizer(_logger){};
    std::vector<std::unique_ptr<SQLCommand>> compile(std::string &);

private:
    Tokenizer tokenizer;
    Parser parser;
};