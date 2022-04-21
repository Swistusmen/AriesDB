#include "ModifyContentExecutor.h"

bool ModifyContentExecutor::executeCommand(std::vector<std::unique_ptr<SQLCommand>> &&commands)
{
    switch ((*commands.begin())->getPriority())
    {
    case SQL::Code::INTO:
    {
        auto val=getTable<Into>(commands);
        if(val.has_value())
        {
            auto rows = commands[0]->getArguments();
            val.value()->addRow(std::move(rows));
            pager.synchronizeDeviceStorageWithADBState();
            return true;
        }
        return false;
    }
    break;
    case SQL::Code::UPDATE:
    {
        auto val=getTable<Update>(commands);
        if(val.has_value())
        {
            auto &cCols = dynamic_cast<Update &>(*commands[0]).getConditionalColumns();
            auto &cVals = dynamic_cast<Update &>(*commands[0]).getConditionalValues();
            auto &cOps = dynamic_cast<Update &>(*commands[0]).getConditionalOperators();
            auto &cols = dynamic_cast<Update &>(*commands[0]).getValuesColumns();
            auto &vals = dynamic_cast<Update &>(*commands[0]).getValues();
            val.value()->findAndUpdate(cCols, cOps, cVals, cols, vals);
            pager.synchronizeDeviceStorageWithADBState();
            return true;
        }
    }
    break;
    case SQL::Code::DELETE:{
        auto val=getTable<Delete>(commands);
        if(val.has_value()){
            auto &cols=dynamic_cast<Delete&>(*commands[0]).getColumns();
            auto &vals=dynamic_cast<Delete&>(*commands[0]).getValues();
            auto &operators=dynamic_cast<Delete&>(*commands[0]).getOperators();
            val.value()->findAndRemoveIfEquals(cols,operators,vals);
            pager.synchronizeDeviceStorageWithADBState();
            return true;
        }
    }break;
    default:
        return false;
    }
    return false;
}

template <typename T>
std::optional<std::vector<DataBaseTable>::iterator> ModifyContentExecutor::getTable(std::vector<std::unique_ptr<SQLCommand>>& commands)
{
    auto &tables = pager.getTablesForModification();
    auto tableName = dynamic_cast<T&>(*commands[0]).getTableName();
    auto foundedTable = std::find_if(tables.begin(), tables.end(), [&tableName](auto &table)
                                     { return table.getTableName() == tableName; });
    if(foundedTable!=tables.end()){
        return foundedTable;
    } 
    return{};
}