#include "gtest/gtest.h"
#include "../../source/SQLCommands/From.cpp"
#include "../Mocks/TableMocks.h"

TEST(From, One_correct_table_in_db){
    ShopTable shop;
    SQLCommand* from=new From;
    from->addArgument("Shops");
    auto res=from->execute(std::move(shop.tab));
    ShopTable shop2;
    EXPECT_EQ(res->tableName,shop2.tab->tableName);
}

TEST(From, One_incorrect_table_in_db){
    ShopTable shop;
    SQLCommand* from=new From;
    from->addArgument("Tanks");
    auto res=from->execute(std::move(shop.tab));
    EXPECT_EQ(res,nullptr);
}