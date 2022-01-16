#pragma once

#include "../Common/Table.h"

#include <memory>
#include <string>
#include <vector>
#include <algorithm>

class SQLCommand
{
public:
    SQLCommand()=default;
    SQLCommand(const SQLCommand &command) = delete;
    SQLCommand(SQLCommand &&command){arguments=std::move(command.arguments);};

    SQLCommand &operator=(SQLCommand &&) noexcept;
    SQLCommand &operator=(const SQLCommand &) = delete;

    virtual ~SQLCommand(){
        arguments.clear();
    };

    void addArgument(std::string word){arguments.push_back(word);};
    std::vector<std::string>& getArguments(){return arguments;};
    virtual int getValidity()=0;

    virtual std::shared_ptr<Table> execute(std::shared_ptr<Table>)=0;

protected:
    std::vector<std::string> arguments;
};