#pragma once

#include "../Common/Table.h"
#include "../Common/DataBaseTable.h"
#include "Commands.h"

#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>

class SQLCommand
{
public:
    SQLCommand() = default;
    SQLCommand(const SQLCommand &command) = delete;
    SQLCommand(SQLCommand &&command) { arguments = std::move(command.arguments); };

    SQLCommand &operator=(SQLCommand &&) noexcept;
    SQLCommand &operator=(const SQLCommand &) = delete;

    virtual ~SQLCommand()
    {
        arguments.clear();
    };

    virtual void addArgument(const std::string& word) { arguments.push_back(word); };
    std::vector<std::string> &getArguments() { return arguments; };
    virtual SQL::Code getPriority() = 0;

    virtual std::unique_ptr<Table> execute(std::unique_ptr<Table>) = 0;

    //TODO: it need to be refactored, the stupidiest thing I've ever done
    virtual std::vector<std::unique_ptr<Table>> execute(std::vector<std::unique_ptr<Table>> & tables)
    {
        std::vector<std::unique_ptr<Table>> vecOfValidTables;
        for (auto &tab : tables)
        {
            auto res = this->execute(std::move(tab));
            if (res != nullptr)
            {
                vecOfValidTables.push_back(std::move(res));
            }
        }
        return vecOfValidTables;
    }

    virtual std::vector<std::unique_ptr<Table>> execute(const std::vector< DataBaseTable>& tableOfVectors){return {};};

    std::optional<std::string> getLog() const {
        if(log=="")
            return {};
        return log;
    };
protected:
    std::vector<std::string> arguments;
    std::string log{""};
};