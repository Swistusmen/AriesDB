#pragma once  

#include "../SQLCommands/SQLCommand.h"
#include "../SQLCommands/ReadCommand.h"
#include "CommonExecutorHelperFunctions.h"
#include "../Logger/Logger.h"
#include "Pager/Pager.h"
#include <vector>

class ReadTaskExecutor{
    public:
        ReadTaskExecutor(Pager& _pager, Logger& _logger);
        std::unique_ptr<Table> execute(std::vector<std::unique_ptr<SQLCommand>>&& );
    private:
        Pager& pager;
        Logger& logger;
};