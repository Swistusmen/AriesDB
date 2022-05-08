#pragma once

#include "SQLCommand.h"

class ReorganizeCommand : public SQLCommand
{
public:
    ReorganizeCommand(){};

    ReorganizeCommand(ReorganizeCommand &&command)
    {
        tableName = std::move(command.tableName);
        arguments=std::move(command.arguments);
    };

    ~ReorganizeCommand(){};

    virtual void addArgument(const std::string &word) = 0;
    const std::string &getTableName() { return tableName; };
    const std::vector<std::string>& getArguments(){return arguments;}

protected:
    std::vector<std::string> arguments;
    std::string tableName;
};