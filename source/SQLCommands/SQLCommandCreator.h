#pragma once

#include <memory>
#include <optional>
#include "Where.h"
#include "Select.h"
#include "On.h"
#include "From.h"
#include "Into.h"
#include "Update.h"
#include "Delete.h"
#include "Create.h"

#include "SQLCommand.h"

class SQLCommandCreator{
public:
    SQLCommandCreator();

    ~SQLCommandCreator();

    std::optional<std::unique_ptr<SQLCommand>>createACommand(const std::string& word);
};