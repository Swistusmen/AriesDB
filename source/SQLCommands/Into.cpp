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

bool Into::execute(DataBaseTable& table)
{
    auto rows=getArguments();
    table.addRow(std::move(rows));
    return true;
}
