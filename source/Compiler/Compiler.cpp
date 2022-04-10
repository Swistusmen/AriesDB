#include "Compiler.h"

std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType> Compiler::compile(std::string &inputString)
{
    auto tokens = tokenizer.tokenizeInputString(inputString);
    auto commands=parser.convertTokensIntoCommands(tokens);
    auto executionType=deductExecutionType(commands);
    return {std::move(commands),executionType};
}

Commands::ExecutionType Compiler::deductExecutionType(const std::vector<std::unique_ptr<SQLCommand>>& _commands)
{
    auto isModifyingContent=std::find_if(_commands.begin(),_commands.end(),[](const auto& ptr){
        return ptr->getPriority()==SQL::Code::INTO;
    });
    if(isModifyingContent!=_commands.end()){
        return Commands::ExecutionType::MODIFY_CONTENT;
    }
    return Commands::ExecutionType::READONLY;
}