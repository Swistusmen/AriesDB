#pragma once

#include "SQLCommand.h"

class WriteCommand:public SQLCommand{
public:
    WriteCommand(){};

    WriteCommand(WriteCommand &&command){
        tableName=std::move(command.tableName);
    }; 

    ~WriteCommand(){};

    virtual void addArgument(const std::string& word)=0;
    virtual bool execute(DataBaseTable&)=0;
    const std::string& getTableName(){return tableName;};
protected:
    std::string tableName;
};