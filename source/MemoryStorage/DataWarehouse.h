#pragma once

#include "../Logger/Logger.h"
#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/ExecutionType.h"
#include "ReadTaskExecutor.h"
#include "ModifyContentExecutor.h"
#include "Pager/Pager.h"

//high level interface for a database

class DataWarehouse{
    public:
        DataWarehouse(Logger& _logger);
        ~DataWarehouse();
        std::unique_ptr<Table> executeQuery(std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>&&);
        std::unique_ptr<Table> tab;

        const std::string& getDeviceStorageLocation() const;
        void setDeviceStroageLocation(const std::string& storageLocation);

    private:
        Pager pager;
        Logger& logger;
        ReadTaskExecutor readTaskExecutor;
        ModifyContentExecutor modifyContentExecutor;
};