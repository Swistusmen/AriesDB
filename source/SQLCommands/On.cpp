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
    auto toMerge = std::partition(tables.begin(), tables.end(), [this](auto &table)
                                  {
        auto found=std::find_if(arguments.begin(),arguments.end(),[&table](auto LongString){
            auto pair=getTableNameAndColumnNameFromArgument(LongString);
            return pair[0]==table->tableName;
        });
        return found==arguments.end(); });

    if (tables.end() - toMerge != 2)
    {
        return {};
    }

    std::vector<std::unique_ptr<Table>> tablesToMerge;

    tablesToMerge.push_back(std::move(tables[tables.size() - 1]));
    tables.pop_back();
    tablesToMerge.push_back(std::move(tables[tables.size() - 1]));
    tables.pop_back();

    std::vector<std::array<std::string, 2>> tableAndColumnValues;
    std::transform(arguments.begin(), arguments.end(), std::back_inserter(tableAndColumnValues), getTableNameAndColumnNameFromArgument);

    std::unique_ptr<Table> a;
    const int indexOfValueToCompare_1 = getIndexOfColumn(tableAndColumnValues, tablesToMerge[0]);
    const int indexOfValueToCompare_2 = getIndexOfColumn(tableAndColumnValues, tablesToMerge[1]);

    auto output = std::make_unique<Table>(tableAndColumnValues[0][0], "1");

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

    std::vector<std::unique_ptr<Table>> out;
    for (auto &it : tables)
    {
        out.push_back(std::move(it));
    }
    out.push_back(std::move(output));
    tables.clear();
    return out;
}

//this should be moved to common space for SQL Commands
int On::getIndexOfColumn(const std::vector<std::array<std::string, 2>> &tableColumn, std::unique_ptr<Table> &table)
{
    if (table == nullptr)
    {
        return -1;
    }
    int mapIndex = table->tableName == tableColumn[0][0] ? 0 : 1;
    auto found = std::find(table->columns.begin(), table->columns.end(), tableColumn[mapIndex][1]);
    if (found == table->columns.end())
    {
        return -1;
    }
    return found - table->columns.begin();
}

// this should be moved to common space for SQL Commands
std::array<std::string, 2> getTableNameAndColumnNameFromArgument(const std::string &argument)
{
    size_t npos = argument.find_last_of('.');
    std::array<std::string, 2> result;
    result[0] = argument.substr(0, npos);
    result[1] = argument.substr(npos + 1, argument.size() - 1);
    return result;
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
