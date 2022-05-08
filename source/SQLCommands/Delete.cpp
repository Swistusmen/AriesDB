#include "Delete.h"

Delete::Delete(Delete &&command)
{
    this->columns=std::move(command.columns);
    this->operators=std::move(command.operators);
    this->values=std::move(command.values);
    this->tableName=std::move(command.tableName);
}

Delete& Delete::operator=(Delete && command) noexcept
{
    this->columns=std::move(command.columns);
    this->operators=std::move(command.operators);
    this->values=std::move(command.values);
    this->tableName=std::move(command.tableName);
    return *this;
}

Delete::~Delete()
{

}

void Delete::addArgument(const std::string& word) 
{
    if(tableName==""){
        tableName=word;
    }else{
        if(word=="="||word=="<"||word==">"){
            operators.emplace_back(word);
        }else{
            if(columns.size()==values.size()){
                columns.emplace_back(word);
            }else{
                values.emplace_back(word);
            }
        }
    }

}

bool Delete::execute(DataBaseTable& table)
{
    return static_cast<bool>(table.findAndRemoveIfEquals(columns,operators,values));
}