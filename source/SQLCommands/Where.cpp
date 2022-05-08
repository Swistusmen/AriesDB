#include "Where.h"

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

std::unique_ptr<Table> Where::execute(std::unique_ptr<Table> table)
{
    if (table == nullptr)
    {
        return nullptr;
    }
    if(arguments.size()%3!=0){
        log="Error, Where: syntax error, get wrong number arguments";
        return nullptr;
    }

    auto columnMatch = std::find(table->columns.begin(), table->columns.end(), arguments.at(0));
    if (columnMatch != table->columns.end())
    {
        const int columnIndex = columnMatch - table->columns.begin();
        const auto conditionValue = arguments.at(2);
        std::string conditionOperator=arguments.at(1);

        if(conditionOperator=="="){
            table->rows.remove_if([columnIndex, conditionValue](auto& a)
                       { return a.at(columnIndex) != conditionValue; });
        }else if(conditionOperator=="<"){
            table->rows.remove_if([columnIndex, conditionValue](auto& a)
                       { return a.at(columnIndex) >= conditionValue; });
        }else if(conditionOperator==">"){
            table->rows.remove_if([columnIndex, conditionValue](auto& a)
                       { return a.at(columnIndex) <= conditionValue; });
        }else{
            log="Error, Where: syntax error, get wrong comparation argument, should be =,< or >";
            return nullptr;
        }

        return table;
    }

    return nullptr;
}