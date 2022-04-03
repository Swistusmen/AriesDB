#include "DataWarehouse.h"

DataWarehouse::DataWarehouse(Logger& _logger):logger(_logger),readTaskExecutor(pager,logger)
{
}

DataWarehouse::~DataWarehouse()
{
    tab.reset();
}

std::unique_ptr<Table> DataWarehouse::executeQuery(std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>&& commands)
{
    switch(commands.second){
        case Commands::ExecutionType::READONLY:
            return readTaskExecutor.execute(std::move(commands.first));
        case Commands::ExecutionType::MODIFY_STRUCTURE:
        case Commands::ExecutionType::MODIFY_CONTENT:
        default:
            return nullptr;
    }
    
}

const std::string &DataWarehouse::getDeviceStorageLocation() const
{
    return pager.getDeviceDataBaseStorageLocation();
}

void DataWarehouse::setDeviceStroageLocation(const std::string &storageLocation)
{
    pager.changeDB(storageLocation);
}