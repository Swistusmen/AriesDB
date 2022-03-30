#include "gtest/gtest.h"

#include "../../source/SQLCommands/From.h"

#include "../../source/SQLCommands/Where.cpp"
#include "../../source/SQLCommands/Select.cpp"

#include "../../source/Compiler/Parser.cpp"
#include "../../source/Compiler/PreCompiledFunctions.h"
#include "../../source/Compiler/PreCompiledFunctions.cpp"
#include "../../source/Compiler/Tokenizer.h"

#include <vector>

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_1){
    std::vector<std::unique_ptr<SQLCommand>> res;
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<Select>());
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<Where>());
    Logger logger ("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Parser parser(logger);
    parser.sortCommands(res);
    const int noSQL=res.size();
    std::vector<SQL::Code>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res.at(i)->getPriority());
    }
    std::vector<SQL::Code> expected{SQL::Code::FROM,SQL::Code::FROM,SQL::Code::FROM,SQL::Code::WHERE,SQL::Code::SELECT};
    ASSERT_EQ(expected, validity);
}

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_2){
    std::vector<std::unique_ptr<SQLCommand>> res;
    res.push_back(std::make_unique<Select>());
    res.push_back(std::make_unique<Where>());
    res.push_back(std::make_unique<Select>());
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<Where>());
    Logger logger ("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Parser parser(logger);
    parser.sortCommands(res);
    const int noSQL=res.size();
    std::vector<SQL::Code>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res.at(i)->getPriority());
    }
    std::vector<SQL::Code> expected{SQL::Code::FROM,SQL::Code::WHERE,SQL::Code::WHERE,SQL::Code::SELECT,SQL::Code::SELECT};
    ASSERT_EQ(expected, validity);
}

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_3){
    std::vector<std::unique_ptr<SQLCommand>> res;
    res.push_back(std::make_unique<Select>());
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<Where>());
    Logger logger ("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Parser parser(logger);
    parser.sortCommands(res);
    const int noSQL=res.size();
    std::vector<SQL::Code>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res.at(i)->getPriority());
    }
    std::vector<SQL::Code> expected{SQL::Code::FROM,SQL::Code::WHERE,SQL::Code::SELECT};
    ASSERT_EQ(expected, validity);
}
/*
Klasa testowa
1. dopisanie testów konwersji tokenów na komendy i sprawdzenie ich  
*/

class Parser_Suite :public ::testing::Test{
    public:
        Parser_Suite():logger("/home/michal/Documents/Programming/Database/Logs/test.txt",1),tokenizer(logger),parser(logger){}

    protected:
    Logger logger;
    Tokenizer tokenizer;
    Parser parser;
};
//compiler test
TEST_F(Parser_Suite,SIMPLE_SELECT){
    std::string input{"select * from shops"};
    auto tokens=tokenizer.tokenizeInputString(input);
    auto output=parser.convertTokensIntoCommands(tokens);
    ASSERT_EQ(output.size(),1);
}

TEST_F(Parser_Suite,SELECT_ALL_FROM_PARSE){
    Grammar::Token t1;
    t1.expr="from";
    t1.lexem=Grammar::Lexem::Command;
    t1.number=0;

    Grammar::Token t2;
    t2.expr="dupa";
    t2.lexem=Grammar::Lexem::Argument;
    t2.number=1;
    std::vector<Grammar::Token> tokens{t1,t2};
    auto commands=parser.convertTokensIntoCommands(tokens);
    ASSERT_EQ(commands.size(),1);
}

TEST_F(Parser_Suite,SELECT_ALL_FROM_TWO_TABLES_PARSE){
    Grammar::Token t1;
    t1.expr="from";
    t1.lexem=Grammar::Lexem::Command;
    t1.number=0;

    Grammar::Token t2;
    t2.expr="dupa";
    t2.lexem=Grammar::Lexem::Argument;
    t2.number=2;

    Grammar::Token t3;
    t3.expr="dupa1";
    t3.lexem=Grammar::Lexem::Argument;
    t3.number=3;
    std::vector<Grammar::Token> tokens{t1,t2,t3};
    auto commands=parser.convertTokensIntoCommands(tokens);
    ASSERT_EQ(commands.size(),1);
}

TEST_F(Parser_Suite,SELECT_SOME_FROM_TABLE_PARSE){
    Grammar::Token t1;
    t1.expr="select";
    t1.lexem=Grammar::Lexem::Command;
    t1.number=0;

    Grammar::Token t2;
    t2.expr="id";
    t2.lexem=Grammar::Lexem::Argument;
    t2.number=1;

    Grammar::Token t3;
    t3.expr="from";
    t3.lexem=Grammar::Lexem::Command;
    t3.number=2;

    Grammar::Token t4;
    t4.expr="dupa";
    t4.lexem=Grammar::Lexem::Argument;
    t4.number=3;

    Grammar::Token t5;
    t5.expr="dupa1";
    t5.lexem=Grammar::Lexem::Argument;
    t5.number=4;
    std::vector<Grammar::Token> tokens{t1,t2,t3,t4,t5};
    auto commands=parser.convertTokensIntoCommands(tokens);
    ASSERT_EQ(commands.size(),2);
}

TEST_F(Parser_Suite,SELECT_SOME_FROM_TABLE_ORDER_PARSE){
    Grammar::Token t1;
    t1.expr="select";
    t1.lexem=Grammar::Lexem::Command;
    t1.number=0;

    Grammar::Token t2;
    t2.expr="id";
    t2.lexem=Grammar::Lexem::Argument;
    t2.number=1;

    Grammar::Token t3;
    t3.expr="from";
    t3.lexem=Grammar::Lexem::Command;
    t3.number=2;

    Grammar::Token t4;
    t4.expr="dupa";
    t4.lexem=Grammar::Lexem::Argument;
    t4.number=3;

    Grammar::Token t5;
    t5.expr="dupa1";
    t5.lexem=Grammar::Lexem::Argument;
    t5.number=4;
    std::vector<Grammar::Token> tokens{t1,t2,t3,t4,t5};
    auto commands=parser.convertTokensIntoCommands(tokens);
    ASSERT_EQ(commands[0]->getPriority(),SQL::Code::FROM);
}

TEST_F(Parser_Suite,FROM_TABLE_WHERE_PARSE){

    Grammar::Token t1;
    t1.expr="from";
    t1.lexem=Grammar::Lexem::Command;
    t1.number=2;

    Grammar::Token t2;
    t2.expr="dupa";
    t2.lexem=Grammar::Lexem::Argument;
    t2.number=3;

    Grammar::Token t3;
    t3.expr="where";
    t3.lexem=Grammar::Lexem::Command;
    t3.number=4;

    Grammar::Token t4;
    t4.expr="id";
    t4.lexem=Grammar::Lexem::Argument;
    t4.number=3;

    Grammar::Token t5;
    t5.expr="=";
    t5.lexem=Grammar::Lexem::Argument;
    t5.number=3;

    Grammar::Token t6;
    t6.expr="9";
    t6.lexem=Grammar::Lexem::Argument;
    t6.number=3;

    std::vector<Grammar::Token> tokens{t1,t2,t3,t4,t5,t6};
    auto commands=parser.convertTokensIntoCommands(tokens);
    ASSERT_EQ(commands.size(),2);
}

