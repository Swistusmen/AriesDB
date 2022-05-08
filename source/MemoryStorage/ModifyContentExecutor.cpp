#include "ModifyContentExecutor.h"

bool ModifyContentExecutor::executeCommand(std::vector<std::unique_ptr<SQLCommand>> &&commands)
{
    auto command=dynamic_cast<WriteCommand*>(commands[0].release());
    auto tableName=command->getTableName();
    auto &tables = pager.getTablesForModification();
    auto foundedTable = std::find_if(tables.begin(), tables.end(), [&tableName](auto &table)
                                     { return table.getTableName() == tableName; });
                                     
    
    if(foundedTable!=tables.end()){
        command->execute(*foundedTable);
        pager.synchronizeDeviceStorageWithADBState();
        delete command;
        return true;
    } 
    delete command;
    return false;
}
