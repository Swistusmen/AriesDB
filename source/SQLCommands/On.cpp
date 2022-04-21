#include "On.h"

On::On(On &&command)
{
    this->arguments = std::move(command.arguments);
}

On &On::operator=(On &&command) noexcept
{
    this->arguments = std::move(command.arguments);
    return *this;
}

On::~On()
{
}

// for now only =
std::vector<std::unique_ptr<Table>> On::execute(std::vector<std::unique_ptr<Table>> &tables)
{
    auto toMerge = std::partition(tables.begin(), tables.end(), [this](auto &table)                      {
        auto found=std::find_if(arguments.begin(),arguments.end(),[&table](auto LongString){
            auto pair=getTableNameAndColumnNameFromArgument(LongString);
            auto tables2=splitString(table->tableName,'*');
            return std::find(tables2.begin(),tables2.end(),pair[0])!=tables2.end();
        });
        return found==arguments.end(); });

    if (tables.end() - toMerge != 2) 
    {
        log="Error, On: found more than 2 matching tables";
        return {};
    }

    std::vector<std::unique_ptr<Table>> tablesToMerge;

    tablesToMerge.push_back(std::move(tables[tables.size() - 1]));
    tables.pop_back();
    tablesToMerge.push_back(std::move(tables[tables.size() - 1]));
    tables.pop_back();

    std::vector<std::array<std::string, 2>> tableAndColumnValues;
    std::transform(arguments.begin(), arguments.end(), std::back_inserter(tableAndColumnValues), getTableNameAndColumnNameFromArgument);

    const int indexOfValueToCompare_1 = getIndexOfColumn(tableAndColumnValues, tablesToMerge[0]);
    const int indexOfValueToCompare_2 = getIndexOfColumn(tableAndColumnValues, tablesToMerge[1]);

    auto output = std::make_unique<Table>(tableAndColumnValues[0][0]+"*"+
    tableAndColumnValues[1][0], "1");
    
    for (auto &it : tablesToMerge[0]->rows)
    {
        auto found = std::find_if(tablesToMerge[1]->rows.begin(), tablesToMerge[1]->rows.end(), [&it, indexOfValueToCompare_1, indexOfValueToCompare_2](auto it2)
                                  { return it2.at(indexOfValueToCompare_2) == it[indexOfValueToCompare_1]; });
        if (found != tablesToMerge[1]->rows.end())
        {
            it.insert(it.end(), found->begin(), found->end());
            output->rows.emplace_back(it);
        }
    }

    for(const auto& it: tablesToMerge[0]->columns){
        output->columns.push_back(it);
    }
    for(const auto& it: tablesToMerge[1]->columns){
        output->columns.push_back(it);
    }
    
    std::vector<std::unique_ptr<Table>> out;
    for (auto &it : tables)
    {
        out.push_back(std::move(it));
    }
    out.push_back(std::move(output));
    tables.clear();
    return out;
}

std::unique_ptr<Table> On::execute(std::unique_ptr<Table>)
{
    return nullptr;
}

void On::addArgument(const std::string& word)
{
    if(word!="="){
        arguments.push_back(word);
    }
}
