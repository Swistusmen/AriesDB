#include "DataWarehouse.h"

DataWarehouse::DataWarehouse(Logger& _logger):logger(_logger),readTaskExecutor(pager,logger),modifyContentExecutor(logger,pager),modifyStructureExecutor(logger,pager)
{
}

DataWarehouse::~DataWarehouse()
{
    tab.reset();
}

CommandResult DataWarehouse::executeQuery(std::pair<std::vector<std::unique_ptr<SQLCommand>>,Commands::ExecutionType>&& commands)
{
    switch(commands.second){
        case Commands::ExecutionType::READONLY:{
            auto table=readTaskExecutor.execute(std::move(commands.first));
            CommandResult::Result _result;
            table==nullptr?_result=CommandResult::Result::Failure:_result=CommandResult::Result::Success;
            return CommandResult{_result,Commands::ExecutionType::READONLY,std::move(table)};
        }break;
        case Commands::ExecutionType::MODIFY_CONTENT:{
            auto wasQuerySuccessful=modifyContentExecutor.executeCommand(std::move(commands.first));
            CommandResult::Result _result;
            _result=wasQuerySuccessful?CommandResult::Result::Success:CommandResult::Result::Failure;
            return {_result,Commands::ExecutionType::MODIFY_CONTENT};
        }
        case Commands::ExecutionType::MODIFY_STRUCTURE:{
            auto wasQuerySuccessful=modifyStructureExecutor.executeCommand(std::move(commands.first));
            CommandResult::Result _result;
            _result=wasQuerySuccessful?CommandResult::Result::Success:CommandResult::Result::Failure;
            return {_result,Commands::ExecutionType::MODIFY_STRUCTURE};
        }
        default:
            return CommandResult(CommandResult::Result::Failure,Commands::ExecutionType::MODIFY_STRUCTURE);
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