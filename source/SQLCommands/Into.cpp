#include "Into.h"

Into::Into(Into &&command)
{
    this->arguments=std::move(command.arguments);
    this->tableName=std::move(command.tableName);
}

Into& Into::operator=(Into && into) noexcept
{
    this->arguments=std::move(into.arguments);
    this->tableName=std::move(into.tableName);
    return *this;
}

Into::~Into()
{

}

std::unique_ptr<Table> Into::execute(std::unique_ptr<Table>)
{
    return nullptr;
}

std::vector<std::unique_ptr<Table>> Into::execute(const std::vector<DataBaseTable>& vectorOfTables)
{
    return {};
}

void Into::addArgument(const std::string& word)
{
    if(word=="("||word==")")
        return;
    if(tableName==""){
        tableName=word;
    }else{
    arguments.push_back(word);
    }
}

const std::string& Into::getTableName()
{
    return tableName;
}