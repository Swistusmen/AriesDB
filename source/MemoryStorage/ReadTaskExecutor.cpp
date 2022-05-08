#include "ReadTaskExecutor.h"

ReadTaskExecutor::ReadTaskExecutor(Pager& _pager,Logger& _logger):pager(_pager),logger(_logger){}

std::unique_ptr<Table> ReadTaskExecutor::execute(std::vector<std::unique_ptr<SQLCommand>>&& commands)
{
    if (commands.size() == 0)
    {
        return nullptr;
    }
    const auto &readOnlyTable = pager.getTablesForReadOnly();
    if(readOnlyTable.empty()){
        logger.log("Database is empty",0);
    }
    auto temporaryTables = (dynamic_cast<ReadCommand&>(*commands.at(0))).execute(readOnlyTable);
    if(commands.at(0)->getLog().has_value()){
        logger.log(commands.at(0)->getLog().value(),0);
    }
    for (auto it = commands.begin() + 1; it != commands.end(); it++)
    {
        temporaryTables = (dynamic_cast<ReadCommand&>(**it)).execute(temporaryTables);
        if((*it)->getLog().has_value()){
            logger.log((*it)->getLog().value(),0);
            return nullptr;
        }
    }
    return mergeVectorOfResultTablesIntoOne(temporaryTables);
}
