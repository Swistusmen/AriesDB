#include "gtest/gtest.h"
#include "../../source/SQLCommands/FromCreator.h"
#include "../../source/SQLCommands/From.cpp"

TEST(FROM_CREATOR,FROM_DETECT_POSITIVE_SMALL_LETTERS){
    std::string testValue="from";
    FromCreator creator;
    auto res=creator.doesAWordRepresentSQLCommand(testValue);
    ASSERT_EQ(true, res);
}

TEST(FROM_CREATOR,FROM_DETECT_POSITIVE_BIG_LETTERS){
    std::string testValue="FROM";
    FromCreator creator;
    auto res=creator.doesAWordRepresentSQLCommand(testValue);
    ASSERT_EQ(true, res);
}

TEST(FROM_CREATOR,FROM_DETECT_POSITIVE_MIXED_LETTERS){
    std::string testValue="FrOM";
    FromCreator creator;
    auto res=creator.doesAWordRepresentSQLCommand(testValue);
    ASSERT_EQ(true, res);
}

TEST(FROM_CREATOR,FROM_DETECT_NEGATIVE){
    std::string testValue="select";
    FromCreator creator;
    auto res=creator.doesAWordRepresentSQLCommand(testValue);
    ASSERT_EQ(false, res);
}


