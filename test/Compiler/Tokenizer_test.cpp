#include "gtest/gtest.h"
#include "../../source/Compiler/Tokenizer.h"
#include "../../source/Compiler/Tokenizer.cpp"
#include "../../source/Logger/Logger.h"

#include <typeinfo>
#include <optional>

TEST(TOKENIZER,CREATE_FROM){
    std::string testValue="from";
    Logger logger("",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(1, res.size());
}

TEST(TOKENIZER,CREATE_FROM_WITH_ARGUMENTS){
    std::string testValue="from x x";
    Logger logger("",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(1, res.size());
}

TEST(TOKENIZER,CREATE_FROM_WITH_ARGUMENTS_CHECK_NO_ARGUMENTS){
    std::string testValue="from x xa";
    Logger logger("",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    auto val=std::move(res.at(0));
    ASSERT_EQ(2, val->getArguments().size());
}
