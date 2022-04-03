#include "Compiler.h"

std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType> Compiler::compile(std::string &inputString)
{
    auto tokens = tokenizer.tokenizeInputString(inputString);
    return {parser.convertTokensIntoCommands(tokens),Commands::ExecutionType::READONLY};
}