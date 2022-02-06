#pragma once

#include "../SQLCommands/SQLCommand.h"
#include "Pager/Pager.h"

//high level interface for a database

using SQLvec =std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>>; //To Refactor

class DataWarehouse{
    public:
        DataWarehouse();
        ~DataWarehouse();
        std::shared_ptr<Table> executeQuery(SQLvec&&);
        std::shared_ptr<Table> tab;

        const std::string& getDeviceStorageLocation() const;
        void setDeviceStroageLocation(const std::string& storageLocation);

    private:

        friend std::shared_ptr<Table> test_executeQuery(std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>>&&,DataWarehouse&);
        std::shared_ptr<Table> mergeVectorOfResultTablesIntoOne(std::vector<std::shared_ptr<Table>> tables);

    private:
        Pager pager;
};