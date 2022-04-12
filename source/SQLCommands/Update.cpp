#include "Update.h"

Update::Update(Update &&command)
{
    this->arguments = std::move(command.arguments);
}

Update &Update::operator=(Update &&command) noexcept
{
    this->arguments = std::move(command.arguments);
    return *this;
}

Update::~Update()
{
}

std::unique_ptr<Table> Update::execute(std::unique_ptr<Table>)
{
    return nullptr;
}

std::vector<std::unique_ptr<Table>> Update::execute(const std::vector<DataBaseTable> &vectorOfTables)
{
    return {};
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

const std::string &Update::getTableName()
{
    return tableName;
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