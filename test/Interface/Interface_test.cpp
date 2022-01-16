#include "gtest/gtest.h"
#include "../../source/Interface/Interface.h"
#include <iostream>
#include <istream>

TEST(INTERFACE,GOOD_INPUT_GOOD_OUTPUT){
    std::stringstream stream;
    std::string testValue="Hello";
    stream>>testValue;
    std::string outputValue=takeInputFromKeyboard(stream);
    ASSERT_EQ(testValue,outputValue);
}