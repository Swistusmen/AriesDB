#include "gtest/gtest.h"
#include "../../source/Compiler/Tokenizer.h"
#include "../../source/Compiler/Tokenizer.cpp"
#include "../../source/Logger/Logger.h"

#include <typeinfo>
#include <optional>

TEST(TOKENIZER,CREATE_FROM){
    std::string testValue="from";
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(1, res.size());
}

TEST(TOKENIZER,CREATE_FROM_WITH_ARGUMENTS){
    std::string testValue="from x x";
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(1, res.size());
}

TEST(TOKENIZER,CREATE_FROM_WITH_ARGUMENTS_CHECK_NO_ARGUMENTS){
    std::string testValue="from x xa";
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    auto val=std::move(res.at(0));
    ASSERT_EQ(2, val->getArguments().size());
}

TEST(TOKENIZER,CREATE_MULTIPLE_THE_SAME_COMMANDS){
    std::string testValue="from x xa from x xa";
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(2, res.size());
}

TEST(TOKENIZER,JOIN_INSIDE_JOIN){
    std::string testValue="select * from shops join workers on shops.id = workers.workers_id join products on workers.worker_id = products.product_id";
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(3, res.size());
}

TEST(TOKENIZER,JOIN_INSIDE_JOIN_2){
    std::string testValue="from shops join workers on shops.id = workers.workers_id join products on workers.worker_id = products.product_id";
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    Tokenizer tokenizer(logger);
    auto res=tokenizer.tokenizeInputString(testValue);
    ASSERT_EQ(3, res.size());
}

