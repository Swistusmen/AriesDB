#include "Delete.h"

Delete::Delete(Delete &&command)
{
    this->arguments=std::move(command.arguments);
    this->tableName=std::move(command.tableName);
}

Delete& Delete::operator=(Delete && Delete) noexcept
{
    this->arguments=std::move(Delete.arguments);
    this->tableName=std::move(Delete.tableName);
    return *this;
}

Delete::~Delete()
{

}

std::unique_ptr<Table> Delete::execute(std::unique_ptr<Table>)
{
    return nullptr;
}

std::vector<std::unique_ptr<Table>> Delete::execute(const std::vector<DataBaseTable>& vectorOfTables)
{
    return {};
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