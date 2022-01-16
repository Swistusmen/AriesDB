#include "Where.h"
#include<iostream>

Where::Where(Where &&command)
{
    this->arguments = std::move(command.arguments);
}

Where &Where::operator=(Where &&command) noexcept
{
    this->arguments = std::move(command.arguments);
    return *this;
}

Where::~Where()
{
}

std::shared_ptr<Table> Where::execute(std::shared_ptr<Table> table)
{
    if (table == nullptr)
    {
        return nullptr;
    }

    auto columnMatch = std::find(table->columns.begin(), table->columns.end(), arguments.at(0));
    if (columnMatch != table->columns.end())
    {
        const int columnIndex = columnMatch - table->columns.begin();
        const auto condition = arguments.at(1);

        table->rows.remove_if([columnIndex, condition](auto& a)
                       { return a.at(columnIndex) != condition; });
        return table;
    }

    return nullptr;
}