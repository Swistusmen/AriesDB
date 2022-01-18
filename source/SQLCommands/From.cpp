#include "From.h"

From::From(From&& command){
    this->arguments=std::move(command.arguments);
}

From& From::operator= (From&& command)noexcept{
    this->arguments=std::move(command.arguments);
    return *this;
}

From::~From(){

}

std::shared_ptr<Table> From::execute(std::shared_ptr<Table> table){
    if(table->tableName==this->arguments[0])
        return table;
    return nullptr;
}

