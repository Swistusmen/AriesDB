#include "Compiler.h"

std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>>  Compiler::compile(std::string& inputString){
    auto tokens = tokenizer.tokenizeInputString(inputString);
    tokens = parser.sortCommands(std::move(tokens));
    return tokens;
}