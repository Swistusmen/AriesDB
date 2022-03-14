#pragma once
#include <memory>

#include "SQLCommand.h"
#include <iostream>

class Creator
{
public:

    virtual bool doesAWordRepresentSQLCommand(std::string)=0;
    virtual std::unique_ptr<SQLCommand> createASQLCommand()=0;

protected:
    void toLower(std::string &word)
    {
        for(auto& elem: word){
            elem=std::tolower(elem);
        }
    }
};