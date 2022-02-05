#include "DataWarehouse.h"
#include<iostream>

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

std::shared_ptr<Table> DataWarehouse::executeQuery(SQLvec&& vec){
    std::vector<std::shared_ptr<Table>> systemTables{tab}; //vector of tables provided by the system- for now it's that
    std::vector<std::shared_ptr<Table>> processingTables=systemTables;

    for(const auto& command: *vec){
        processingTables=command->execute(processingTables);
    }

    return mergeVectorOfResultTablesIntoOne(processingTables);
}

std::shared_ptr<Table> DataWarehouse::mergeVectorOfResultTablesIntoOne(std::vector<std::shared_ptr<Table>> tables){
    const int noTables=tables.size();
    if(noTables==0){
        return nullptr;
    }

    if(noTables==1){
        return tables.at(0);
    }

    auto it=tables.begin();
    auto outputTable=*it;
    

    for(;it!=tables.end();++it){
        outputTable->columns.insert(outputTable->columns.end(),(*it)->columns.begin(),(*it)->columns.end());

        std::for_each(outputTable->rows.begin(),outputTable->rows.end(),[&it](auto row){
                std::for_each((*it)->rows.begin(),(*it)->rows.end(),[&row](auto toAdd){
                    row.insert(row.end(),toAdd.begin(),toAdd.end());
                });
        });
    }

    return outputTable;
}