#include "gtest/gtest.h"
#include "../../source/SQLCommands/On.cpp"
#include "../Mocks/TableMocks.h"

TEST(On, On_correct_join_two_correct_tables){
    ShopTable shop;
    WorkersTable workers;
    SQLCommand* on=new On;
    on->addArgument("Shops.id");
    on->addArgument("Workers.worker_id");
    auto res=on->execute(std::move(shop.tab));

    std::vector<std::string> expected{
        "id", "shop", "category", "floor","worker_id", "work_place", "name", "surname",
        "1", "Rossman", "Beauty", "1","1", "Rossman", "Adam", "Waters",
        "2", "H&M", "Fashion", "1","2", "Rossman", "Joseph", "Eilish",
        "3", "C&A", "Fashion", "1","3", "Rossman", "Anna", "Scott",
        "4", "NewYorker", "Fashion", "2","4", "H&M", "Jeronimo", "Kardashian",
        "5", "Biedronka", "Supermarket", "2","5", "H&M", "Thomas", "Biden"
    };
    std::vector<std::string> actual;
    actual.insert(actual.end(),res->columns.begin(),res->columns.end());
    for(const auto& it: res->rows){
        actual.insert(actual.end(),it.begin(),it.end());
    }

    EXPECT_EQ(actual, expected);
}


