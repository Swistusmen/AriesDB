#include "SQLCommandCreator.h"

SQLCommandCreator::SQLCommandCreator(){
}

SQLCommandCreator::~SQLCommandCreator(){
}

std::optional<std::unique_ptr<SQLCommand>> SQLCommandCreator::createACommand(const std::string& word)
{
    SQL::Code code=SQL::toCode(word);
    switch(code){
        case SQL::Code::FROM:{
            return std::make_unique<From>();
        }case SQL::Code::ON:{
            return std::make_unique<On>();
        }case SQL::Code::SELECT:{
            return std::make_unique<Select>();
        }case SQL::Code::WHERE:{
            return std::make_unique<Where>();
        }case SQL::Code::INTO:{
            return std::make_unique<Into>();
        } 
        /*
        commands: join are
         a command in SQL-sense, but does not have a function representation in this progra
         such a commands are a compiled time operations
         */
        default:{
            return {};
        }
    }
}