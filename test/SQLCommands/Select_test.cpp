#include "gtest/gtest.h"
#include "../../source/SQLCommands/Select.h"
#include "../Mocks/TableMocks.h"

TEST(Select, Select_single_column)
{
    ShopTable shop;
    ReadCommand *select = new Select;
    select->addArgument("shop");
    auto res = select->execute(std::move(shop.tab));

    std::vector<std::string> expected{"Rossman", "H&M", "C&A", "NewYorker", "Biedronka"};
    std::vector<std::string> whatIGet;

    for (auto &row : res->rows)
    {
        whatIGet.push_back(row.at(0));
    }
    EXPECT_EQ(expected, whatIGet);
}

TEST(Select, Select_two_columns)
{
    ShopTable shop;
    ReadCommand *select = new Select;
    select->addArgument("shop");
    select->addArgument("category");
    auto res = select->execute(std::move(shop.tab));

    std::vector<std::string> expected{"Rossman", "H&M", "C&A", "NewYorker", "Biedronka", "Beauty", "Fashion", "Fashion", "Fashion", "Supermarket"};
    std::vector<std::string> whatIGet;

    for (auto &row : res->rows)
    {
        whatIGet.push_back(row.at(0));
    }
    for (auto &row : res->rows)
    {
        whatIGet.push_back(row.at(1));
    }
    EXPECT_EQ(expected, whatIGet);
}