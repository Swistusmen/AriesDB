#include "gtest/gtest.h"

#include "../../source/SQLCommands/From.h"

#include "../../source/SQLCommands/Where.cpp"
#include "../../source/SQLCommands/Select.cpp"

#include "../../source/Compiler/Parser.cpp"

#include <vector>

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_1){
    auto res=std::make_unique<std::vector<std::unique_ptr<SQLCommand>>>();
    res->push_back(std::make_unique<From>());
    res->push_back(std::make_unique<From>());
    res->push_back(std::make_unique<Select>());
    res->push_back(std::make_unique<From>());
    res->push_back(std::make_unique<Where>());
    Parser parser;
    res=parser.sortCommands(std::move(res));
    const int noSQL=res->size();
    std::vector<int>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res->at(i)->getValidity());
    }
    std::vector<int> expected{1,1,1,2,3};
    ASSERT_EQ(expected, validity);
}

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_2){
    auto res=std::make_unique<std::vector<std::unique_ptr<SQLCommand>>>();
    res->push_back(std::make_unique<Select>());
    res->push_back(std::make_unique<Where>());
    res->push_back(std::make_unique<Select>());
    res->push_back(std::make_unique<From>());
    res->push_back(std::make_unique<Where>());
    Parser parser;
    res=parser.sortCommands(std::move(res));
    const int noSQL=res->size();
    std::vector<int>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res->at(i)->getValidity());
    }
    std::vector<int> expected{1,2,2,3,3};
    ASSERT_EQ(expected, validity);
}

TEST(PARSER,SORT_FROM_SELECT_WHERE_CORRECTLY_3){
    auto res=std::make_unique<std::vector<std::unique_ptr<SQLCommand>>>();
    res->push_back(std::make_unique<Select>());
    res->push_back(std::make_unique<From>());
    res->push_back(std::make_unique<Where>());
    Parser parser;
    res=parser.sortCommands(std::move(res));
    const int noSQL=res->size();
    std::vector<int>  validity;
    for(int i=0;i<noSQL;i++){
        validity.push_back(res->at(i)->getValidity());
    }
    std::vector<int> expected{1,2,3};
    ASSERT_EQ(expected, validity);
}
