#pragma once

#include "SQLCommand.h"

class ReadCommand: public SQLCommand{
public:

    ReadCommand();
    ReadCommand(ReadCommand &&command); 
    ~ReadCommand();

    virtual std::unique_ptr<Table> execute(std::unique_ptr<Table>) = 0;
    virtual std::vector<std::unique_ptr<Table>> execute(std::vector<std::unique_ptr<Table>> & tables);
    virtual std::vector<std::unique_ptr<Table>> execute(const std::vector< DataBaseTable>& tableOfVectors){return {};};

    std::vector<std::string> &getArguments() { return arguments; };
    void addArgument(const std::string& word) override{ arguments.push_back(word); };

protected:
    std::vector<std::string> arguments;
};