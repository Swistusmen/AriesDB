#include "Tokenizer.h"

std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> Tokenizer::tokenizeInputString(std::string &inputString)
{
    auto words = splitLongStringIntoAWords(inputString);
    auto commands = initializeSQLCommands(words);
    return std::move(commands);
}

std::vector<std::string> Tokenizer::splitLongStringIntoAWords(std::string inputStr)
{
    std::vector<std::string> words;
    std::string buffer;

    for(auto letter: inputStr){
        if(letter != DELIMITER && letter!=',' ){
            buffer+=letter;
        }else{
            words.push_back(buffer);
            buffer="";
        }
    }
    if(buffer!="")
        words.push_back(buffer);
    return std::move(words);
}

std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> Tokenizer::initializeSQLCommands(std::vector<std::string> &words)
{
    int noWords = words.size();
    auto commands=std::make_unique<std::vector<std::unique_ptr<SQLCommand>>>();
    for (int i = 0; i < noWords; i++)
    {
        auto respond=sqlCreator.createACommand(words[i]);
        if(respond.has_value()){
            commands->push_back(std::move(respond.value()));
        }else{
            words[i]=="*"? commands->pop_back() :  commands->back()->addArgument(words[i]);
        }
    }
    return commands;
}