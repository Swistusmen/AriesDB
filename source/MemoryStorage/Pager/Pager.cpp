#include "Pager.h"

Pager::~Pager()
{
    cleanProgramDataBaseTables();
}

void Pager::changeDB(const std::string &storageLocation)
{
    synchronizeDeviceStorageWithADBState();
    changeDeviceDataBaseStorageLocation(storageLocation);
    loadDataTables();
}

void Pager::synchronizeDeviceStorageWithADBState()
{
    if (currentDataBasePath == "")
    {
        return;
    }
    std::list<std::vector<DataBaseTable>::iterator> toUpdate;

    for (auto it = tables.begin(); it != tables.end(); it++)
    {
        if (it->getLastModificationDate() - lastUpdateTime > backupTimeIntervalInSeconds)
        {
            toUpdate.push_back(it);
        }
    }

    for (const auto &tab : toUpdate)
    {
        saveATableIntoATextFile(currentDataBasePath, tab->getTableName(), tab->getTableDataForReadOnly());
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
    if (currentDataBasePath == "")
    {
        return;
    }
    files = listFiles(currentDataBasePath);

    if (files.empty())
    {
        return;
    }
    for (const auto &fileName : files)
    {
        auto loadedFile = loadAFile(currentDataBasePath, fileName);
        if (loadedFile.has_value())
        {
            tables.push_back(std::move(loadedFile.value()));
        }
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

std::vector<DataBaseTable> &Pager::getTablesForModification()
{
    return tables;
}

const std::string &Pager::getDeviceDataBaseStorageLocation() const
{
    return currentDataBasePath;
}
