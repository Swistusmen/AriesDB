#include "DataBaseTable.h"

DataBaseTable::DataBaseTable(DataBaseTable &&dbTable)
{
    lastChangedDate = std::move(dbTable.lastChangedDate);
    table = dbTable.table;
}

DataBaseTable::DataBaseTable(Table &&tab)
{
    table = std::move(tab);
}

DataBaseTable &DataBaseTable::operator=(DataBaseTable &&tab)
{
    lastChangedDate = std::move(tab.lastChangedDate);
    table = std::move(tab.table);
    return *this;
}

DataBaseTable::~DataBaseTable()
{
}

void DataBaseTable::addRow(std::vector<std::string> &&vec)
{
    table.rows.push_back(std::move(vec));
}

int DataBaseTable::findAndRemoveIfEquals(const std::vector<std::string> &columnNames, const std::vector<std::string> &operators, const std::vector<std::string> &values)
{
    std::vector<int> columnIndexes = getColumnIndexes(columnNames);

    auto toDelete = findRowsMatchingTheCriteria(std::move(columnIndexes), operators, values);

    int noDeletions = 0;
    for (auto &it : toDelete)
    {
        try
        {
            std::lock_guard<std::mutex>lock(modificationMutex);
            table.rows.erase(it);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }
        noDeletions++;
        lastChangedDate = std::chrono::system_clock::now();
    }

    return noDeletions;
}

int DataBaseTable::findRowsAndUpdate(const std::vector<std::string> &columnNames, const std::vector<std::string> &operators,
                                     const std::vector<std::string> &valuesToCompare, const std::vector<std::string> &newValues)
{
    std::vector<int> columnIndexes = getColumnIndexes(columnNames);
    std::vector<int> copyOfIndexes = columnIndexes;
    auto toUpdate = findRowsMatchingTheCriteria(std::move(columnIndexes), operators, valuesToCompare);

    int updates = 0;
    for (auto &it : toUpdate)
    {
        try
        {
            std::vector<std::string> copyOfRow = *it;
            const int noNewValues = newValues.size();
            for (int i = 0; i < noNewValues; i++)
            {
                copyOfRow[copyOfIndexes[i]] = newValues[i];
            }
            std::lock_guard<std::mutex>lock(modificationMutex);
            *it = copyOfRow;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }
        updates++;
        lastChangedDate = std::chrono::system_clock::now();
    }

    return updates;
}

int DataBaseTable::findAndUpdate(const std::vector<std::string> &conditionalColumnNames, const std::vector<std::string> &operators,
        const std::vector<std::string> &conditionalValues, const std::vector<std::string> &columnsToUpdate,const std::vector<std::string> &newValues)
{
    std::vector<int> columnIndexes = getColumnIndexes(conditionalColumnNames);
    std::vector<int> copyOfIndexes = columnIndexes;
    auto toUpdate = findRowsMatchingTheCriteria(std::move(columnIndexes), operators, conditionalValues);
    std::vector<int> updateIndexes = getColumnIndexes(columnsToUpdate);

    int updates = 0;
    for (auto &it : toUpdate)
    {
        try
        {
            std::vector<std::string> copyOfRow = *it;
            const int noNewValues = newValues.size();
            for (int i = 0; i < noNewValues; i++)
            {
                copyOfRow[updateIndexes[i]] = newValues[i];
            }
            std::lock_guard<std::mutex>lock(modificationMutex);
            *it = copyOfRow;
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            continue;
        }
        updates++;
        lastChangedDate = std::chrono::system_clock::now();
    }

    return updates;
}

std::vector<int> DataBaseTable::getColumnIndexes(const std::vector<std::string> &columnNames) 
{
    std::vector<int> columnIndexes;
    std::transform(columnNames.begin(), columnNames.end(), std::back_inserter(columnIndexes), [this](auto name) mutable
                   { return std::find(this->table.columns.begin(), this->table.columns.end(), name) -
                             this->table.columns.begin(); });           
    return columnIndexes;
}

std::vector<std::list<std::vector<std::string>>::iterator> DataBaseTable::findRowsMatchingTheCriteria(std::vector<int> &&indexes, const std::vector<std::string> &operators, const std::vector<std::string> &valuesToCompareWith)
{
    make_comparator make_compar;
    auto comparator = make_compar(std::move(indexes), operators, valuesToCompareWith);

    auto it = table.rows.begin();
    std::vector<std::list<std::vector<std::string>>::iterator> toOperateOn;
    for(auto it=table.rows.begin();it!=table.rows.end();it++){
        if(comparator(*it)){
            toOperateOn.push_back(it);
        }
    }
    
    return toOperateOn;
}
