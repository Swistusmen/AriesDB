#include "gtest/gtest.h"
#include "../../source/SQLCommands/Where.h"
#include "../Mocks/TableMocks.h"

TEST(Where, Where_one_condition){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("category");
    where->addArgument("Beauty");
    auto res=where->execute(shop.tab);

    std::vector<std::string> expected{"1","Rossman","Beauty","1"};
    std::vector<std::string> whatIGet;
    
    int size=res->rows.begin()->size();
    for(int i=0;i<size;i++){
        whatIGet.push_back(res->rows.begin()->at(i));
    }

    EXPECT_EQ(expected,whatIGet);
}

TEST(Where, Where_one_condition_multiple_columns){
    ShopTable shop;
    SQLCommand* where=new Where;
    where->addArgument("category");
    where->addArgument("Fashion");
    auto res=where->execute(shop.tab);

    std::vector<std::string> expected{"2","H&M","Fashion","1","3","C&A","Fashion","1","4","NewYorker","Fashion","2"};
    std::vector<std::string> whatIGet;
    
    std::for_each(res->rows.begin(),res->rows.end(),[&whatIGet](auto row){

        std::for_each(row.begin(),row.end(),[&whatIGet](auto var){
                whatIGet.push_back(var);
        });
    });


    EXPECT_EQ(expected,whatIGet);
}
