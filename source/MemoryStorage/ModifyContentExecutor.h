#pragma once

#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/WriteCommand.h"
#include "../SQLCommands/ExecutionType.h"
#include "Pager/Pager.h"
#include "../Logger/Logger.h"

#include <optional>
#include <memory>

class ModifyContentExecutor
{
public:
    ModifyContentExecutor(Logger &_logger, Pager &_pager) : pager(_pager), logger(_logger) {}

    bool executeCommand(std::vector<std::unique_ptr<SQLCommand>> &&);

private:
    Logger &logger;
    Pager &pager;
};
