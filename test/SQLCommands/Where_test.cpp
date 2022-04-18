#include "gtest/gtest.h"
#include "../../source/SQLCommands/Where.h"
#include "../Mocks/TableMocks.h"

TEST(Where, Where_equals_one_row){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("category");
    where->addArgument("=");
    where->addArgument("Beauty");
    auto res=where->execute(std::move(shop.tab));

    std::vector<std::string> expected{"1","Rossman","Beauty","1"};
    std::vector<std::string> whatIGet;
    
    int size=res->rows.begin()->size();
    for(int i=0;i<size;i++){
        whatIGet.push_back(res->rows.begin()->at(i));
    }

    EXPECT_EQ(expected,whatIGet);
}

TEST(Where, Where_equals_multiple_rows){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("category");
    where->addArgument("=");
    where->addArgument("Fashion");
    auto res=where->execute(std::move(shop.tab));

    std::vector<std::string> expected{"2","H&M","Fashion","1","3","C&A","Fashion","1","4","NewYorker","Fashion","2"};
    std::vector<std::string> whatIGet;
    
    std::for_each(res->rows.begin(),res->rows.end(),[&whatIGet](auto row){

        std::for_each(row.begin(),row.end(),[&whatIGet](auto var){
                whatIGet.push_back(var);
        });
    });


    EXPECT_EQ(expected,whatIGet);
}

TEST(Where, Where_greater_than_multiple_rows){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("id");
    where->addArgument(">");
    where->addArgument("3");
    auto res=where->execute(std::move(shop.tab));

    std::vector<std::string> expected{"4","NewYorker","Fashion","2","5","Biedronka","Supermarket","2"};
    std::vector<std::string> whatIGet;
    
    std::for_each(res->rows.begin(),res->rows.end(),[&whatIGet](auto row){

        std::for_each(row.begin(),row.end(),[&whatIGet](auto var){
                whatIGet.push_back(var);
        });
    });


    EXPECT_EQ(expected,whatIGet);
}

TEST(Where, Where_less_than_multiple_rows){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("id");
    where->addArgument("<");
    where->addArgument("3");
    auto res=where->execute(std::move(shop.tab));

    std::vector<std::string> expected{"1","Rossman","Beauty","1","2","H&M","Fashion","1"};
    std::vector<std::string> whatIGet;
    
    std::for_each(res->rows.begin(),res->rows.end(),[&whatIGet](auto row){

        std::for_each(row.begin(),row.end(),[&whatIGet](auto var){
                whatIGet.push_back(var);
        });
    });


    EXPECT_EQ(expected,whatIGet);
}

TEST(Where, Where_greater_than_multiple_rows_2){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("category");
    where->addArgument(">");
    where->addArgument("Beauty");
    auto res=where->execute(std::move(shop.tab));

    std::vector<std::string> expected{ "2", "H&M", "Fashion", "1", "3", "C&A", "Fashion", "1", "4", "NewYorker", "Fashion", "2", "5", "Biedronka", "Supermarket", "2" };
    std::vector<std::string> whatIGet;
    
    std::for_each(res->rows.begin(),res->rows.end(),[&whatIGet](auto row){

        std::for_each(row.begin(),row.end(),[&whatIGet](auto var){
                whatIGet.push_back(var);
        });
    });


    EXPECT_EQ(expected,whatIGet);
}

TEST(Where, Where_less_than_multiple_rows_2){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("category");
    where->addArgument("<");
    where->addArgument("Beauty");
    auto res=where->execute(std::move(shop.tab));

    std::vector<std::string> expected{} ;
    std::vector<std::string> whatIGet;
    
    std::for_each(res->rows.begin(),res->rows.end(),[&whatIGet](auto row){

        std::for_each(row.begin(),row.end(),[&whatIGet](auto var){
                whatIGet.push_back(var);
        });
    });


    EXPECT_EQ(expected,whatIGet);
}

