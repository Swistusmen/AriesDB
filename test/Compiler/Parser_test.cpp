#include "gtest/gtest.h"

#include "../../source/SQLCommands/From.h"

#include "../../source/SQLCommands/Where.cpp"
#include "../../source/SQLCommands/Select.cpp"

#include "../../source/Compiler/Parser.cpp"

#include <vector>

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_1){
    std::vector<std::unique_ptr<SQLCommand>> res;
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<Select>());
    res.push_back(std::make_unique<From>());
    res.push_back(std::make_unique<Where>());
    Parser parser;
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
    Parser parser;
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
    Parser parser;
    parser.sortCommands(res);
    const int noSQL=res.size();
    std::vector<SQL::Code>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res.at(i)->getPriority());
    }
    std::vector<SQL::Code> expected{SQL::Code::FROM,SQL::Code::WHERE,SQL::Code::SELECT};
    ASSERT_EQ(expected, validity);
}
