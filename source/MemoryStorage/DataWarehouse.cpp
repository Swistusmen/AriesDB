#include "DataWarehouse.h"

DataWarehouse::DataWarehouse(){
    tab=std::make_shared<Table>("Shops","1");
    tab->columns=std::vector<std::string>{"id","shop","category","floor"};
    std::vector<std::string> a{"1","Rossman","Beauty","1"};
    std::vector<std::string> b{"2","H&M","Fashion","1"};
    std::vector<std::string> c{"3","C&A","Fashion","1"};
    std::vector<std::string> d{"4","NewYorker","Fashion","2"};
    std::vector<std::string> e{"5","Biedronka","Supermarket","2"};
    tab->rows.push_back(a);
    tab->rows.push_back(b);
    tab->rows.push_back(c);
    tab->rows.push_back(d);
    tab->rows.push_back(e);
}

DataWarehouse::~DataWarehouse(){
    tab.reset();
}

std::unique_ptr<Table> DataWarehouse::executeQuery(SQLvec vec){
    
    //write a method which takes vector of tables ()- it calls a metod on every element of a table, thanks to what we got smaller table
    //output of previous query is an input of next query
    //after all, every table in a vector is unified into one big output table which is returned

    return nullptr;
}