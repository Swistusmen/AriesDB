#include "gtest/gtest.h"

#include "../../source/SQLCommands/From.h"

#include "../../source/SQLCommands/Where.h"
#include "../../source/SQLCommands/Select.h"
#include "../../source/SQLCommands/On.h"

#include "../../source/MemoryStorage/DataWarehouse.cpp"
#include "../../source/MemoryStorage/Pager/Pager.cpp"
#include "../../source/MemoryStorage/Pager/OSInterface/FileOperations.cpp"
#include "../../source/Logger/Logger.cpp"
#include "../../source/Common/Algorithms.h"
#include "../../source/Common/Algorithms.cpp"

#include <vector>
#include <memory>
#include <utility>
#include <tuple>

class Mocked_DataWarehouse: public ::testing::Test{
    public:
     Mocked_DataWarehouse():logger("/home/michal/Documents/Programming/Database/Logs/test.txt",1),db(logger){
         db.setDeviceStroageLocation("/home/michal/Documents/Programming/Database/source/Tables");
     }   
    protected:

    DataWarehouse db;

    private:

    Logger logger;

};

TEST(Data_Warehoouse,Simple_query_select_from_where_one_table){
    // mocking compiler output
    std::vector<std::unique_ptr<SQLCommand>> res;
    
    res.emplace_back(std::make_unique<From>());
    res.back()->addArgument("Shops");
    res.push_back(std::make_unique<Where>());
    res.back()->addArgument("id");
    res.back()->addArgument(">");
    res.back()->addArgument("3");
    res.push_back(std::make_unique<Select>()); 
    res.back()->addArgument("category");
    res.back()->addArgument("shop");
    // mocking compiler output
    Logger logger("/home/michal/Documents/Programming/Database/Logs/test.txt",8);
    DataWarehouse db(logger);
    auto output=test_executeQuery(std::move(res),db);
    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    std::vector<std::string> expected{"shop", "category", "NewYorker", "Fashion", "Biedronka", "Supermarket"};

    ASSERT_EQ(expected, flatTable);
}

TEST_F(Mocked_DataWarehouse,POSITIVE_SELECT_FROM_WHERE){
     std::vector<std::unique_ptr<SQLCommand>> res;
     res.emplace_back(std::make_unique<From>());
     res.back()->addArgument("shops");
     res.push_back(std::make_unique<Where>());
    res.back()->addArgument("id");
    res.back()->addArgument(">");
    res.back()->addArgument("3");
    res.push_back(std::make_unique<Select>()); 
    res.back()->addArgument("category");
    res.back()->addArgument("shop");
    auto arg=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res),Commands::ExecutionType::READONLY);
    auto output=db.executeQuery(std::move(arg));

    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    std::vector<std::string> expected{"shop", "category", "NewYorker", "Fashion", "Biedronka", "Supermarket"};

    ASSERT_EQ(expected, flatTable);
}

TEST_F(Mocked_DataWarehouse,POSITIVE_SELECT_FROM){
     std::vector<std::unique_ptr<SQLCommand>> res;
     res.emplace_back(std::make_unique<From>());
     res.back()->addArgument("shops");
        auto arg=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res),Commands::ExecutionType::READONLY);
        auto output=db.executeQuery(std::move(arg));

    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    
    std::vector<std::string> expected{"id", "shop", "category", "floor",
    "1", "Rossman", "Beauty", "1",
    "2", "H&M", "Fashion", "1",
    "3", "C&A", "Fashion", "1",
    "4", "NewYorker", "Fashion", "2",
    "5", "Biedronka", "Supermarket", "2"};

    ASSERT_EQ(expected, flatTable);
}

TEST_F(Mocked_DataWarehouse,POSITIVE_SELECT_FROM_JOIN_ON_WHERE_ID_BIGGER_THAN_THREE){
     std::vector<std::unique_ptr<SQLCommand>> res;
     res.emplace_back(std::make_unique<From>());
     res.back()->addArgument("shops");
     res.back()->addArgument("workers");
     res.emplace_back(std::make_unique<On>());
     res.back()->addArgument("workers.worker_id");
     res.back()->addArgument("shops.id");
     res.push_back(std::make_unique<Where>());
    res.back()->addArgument("id");
    res.back()->addArgument(">");
    res.back()->addArgument("3");
    res.push_back(std::make_unique<Select>()); 
    res.back()->addArgument("category");
    res.back()->addArgument("shop");
        auto arg=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res),Commands::ExecutionType::READONLY);
    auto output=db.executeQuery(std::move(arg));

    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    std::vector<std::string> expected{"shop", "category", "NewYorker", "Fashion", "Biedronka", "Supermarket"};

    ASSERT_EQ(expected, flatTable);
}

TEST_F(Mocked_DataWarehouse,POSITIVE_SELECT_ALL_FROM_JOIN_ON){
     std::vector<std::unique_ptr<SQLCommand>> res;
     res.emplace_back(std::make_unique<From>());
     res.back()->addArgument("shops");
     res.back()->addArgument("workers");
     res.emplace_back(std::make_unique<On>());
     res.back()->addArgument("workers.worker_id");
     res.back()->addArgument("shops.id");

        auto arg=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res),Commands::ExecutionType::READONLY);
    auto output=db.executeQuery(std::move(arg));

    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    std::vector<std::string> expected{"worker_id", "work_place", "name", "surname", "id", "shop", "category", "floor", 
    "1", "Rossman", "Adam", "Waters", "1", "Rossman", "Beauty", "1",
      "2", "Rossman", "Joseph", "Eilish", "2", "H&M", "Fashion","1",
       "3", "Rossman", "Anna", "Scott", "3", "C&A", "Fashion", "1",
     "4", "H&M", "Jeronimo", "Kardashian", "4", "NewYorker", "Fashion", "2", 
    "5", "H&M", "Thomas", "Biden", "5", "Biedronka", "Supermarket", "2" };

    ASSERT_EQ(expected, flatTable);
}

TEST_F(Mocked_DataWarehouse,POSITIVE_SELECT_ALL_FROM_JOIN_ON_WHERE_ID_EQUALS_3){
     std::vector<std::unique_ptr<SQLCommand>> res;
     res.emplace_back(std::make_unique<From>());
     res.back()->addArgument("shops");
     res.back()->addArgument("workers");
     res.emplace_back(std::make_unique<On>());
     res.back()->addArgument("workers.worker_id");
     res.back()->addArgument("shops.id");
     res.emplace_back(std::make_unique<Where>());
        res.back()->addArgument("id");
    res.back()->addArgument("=");
    res.back()->addArgument("3");

        auto arg=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res),Commands::ExecutionType::READONLY);
    auto output=db.executeQuery(std::move(arg));

    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });
    std::vector<std::string> expected{"worker_id", "work_place", "name", "surname", "id", "shop", "category", "floor", 
       "3", "Rossman", "Anna", "Scott", "3", "C&A", "Fashion", "1"};

    ASSERT_EQ(expected, flatTable);
}

TEST_F(Mocked_DataWarehouse,SAME_SELECT_AFTER_SELECT_GIVE_SAME_RESULT){
     std::vector<std::unique_ptr<SQLCommand>> res;
     res.emplace_back(std::make_unique<From>());
     res.back()->addArgument("shops");
     res.back()->addArgument("workers");
     res.emplace_back(std::make_unique<On>());
     res.back()->addArgument("workers.worker_id");
     res.back()->addArgument("shops.id");
     res.emplace_back(std::make_unique<Where>());
        res.back()->addArgument("id");
    res.back()->addArgument("=");
    res.back()->addArgument("3");

        auto arg=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res),Commands::ExecutionType::READONLY);
    auto output=db.executeQuery(std::move(arg));

    std::vector<std::string> flatTable;
    flatTable.insert(flatTable.end(),output->columns.begin(),output->columns.end());
    std::for_each(output->rows.begin(),output->rows.end(),[&flatTable](auto row){
            flatTable.insert(flatTable.end(),row.begin(),row.end());
    });

    std::vector<std::unique_ptr<SQLCommand>> res2;
     res2.emplace_back(std::make_unique<From>());
     res2.back()->addArgument("shops");
     res2.back()->addArgument("workers");
     res2.emplace_back(std::make_unique<On>());
     res2.back()->addArgument("workers.worker_id");
     res2.back()->addArgument("shops.id");
     res2.emplace_back(std::make_unique<Where>());
        res2.back()->addArgument("id");
    res2.back()->addArgument("=");
    res2.back()->addArgument("3");

        auto arg2=std::make_pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>(std::move(res2),Commands::ExecutionType::READONLY);
    auto output2=db.executeQuery(std::move(arg2));

    std::vector<std::string> flatTable2;
    flatTable2.insert(flatTable2.end(),output2->columns.begin(),output2->columns.end());
    std::for_each(output2->rows.begin(),output2->rows.end(),[&flatTable2](auto row){
            flatTable2.insert(flatTable2.end(),row.begin(),row.end());
    });

    ASSERT_EQ(flatTable2, flatTable);
}




