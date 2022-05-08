#pragma once

#include "../Common/Table.h"
#include "../Common/DataBaseTable.h"
#include "Commands.h"

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>

#include <variant>


class SQLCommand
{
public:
    SQLCommand() = default;
    SQLCommand(const SQLCommand &command) = delete;
    SQLCommand(SQLCommand &&command){log=std::move(command.log);};

    SQLCommand &operator=(SQLCommand && command){
        log=std::move(command.log);
        return *this;
    };

    SQLCommand &operator=(const SQLCommand &) = delete;

    virtual ~SQLCommand(){};

    virtual void addArgument(const std::string& word)=0;

    virtual SQL::Code getPriority() = 0;

    std::optional<std::string> getLog() const {
        if(log=="")
            return {};
        return log;
    };

protected:
    std::string log{""};
};

using commandToExecute=std::variant<std::unique_ptr<SQLCommand>,std::vector<std::unique_ptr<SQLCommand>>>;