#include "ModifyContentExecutor.h"

bool ModifyContentExecutor::executeCommand(std::vector<std::unique_ptr<SQLCommand>>&& commands){
    switch((*commands.begin())->getPriority()){
        case SQL::Code::INTO:{
            auto& tables=pager.getTablesForModification();
            auto tableName=dynamic_cast<Into&>(*commands[0]).getTableName();
            auto foundedTable=std::find_if(tables.begin(),tables.end(),[&tableName](auto& table){
                return table.getTableName()==tableName;
            });
            if(foundedTable!=tables.end()){
                auto a=commands[0]->getArguments();
                foundedTable->addRow(std::move(a));
                pager.synchronizeDeviceStorageWithADBState();
                return true;
            }
            return false;
        }break;
    }
}