#include "Create.h"

Create::Create(Create &&command)
{
    this->arguments=std::move(command.arguments);
    this->tableName=std::move(command.tableName);
}

Create& Create::operator=(Create && Create) noexcept
{
    this->arguments=std::move(Create.arguments);
    this->tableName=std::move(Create.tableName);
    return *this;
}

Create::~Create()
{

}

std::unique_ptr<Table> Create::execute(std::unique_ptr<Table>)
{
    return nullptr;
}

std::vector<std::unique_ptr<Table>> Create::execute(const std::vector<DataBaseTable>& vectorOfTables)
{
    return {};
}

void Create::addArgument(const std::string& word){
    if(tableName==""){
        tableName=word;
    }else{
        arguments.emplace_back(word);
    }
}