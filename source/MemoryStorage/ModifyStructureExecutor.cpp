#include "ModifyStructureExecutor.h"

bool ModifyStructureExecutor::executeCommand(std::vector<std::unique_ptr<SQLCommand>> &&commands)
{
    switch ((*commands.begin())->getPriority())
    {
    case SQL::Code::CREATE:
    {
        auto tableName = dynamic_cast<Create&>(*commands[0]).getTableName();
        const auto& columns=dynamic_cast<Create&>(*commands[0]).getArguments();
        Table tab;
        tab.tableName=tableName;
        tab.columns=columns;
        pager.addNewTable(std::move(tab));
        pager.synchronizeDeviceStorageWithADBState();
        return true;
    }
    break;
    default:
        return false;
    }
}