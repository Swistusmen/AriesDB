#include "gtest/gtest.h"
#include "../../source/SQLCommands/From.h"
#include "../Mocks/TableMocks.h"

TEST(From, One_correct_table_in_db){
    ShopTable shop;
    SQLCommand* where=new From;
    where->addArgument("Shops");
    auto res=where->execute(shop.tab);

    EXPECT_EQ(res,shop.tab);
}

TEST(From, One_incorrect_table_in_db){
    ShopTable shop;
    SQLCommand* where=new From;
    where->addArgument("Tanks");
    auto res=where->execute(shop.tab);

    EXPECT_EQ(res,nullptr);
}