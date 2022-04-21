#pragma once

#include "../Logger/Logger.h"
#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/ExecutionType.h"
#include "../Common/CommandResult.h"
#include "ReadTaskExecutor.h"
#include "ModifyContentExecutor.h"
#include "ModifyStructureExecutor.h"
#include "Pager/Pager.h"

class DataWarehouse{
    public:
        DataWarehouse(Logger& _logger);
        ~DataWarehouse();
        CommandResult executeQuery(std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>&&);
        std::unique_ptr<Table> tab;

        const std::string& getDeviceStorageLocation() const;
        void setDeviceStroageLocation(const std::string& storageLocation);

    private:
        Pager pager;
        Logger& logger;
        ReadTaskExecutor readTaskExecutor;
        ModifyContentExecutor modifyContentExecutor;
        ModifyStructureExecutor modifyStructureExecutor;
};