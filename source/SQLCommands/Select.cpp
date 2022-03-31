#include "Select.h"

Select::Select(Select &&command)
{
    this->arguments = std::move(command.arguments);
}

Select &Select::operator=(Select &&command) noexcept
{
    this->arguments = std::move(command.arguments);
    return *this;
}

Select::~Select()
{
}

std::unique_ptr<Table> Select::execute(std::unique_ptr<Table> table)
{
    if (table == nullptr)
    {
        return nullptr;
    }
    auto newTable = std::make_unique<Table>(table->tableName, "0");

    std::copy_if(table->columns.begin(), table->columns.end(), std::back_inserter(newTable->columns), [this](auto &a)
                 { return std::find(arguments.begin(), arguments.end(), a) != arguments.end(); });

    std::vector<int> matchingColumnIndexes;
    std::for_each(newTable->columns.begin(), newTable->columns.end(), [&table, &matchingColumnIndexes](auto &a) mutable
                  { matchingColumnIndexes.push_back(std::find(table->columns.begin(), table->columns.end(), a) - table->columns.begin()); });

    for (auto it = table->rows.begin(); it != table->rows.end(); it++)
    {
        std::vector<std::string> buffer;
        std::for_each(matchingColumnIndexes.begin(), matchingColumnIndexes.end(), [&buffer, &it](auto index)
                      { buffer.push_back(it->at(index)); });
        newTable->rows.push_back(std::move(buffer));
    }

    return newTable;
}
