#include "Parser.h"

std::vector<std::unique_ptr<SQLCommand>> Parser::convertTokensIntoCommands(std::vector<Grammar::Token>& tokens)
{
    //TODO: add nested expressions
    precompileTokens(tokens);
    auto commands=initializeSqlCommands(tokens);
    sortCommands(commands);
    return commands;
}

void Parser::precompileTokens(std::vector<Grammar::Token>& tokens)
{
    for(auto& token: tokens){
        auto fun=isPrecompileTime(token); 
        if(fun.has_value()){
            fun.value()(tokens,logger); 
        }
    }
}

std::optional<std::function<void(std::vector<Grammar::Token>&,Logger&)>>  Parser::isPrecompileTime(const Grammar::Token& token)
{
    if(token.lexem==Grammar::Lexem::Command&&token.expr=="join"){
        return preJoin(token);
    }else if(token.lexem==Grammar::Lexem::Command&&token.expr=="values"){
        return preValues(token);
    }else if(token.lexem==Grammar::Lexem::Command&&token.expr=="insert"){
        return preInsert(token);
    }else if(token.lexem==Grammar::Lexem::Command&&token.expr=="update"){
        return preUpdate(token);
    }else if(token.lexem==Grammar::Lexem::Command&&token.expr=="delete"){
        return preDelete(token);
    }else if(token.lexem==Grammar::Lexem::Control_sign){
        return preStar(token); 
    }
    return {};
}

 std::vector<std::unique_ptr<SQLCommand>> Parser::initializeSqlCommands(std::vector<Grammar::Token>& tokens)
 {
     const int noWords = tokens.size();
    std::vector<std::unique_ptr<SQLCommand>> commands;
    for (int i = 0; i < noWords; i++)
    {
        auto respond=sqlCreator.createACommand(tokens[i].expr);
        if(respond.has_value()){
            commands.push_back(std::move(respond.value()));
        }else{
            commands.back()->addArgument(tokens[i].expr);
        }
    }
    return commands;
 }

void Parser::sortCommands(
    std::vector<std::unique_ptr<SQLCommand>> &commands)
{
    std::sort(commands.begin(), commands.end(), [](const auto &a, const auto &b)
              { return a->getPriority() < b->getPriority(); });
}