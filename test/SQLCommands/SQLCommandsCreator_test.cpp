#include "gtest/gtest.h"
#include "../../source/SQLCommands/SQLCommandCreator.h"
#include "../../source/SQLCommands/SQLCommandCreator.cpp"
#include "../../source/SQLCommands/From.h"
#include "../../source/SQLCommands/Select.h"
#include "../../source/SQLCommands/Where.h"
#include "../../source/SQLCommands/On.cpp"


#include "../../source/SQLCommands/Update.cpp"

#include "../../source/SQLCommands/Create.cpp"
#include "../../source/SQLCommands/Delete.cpp"

#include <optional>

TEST(SQL_COMMAND_CREATOR,CREATE_FROM){
    std::string testValue="from";
    SQLCommandCreator creator;
    auto res=creator.createACommand(testValue);
    ASSERT_EQ(true, res.has_value());
}
