#include "Tokenizer.h"

std::vector<Grammar::Token> Tokenizer::tokenizeInputString(const std::string &inputString)
{
    auto words = splitLongStringIntoAWords(inputString);
    if(words.empty()){
        logger.log("Could not tokenize command, there are no tokens",0);
        return{};
    }
    return convertWordsIntoTokens(words);
}

std::vector<std::string> Tokenizer::splitLongStringIntoAWords(std::string inputStr)
{
    std::vector<std::string> words;
    std::string buffer;

    for(const auto& letter: inputStr){
        
        if(letter != Delimiters::DELIMITER_1 && letter!=Delimiters::DELIMITER_2 ){
            if(letter!='=' &&letter!= '<' &&letter!='>'){
                buffer+=letter;
            }else{
                if(!buffer.empty()){
                words.push_back(buffer);
                buffer="";
                }
                words.push_back(std::string{letter});
            }
        }else{
            if(buffer!=""){
            words.push_back(buffer);
            }
            buffer="";
        }
    }
    if(buffer!="")
        words.push_back(buffer);
    return words;
}

std::vector<Grammar::Token> Tokenizer::convertWordsIntoTokens(const std::vector<std::string>& words)
{
    std::vector<Grammar::Token> tokens;
    const int noWords=words.size();
    for(int i=0;i<noWords;i++){
        Grammar::Token t;
        t.expr=words[i];
        t.number=i;
        t.lexem=Grammar::identifyLexem(words[i]);
        tokens.push_back(t);
    }
    return tokens;
}
