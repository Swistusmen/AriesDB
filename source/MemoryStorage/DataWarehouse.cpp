#include "DataWarehouse.h"

DataWarehouse::DataWarehouse()
{
}

DataWarehouse::~DataWarehouse()
{
    tab.reset();
}

std::unique_ptr<Table> DataWarehouse::executeQuery(std::vector<std::unique_ptr<SQLCommand>> &&commands)
{
    return executeReadOnlyQuery(std::move(commands));
}

std::unique_ptr<Table> DataWarehouse::executeReadOnlyQuery(std::vector<std::unique_ptr<SQLCommand>> &&commands)
{
    if (commands.size() == 0)
    {
        return nullptr;
    }
    const auto &readOnlyTable = pager.getTablesForReadOnly();
    auto temporaryTables = commands.at(0)->execute(readOnlyTable);
    for (auto it = commands.begin() + 1; it != commands.end(); it++)
    {
        temporaryTables = (*it)->execute(temporaryTables);
    }
    return mergeVectorOfResultTablesIntoOne(temporaryTables);
}

std::unique_ptr<Table> DataWarehouse::mergeVectorOfResultTablesIntoOne(std::vector<std::unique_ptr<Table>> &tables)
{
    const int noTables = tables.size();
    if (noTables == 0)
    {
        return nullptr;
    }

    if (noTables == 1)
    {
        return std::move(tables.at(0));
    }

    std::cout<<(tables.at(0)==nullptr)<<" "<<(tables.at(1)==nullptr)<<std::endl;
    auto it = tables.begin();
    std::cout<<(tables.at(0)==nullptr)<<" "<<(tables.at(1)==nullptr)<<std::endl;
    auto outputTable = std::move(*it);
    std::cout<<(tables.at(0)==nullptr)<<" "<<(tables.at(1)==nullptr)<<std::endl;
    int i=0;
    std::cout<<"Tables: "<<tables.size()<<std::endl;
    it++;
    for (; it != tables.end();it++)
    {
        std::cout<<"Obieg "<<i++<<" is nuppltr: "<<(outputTable==nullptr)<<std::endl;
        std::cout<<((*it)==nullptr)<<std::endl;
        outputTable->columns.insert(outputTable->columns.end(), (*it)->columns.begin(), (*it)->columns.end());
        std::cout<<"ELuwina\n";
        std::cout<<(*it)->tableName<<std::endl;

        for(auto row=outputTable->rows.begin(), add=(*it)->rows.begin();row!=outputTable->rows.end() ;add++,row++){
            std::cout<<"O\n";
            row->insert(row->end(),add->begin(),add->end());    
        }

    }
    std::cout<<"Wyszedlem z petli i koncze z tym syfem\n";

    return outputTable;
}

const std::string &DataWarehouse::getDeviceStorageLocation() const
{
    return pager.getDeviceDataBaseStorageLocation();
}

void DataWarehouse::setDeviceStroageLocation(const std::string &storageLocation)
{
    pager.changeDB(storageLocation);
}

std::unique_ptr<Table> test_executeQuery(std::vector<std::unique_ptr<SQLCommand>> &&commands, DataWarehouse &db)
{
    auto tab = std::make_unique<Table>("Shops", "1");
    tab->columns = std::vector<std::string>{"id", "shop", "category", "floor"};
    std::vector<std::string> a{"1", "Rossman", "Beauty", "1"};
    std::vector<std::string> b{"2", "H&M", "Fashion", "1"};
    std::vector<std::string> c{"3", "C&A", "Fashion", "1"};
    std::vector<std::string> d{"4", "NewYorker", "Fashion", "2"};
    std::vector<std::string> e{"5", "Biedronka", "Supermarket", "2"};
    tab->rows.push_back(a);
    tab->rows.push_back(b);
    tab->rows.push_back(c);
    tab->rows.push_back(d);
    tab->rows.push_back(e);
    std::vector<std::unique_ptr<Table>> processingTables;
    processingTables.push_back(std::move(tab));

    for (const auto &command : commands)
    {
        processingTables = command->execute(processingTables);
    }

    return db.mergeVectorOfResultTablesIntoOne(processingTables);
}