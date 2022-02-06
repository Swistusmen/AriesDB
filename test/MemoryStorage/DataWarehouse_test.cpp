#include "gtest/gtest.h"

#include "../../source/SQLCommands/From.h"

#include "../../source/SQLCommands/Where.h"
#include "../../source/SQLCommands/Select.h"

#include "../../source/MemoryStorage/DataWarehouse.cpp"
#include "../../source/MemoryStorage/Pager/Pager.cpp"
#include "../../source/MemoryStorage/Pager/OSInterface/FileOperations.cpp"

#include <vector>
#include <memory>
#include <utility>

TEST(Data_Warehoouse,Simple_query_select_from_where_one_table){
    // mocking compiler output
    auto res=std::make_unique<std::vector<std::unique_ptr<SQLCommand>>>();
    
    res->emplace_back(std::make_unique<From>());
    res->back()->addArgument("Shops");
    res->push_back(std::make_unique<Where>());
    res->back()->addArgument("id");
    res->back()->addArgument(">");
    res->back()->addArgument("3");
    res->push_back(std::make_unique<Select>()); 
    res->back()->addArgument("category");
    res->back()->addArgument("shop");
    // mocking compiler output
    
    DataWarehouse db;
    auto output=test_executeQuery(std::move(res),db);
    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    std::vector<std::string> expected{"shop", "category", "NewYorker", "Fashion", "Biedronka", "Supermarket"};

    ASSERT_EQ(expected, flatTable);

}
