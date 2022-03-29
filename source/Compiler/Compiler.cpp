#include "Compiler.h"

std::vector<std::unique_ptr<SQLCommand>> Compiler::compile(std::string &inputString)
{
    auto tokens = tokenizer.tokenizeInputString(inputString);
    return parser.convertTokensIntoCommands(tokens);
}