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
        std::unique_ptr<Table> executeQuery(SQLvec);
        std::shared_ptr<Table> tab;
};