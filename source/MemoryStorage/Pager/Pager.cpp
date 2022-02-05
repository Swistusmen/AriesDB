#include "Pager.h"

Pager::Pager()
{
    lastUpdateTime = std::chrono::system_clock::now();
}

Pager::~Pager()
{
    cleanProgramDataBaseTables();
}

void Pager::synchronizeDeviceStorageWithADBState()
{
    std::vector<const DataBaseTable&> toUpdate;

    std::copy_if(tables.begin(),tables.end(),std::back_inserter(toUpdate),[this](auto dbTable){
        return dbTable.getLastModificationDate()-lastUpdateTime>backupTimeIntervalInSeconds;
    });

    for(const auto& tab:toUpdate){
        saveATableIntoATextFile(currentDataBasePath,tab.getTableName(),tab.getTableForReadOnly());
    }
    lastUpdateTime = std::chrono::system_clock::now();
}

void Pager::cleanProgramDataBaseTables()
{
    synchronizeDeviceStorageWithADBState();
    tables.clear();
    files.clear();
    lastUpdateTime = std::chrono::system_clock::now();
}

void Pager::loadDataTables()
{
    if(currentDataBasePath==""){
        return;
    }

    files=listFiles(currentDataBasePath);

    if(files.empty()){
        return;
    }

    for(const auto& fileName: files){
        tables.push_back(loadAFile(currentDataBasePath,fileName));
    }
    lastUpdateTime = std::chrono::system_clock::now();
}

void Pager::addNewTable(Table &&tab)
{
    DataBaseTable dbTable(std::move(tab));
    tables.push_back(std::move(dbTable));
    lastUpdateTime = std::chrono::system_clock::now();
}

void Pager::changeDeviceDataBaseStorageLocation(const std::string &path)
{
    currentDataBasePath = path;
}

const std::vector<DataBaseTable> &Pager::getTablesForReadOnly() const
{
    return tables;
}

const std::string &Pager::getDeviceDataBaseStorageLocation() const
{
    return currentDataBasePath;
}
