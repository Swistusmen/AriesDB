#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../SQLCommands/SQLCommand.h"

class Parser{
    public:
        std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>> sortCommands(
            std::unique_ptr<std::vector<std::unique_ptr<SQLCommand>>>);
};