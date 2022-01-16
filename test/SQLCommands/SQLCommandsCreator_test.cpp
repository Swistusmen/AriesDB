#include "gtest/gtest.h"
#include "../../source/SQLCommands/SQLCommandCreator.h"
#include "../../source/SQLCommands/SQLCommandCreator.cpp"
#include "../../source/SQLCommands/From.h"
#include "../../source/SQLCommands/Select.h"
#include "../../source/SQLCommands/Where.h"

TEST(SQL_COMMAND_CREATOR,CREATE_FROM){
    std::string testValue="from";
    SQLCommandCreator creator;
    auto res=creator.createACommand(testValue);
    ASSERT_EQ(true, res.has_value());
}

