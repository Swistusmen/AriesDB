#pragma once
#include "../../Common/DataBaseTable.h"
#include "OSInterface/FileOperations.h"
#include <memory>
#include <chrono>

using namespace std::chrono_literals;

class Pager
{
public:
    Pager()=default;
    ~Pager();

    const std::vector<DataBaseTable> &getTablesForReadOnly() const;
    std::vector<DataBaseTable> &getTablesForModification();

    void changeDB(const std::string&storageLocation);
    
    void synchronizeDeviceStorageWithADBState();
    void cleanProgramDataBaseTables();
    void changeDeviceDataBaseStorageLocation(const std::string &path);
    const std::string &getDeviceDataBaseStorageLocation() const;
    void loadDataTables();
    void addNewTable(Table &&);

private:
    std::vector<DataBaseTable> tables;
    std::vector<std::string> files;
    std::string currentDataBasePath;
    const std::string fileExtenstion{".txt"};
    const std::chrono::seconds backupTimeIntervalInSeconds{1};
    std::chrono::time_point<std::chrono::system_clock> lastUpdateTime=std::chrono::system_clock::now();
};