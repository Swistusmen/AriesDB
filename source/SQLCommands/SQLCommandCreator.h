#pragma once
#include <string>
#include <vector>
#include <memory>
#include <optional>
#include <algorithm>

#include "SQLCommand.h"
#include "FromCreator.h"
#include "SelectCreator.h"
#include "WhereCreator.h"

class SQLCommandCreator{
public:
    SQLCommandCreator();

    ~SQLCommandCreator();

    std::optional<std::unique_ptr<SQLCommand>>createACommand(std::string word);

private:
    std::vector<std::unique_ptr<Creator>> creators;
};