#include "PreCompiledFunctions.h"

void preCreate::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    tokens.erase(tokens.begin()+1); //create table ( ) -deleting table
    for(int i=0;i<tokens.size();i++){
        tokens[i].number=i;
    }
}

void preDelete::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    tokens.erase(std::remove_if(tokens.begin(),tokens.end(),[](auto& t){
        return t.lexem==Grammar::Lexem::Command && t.expr!="delete";
    }));
    tokens.erase(tokens.begin()+(tokens.size()-1));
    for(int i=0;i<tokens.size();i++){
        tokens[i].number=i;
    }
}

void preUpdate::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    bool isCounting{true};
    int noArguments{0};
    int index=token.number+1;
    while(index<tokens.size()){
        if(tokens[index].lexem==Grammar::Lexem::Command){
            if(tokens[index].expr=="set"){
                tokens.erase(tokens.begin()+index);
                continue;
            }else if(tokens[index].expr=="where"){
                tokens.erase(tokens.begin()+index);
                isCounting=false;
                continue;
            }else{
                logger.log("Syntax error: additional command in update: "+tokens[index].expr,0);
                return;
            }
        }
        if(isCounting){
            noArguments++;
            index++;
        }else{
            break;
        }
    }
    Grammar::Token noArgs;
    noArgs.expr=std::to_string(noArguments);
    noArgs.lexem=Grammar::Lexem::Argument;
    tokens.insert(tokens.begin()+token.number+1,noArgs);
    for(int i=0;i<tokens.size();i++){
        tokens[i].number=i;
    }
}

void preValues::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    const int currentIndex=token.number;
    auto toAdd=std::find_if(tokens.begin(),tokens.begin()+currentIndex,[this](auto token){
        return token.expr=="into";
    });

    if(toAdd==tokens.begin()+currentIndex){
        logger.log("Syntax error: missing into",0);
        return;
    }
    const int toAddIndex=toAdd-tokens.begin();

    std::vector<Grammar::Token> toCarry;
    tokens.erase(tokens.begin()+currentIndex); 
    
    while(tokens[currentIndex].lexem==Grammar::Lexem::Argument&& currentIndex<tokens.size()){
        toCarry.emplace_back(tokens[currentIndex]);
        tokens.erase(tokens.begin()+currentIndex); 
    }
    
    if(toCarry.empty()){
        logger.log("Syntax error: there are no arguments after values",0);
        return;
    }
    const int shift=currentIndex-toAddIndex;
    tokens.insert(tokens.begin()+shift,toCarry.begin(),toCarry.end());
    const int noTokens=tokens.size();
    for(int i=0;i<noTokens;i++){
        tokens[i].number=i;
    }
}

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

void preInsert::operator()(std::vector<Grammar::Token>& tokens,Logger& logger)
{
    const int indexToDelete=token.number;
    tokens.erase(tokens.begin()+indexToDelete);
    const int noTokens=tokens.size();
    for(int i=0;i<noTokens;i++){
        tokens[i].number=i;
    }
}