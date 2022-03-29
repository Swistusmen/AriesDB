#include "PreCompiledFunctions.h"

void preJoin::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    const int currentIndex=token.number;
    auto from=std::find_if(tokens.begin(),tokens.begin()+currentIndex,[](auto token){
        return token.expr=="from";
    });
    if(from==tokens.begin()+currentIndex){
        logger.log("Syntax error: missing from",0);
        return;
    }
    const int fromIndex=from-tokens.begin();

    std::vector<Grammar::Token> toCarry;
    tokens.erase(tokens.begin()+currentIndex); //deleting join
    
    while(tokens[currentIndex].lexem==Grammar::Lexem::Argument){
        toCarry.emplace_back(tokens[currentIndex]);
        tokens.erase(tokens.begin()+currentIndex); //arguments will be carried from after join to after from
    }
    
    if(toCarry.empty()){
        logger.log("Syntax error: there are no arguments after join",0);
        return;
    }
    
    tokens.insert(tokens.begin()+fromIndex+1,toCarry.begin(),toCarry.end());
    const int noTokens=tokens.size();
    for(int i=0;i<noTokens;i++){
        tokens[i].number=i;
    }
}

void preStar::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    const int currentIndex=token.number;
    tokens.erase(tokens.begin()+currentIndex);
    if(tokens[currentIndex-1].lexem!=Grammar::Lexem::Command){
        logger.log("Syntax error: before * has to be SQL command",0);
        return;
    }
    tokens.erase(tokens.begin()+currentIndex-1);
    const int noTokens=tokens.size();
    for(int i=0;i!=noTokens;i++){
        tokens[i].number=i;
    }
}