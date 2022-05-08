#pragma once

#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/Create.h"
#include "../SQLCommands/ExecutionType.h"
#include "Pager/Pager.h"
#include "../Logger/Logger.h"

#include <optional>
#include <memory>

class ModifyStructureExecutor
{
public:
    ModifyStructureExecutor(Logger &_logger, Pager &_pager) : pager(_pager), logger(_logger) {}

    bool executeCommand(std::vector<std::unique_ptr<SQLCommand>> &&);

private:
    template <typename T>
    std::optional<std::vector<DataBaseTable>::iterator> getTable(std::vector<std::unique_ptr<SQLCommand>> &);

    Logger &logger;
    Pager &pager;
};
