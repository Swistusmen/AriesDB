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
#include "OnCreator.h"

class SQLCommandCreator{
public:
    SQLCommandCreator();

    ~SQLCommandCreator();

    std::optional<std::unique_ptr<SQLCommand>>createACommand(std::string word);

private:
    //TODO: refactor
    std::vector<std::unique_ptr<Creator>> creators;
};