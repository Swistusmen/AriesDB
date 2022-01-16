#pragma once
#include "Tokenizer.h"
#include "Parser.h"

class Compiler{
    public:
        std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>>  compile(std::string& );
    private:
    Tokenizer tokenizer;
    Parser parser;
};