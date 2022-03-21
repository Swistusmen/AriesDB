#pragma once

#include "../Logger/Logger.h"
#include "../SQLCommands/SQLCommand.h"
#include "Pager/Pager.h"

//high level interface for a database

class DataWarehouse{
    public:
        DataWarehouse(Logger& _logger);
        ~DataWarehouse();
        std::unique_ptr<Table> executeQuery(std::vector<std::unique_ptr<SQLCommand>>&&);
        std::unique_ptr<Table> tab;

        const std::string& getDeviceStorageLocation() const;
        void setDeviceStroageLocation(const std::string& storageLocation);

    private:

        friend std::unique_ptr<Table> test_executeQuery(std::vector<std::unique_ptr<SQLCommand>>&&,DataWarehouse&);
        std::unique_ptr<Table> mergeVectorOfResultTablesIntoOne(std::vector<std::unique_ptr<Table>>& tables);
        std::unique_ptr<Table> executeReadOnlyQuery(std::vector<std::unique_ptr<SQLCommand>>&&);

    private:
        Pager pager;
        Logger& logger;
};