#pragma once

#include "../SQLCommands/SQLCommand.h"
#include "../Common/Table.h"

#include <memory>
#include <vector>
//high level interface for a database

using SQLvec =std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>>;

class DataWarehouse{
    public:
        DataWarehouse();
        ~DataWarehouse();
        std::shared_ptr<Table> executeQuery(SQLvec&&);
        std::shared_ptr<Table> tab;

    private:
        std::shared_ptr<Table> mergeVectorOfResultTablesIntoOne(std::vector<std::shared_ptr<Table>> tables);
};