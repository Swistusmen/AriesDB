#include "Update.h"

Update::Update(Update &&command)
{
    conditionColumns=std::move(command.conditionColumns);
    conditionOperators=std::move(command.conditionOperators);
    conditionValues=std::move(command.conditionValues);
    values=std::move(command.values);
    valuesColumns=std::move(command.valuesColumns);
    tableName=std::move(command.tableName);
}

Update &Update::operator=(Update &&command) noexcept
{
    conditionColumns=std::move(command.conditionColumns);
    conditionOperators=std::move(command.conditionOperators);
    conditionValues=std::move(command.conditionValues);
    values=std::move(command.values);
    valuesColumns=std::move(command.valuesColumns);
    tableName=std::move(command.tableName);
    return *this;
}

Update::~Update()
{
}

void Update::addArgument(const std::string &word)
{
    if (noValuesAfterWhichAddToConditionNotArgumentsNorTableName == -1)
    {
        noValuesAfterWhichAddToConditionNotArgumentsNorTableName = std::stoi(word);
        return;
    }
    if (tableName == "")
    {
        tableName = word;
        noValuesAfterWhichAddToConditionNotArgumentsNorTableName--;
    }
    else if (0 == noValuesAfterWhichAddToConditionNotArgumentsNorTableName)
    {
        addToConditional(word);
    }
    else
    {
        addToValues(word);
        noValuesAfterWhichAddToConditionNotArgumentsNorTableName--;
    }
}

void Update::addToConditional(const std::string& word)
{
    if (word == "=" || word == "<" || word == ">")
        {
            conditionOperators.push_back(word);
            return;
        }
        if (conditionValues.size() == conditionColumns.size())
        {
            conditionColumns.push_back(word);
        }
        else
        {
            conditionValues.push_back(word);
        }
}

void Update::addToValues(const std::string& word){
    if (word != "=")
        {

            if (valuesColumns.size() == values.size())
            {
                valuesColumns.push_back(word);
            }
            else
            {
                values.push_back(word);
            }
        }
}


bool Update::execute(DataBaseTable& table)
{
    std::cout<<"UPDATE UPDATE\n";
    return static_cast<bool>(table.findAndUpdate(conditionColumns,conditionOperators,conditionValues,valuesColumns,values));
}