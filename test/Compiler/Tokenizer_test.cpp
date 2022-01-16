#include "gtest/gtest.h"
#include "../../source/Compiler/Tokenizer.h"
#include "../../source/Compiler/Tokenizer.cpp"

#include <typeinfo>
#include <optional>

TEST(TOKENIZER,CREATE_FROM){
    std::string testValue="from";
    Tokenizer tokenizer;
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(1, res->size());
}

TEST(TOKENIZER,CREATE_FROM_WITH_ARGUMENTS){
    std::string testValue="from x x";
    Tokenizer tokenizer;
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(1, res->size());
}

TEST(TOKENIZER,CREATE_FROM_WITH_ARGUMENTS_CHECK_NO_ARGUMENTS){
    std::string testValue="from x xa";
    Tokenizer tokenizer;
    auto res=tokenizer.tokenizeInputString(testValue);
    auto val=std::move(res->at(0));
    ASSERT_EQ(2, val->getArguments().size());
}
