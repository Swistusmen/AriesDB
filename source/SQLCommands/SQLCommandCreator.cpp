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
        }case SQL::Code::UPDATE:{
            return std::make_unique<Update>();
        }case SQL::Code::DELETE:{
            return std::make_unique<Delete>();
        }case SQL::Code::CREATE:{
            return std::make_unique<Create>();
        }
        default:{
            return {};
        }
    }
}