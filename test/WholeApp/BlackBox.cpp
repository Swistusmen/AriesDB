#include "gtest/gtest.h"

#include "../../source/SQLCommands/From.h"

#include "../../source/SQLCommands/Where.h"
#include "../../source/SQLCommands/Select.h"
#include "../../source/SQLCommands/On.h"

#include "../../source/MemoryStorage/DataWarehouse.h"
#include "../../source/MemoryStorage/Pager/Pager.h"
#include "../../source/MemoryStorage/Pager/OSInterface/FileOperations.h"
#include "../../source/Logger/Logger.h"
#include "../../source/Compiler/Compiler.cpp"

#include <vector>   
#include <memory>
#include <utility>

/*
When creating test table to enable deletion after tests, it should have *_test name so that bash script could delete it
*/

class App: public ::testing::Test{
    public:
     App():logger("/home/michal/Documents/Programming/Database/Logs/test.txt",1),db(logger),compiler(logger){
         db.setDeviceStroageLocation("/home/michal/Documents/Programming/Database/source/Tables");
     }   

    protected:

    void query (std::string input){
        auto commands = compiler.compile(input);
        db.executeQuery(std::move(commands));
    }

    DataWarehouse db;
    Compiler compiler;
    Logger logger;
};

std::vector<std::string> flat(const std::unique_ptr<Table>& tab){
    std::vector<std::string> output;
    output.insert(output.end(),tab->columns.begin(),tab->columns.end());
    std::for_each(tab->rows.begin(),tab->rows.end(),[&output](auto row){
            output.insert(output.end(),row.begin(),row.end());
    });
    return output;
}

TEST_F(App,SIMPLE_SELECT){
    std::string input="select * from shops";
    auto commands = compiler.compile(input);
    auto response = db.executeQuery(std::move(commands));
    std::vector<std::string> expected{"id", "shop", "category", "floor",
    "1", "Rossman", "Beauty", "1",
    "2", "H&M", "Fashion", "1",
    "3", "C&A", "Fashion", "1",
    "4", "NewYorker", "Fashion", "2",
    "5", "Biedronka", "Supermarket", "2"};
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,SIMPLE_SELECT_FROM_WHERE_ID_BIGGER_THAN_3){
    std::string input="select * from shops where id > 3";
    auto commands = compiler.compile(input);
    auto response = db.executeQuery(std::move(commands));
    std::vector<std::string> expected{"id", "shop", "category", "floor",
    "4", "NewYorker", "Fashion", "2",
    "5", "Biedronka", "Supermarket", "2"};
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,SIMPLE_SELECT_ALL_FROM_SHOPS_JOIN_WORKERS_ON_ID_EQUALS_ID){
    std::string input="select * from shops join workers on shops.id = workers.worker_id";
    auto commands = compiler.compile(input);
    auto response = db.executeQuery(std::move(commands));
    std::vector<std::string> expected{"worker_id", "work_place", "name", "surname", "id", "shop", "category", "floor", 
    "1", "Rossman", "Adam", "Waters", "1", "Rossman", "Beauty", "1",
      "2", "Rossman", "Joseph", "Eilish", "2", "H&M", "Fashion","1",
       "3", "Rossman", "Anna", "Scott", "3", "C&A", "Fashion", "1",
     "4", "H&M", "Jeronimo", "Kardashian", "4", "NewYorker", "Fashion", "2", 
    "5", "H&M", "Thomas", "Biden", "5", "Biedronka", "Supermarket", "2" };
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,SIMPLE_SELECT_ALL_FROM_SHOPS_JOIN_WORKERS_ON_ID_EQUALS_ID_WHERE_ID_IS_LOWER_THAN_3){
    std::string input="select * from shops join workers on shops.id = workers.worker_id where id < 3";
    auto commands = compiler.compile(input);
    auto response = db.executeQuery(std::move(commands));
    std::vector<std::string> expected{"worker_id", "work_place", "name", "surname", "id", "shop", "category", "floor", 
    "1", "Rossman", "Adam", "Waters", "1", "Rossman", "Beauty", "1",
      "2", "Rossman", "Joseph", "Eilish", "2", "H&M", "Fashion","1" };
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,SIMPLE_SELECT_SOME_FROM_SHOPS_JOIN_WORKERS_ON_ID_EQUALS_ID_WHERE_ID_IS_LOWER_THAN_3){
    std::string input="select id, name, surname, work_place, category from shops join workers on shops.id = workers.worker_id where id < 3";
    auto commands = compiler.compile(input);
    auto response = db.executeQuery(std::move(commands));
    std::vector<std::string> expected{ "work_place", "name", "surname", "id", "category", "Rossman", "Adam", "Waters", "1", "Beauty", "Rossman", "Joseph", "Eilish", "2", "Fashion" };
  
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,SIMPLE_SELECT_ALL_FROM_SHOPS_JOIN_WORKERS_ON_ID_EQUALS_ID_JOIN_ON_PRODUCTS){
    std::string input="select * from shops join workers on shops.id = workers.worker_id join products on workers.worker_id = products.product_id";
    auto commands = compiler.compile(input);
    auto response = db.executeQuery(std::move(commands));


     std::vector<std::string> expected{
        "worker_id", "work_place", "name", "surname", "id", "shop", "category", "floor", "product_id", "product_name", "product_price", "quality",
         "1", "Rossman", "Adam", "Waters", "1", "Rossman", "Beauty", "1", "1", "helmet", "599", "good",
          "2", "Rossman", "Joseph", "Eilish", "2", "H&M", "Fashion", "1","2", "shirt", "10", "good",
          "3", "Rossman", "Anna", "Scott", "3", "C&A", "Fashion", "1", "3", "bed", "13", "good",
          "4", "H&M", "Jeronimo", "Kardashian", "4", "NewYorker", "Fashion", "2", "4", "hhh", "13", "good",
          "5", "H&M", "Thomas", "Biden", "5", "Biedronka", "Supermarket", "2","5", "cccc", "13", "good"
     };


    
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,CREATE_INSERT_SELECT){
    std::string input="create table cartoons_test, cartoon_id, name, year";
    auto commands = compiler.compile(input);
    db.executeQuery(std::move(commands));


    query("insert into cartoons_test values 0, Scooby-Doo, 1980");

    query("insert into cartoons_test values 1, Naruto, 1998");

    std::string input3="select * from cartoons_test";
    auto commands3 = compiler.compile(input3);
    auto response = db.executeQuery(std::move(commands3));

    std::vector<std::string> expected{
        "cartoon_id", "name", "year",
        "0", "Scooby-Doo", "1980",
        "1", "Naruto", "1998"
     };
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,CREATE_INSERT_UPDATE_SELECT){
    std::string input="create table movies_test, movie_id, name, genre, year";
    auto commands = compiler.compile(input);
    db.executeQuery(std::move(commands));

    query("insert into movies_test values 0, Scooby-Doo, kids, 1980");

    query("insert into movies_test values 1, Naruto, anime, 1998");

    query("insert into movies_test values 2, Batman, thriller, 2007");

    query("insert into movies_test values 3, Fight-club, comedy, 1998");

    query("update movies_test set genre = thriller where name = Fight-club");
    
    std::string input3="select * from movies_test";
    auto commands3 = compiler.compile(input3);
    auto response = db.executeQuery(std::move(commands3));

    std::vector<std::string> expected{
        "movie_id", "name", "genre", "year",
        "0", "Scooby-Doo", "kids", "1980",
        "1", "Naruto", "anime","1998",
        "2", "Batman", "thriller", "2007",
        "3", "Fight-club", "thriller", "1998"
     };
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}

TEST_F(App,CREATE_INSERT_DELETE_SELECT){
    std::string input="create table films_test, movie_id, name, genre, year";
    auto commands = compiler.compile(input);
    db.executeQuery(std::move(commands));


    query("insert into films_test values 0, Scooby-Doo, kids, 1980");

    query("insert into films_test values 1, Naruto, anime, 1998");

    query("insert into films_test values 2, Batman, thriller, 2007");

    query("insert into films_test values 3, Fight-club, comedy, 1998");

    query("delete from films_test where movie_id = 2");
    
    std::string input3="select * from films_test";
    auto commands3 = compiler.compile(input3);
    auto response = db.executeQuery(std::move(commands3));

    std::vector<std::string> expected{
        "movie_id", "name", "genre", "year",
        "0", "Scooby-Doo", "kids", "1980",
        "1", "Naruto", "anime","1998",
        "3", "Fight-club", "comedy", "1998"
     };
    auto actual=flat(response.getTable());
    ASSERT_EQ(expected,actual);
}