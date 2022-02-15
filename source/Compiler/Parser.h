#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include "../SQLCommands/SQLCommand.h"

class Parser{
    public:
        void sortCommands(
            std::vector<std::unique_ptr<SQLCommand>>& commands);
};