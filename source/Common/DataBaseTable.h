#pragma once
#include "Table.h"
#include "make_comparator.h"
#include "Algorithms.h"
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <iostream>
#include <memory>

class DataBaseTable
{
public:
    //column name, operator, value
    using conds = std::tuple<std::string, std::string, std::string>;

    DataBaseTable() = default;
    DataBaseTable(Table &&);
    DataBaseTable(DataBaseTable &&);
    DataBaseTable(const Table &) = delete;
    DataBaseTable &operator=(const DataBaseTable &) = delete;
    DataBaseTable &operator=(DataBaseTable &&);
    ~DataBaseTable();

    const std::string &getTableName() const { return table.tableName; };
    const std::vector<std::string> &getColumns() const { return table.columns; };
    const Table &getTableDataForReadOnly() const { return table; };
    const auto &getLastModificationDate() const { return lastChangedDate; };

    void addRow(std::vector<std::string> &&vec);
    int findAndRemoveIfEquals(const std::vector<std::string> &columnNames, const std::vector<std::string> &operators, const std::vector<std::string> &values);
    int findRowsAndUpdate(const std::vector<std::string> &columnNames, const std::vector<std::string> &operators,
                          const std::vector<std::string> &valuesToCompare, const std::vector<std::string> &newValues);
    int findAndUpdate(const std::vector<std::string> &conditionalColumnNames, const std::vector<std::string> &operators,
        const std::vector<std::string> &conditionalValues, const std::vector<std::string> &columnsToUpdate,const std::vector<std::string> &newValues);
   // std::vector<std::vector<const std::string>> findToToModifyAndUpdateWasChanged(const std::vector<std::pair<std::string, std::string>> &conditions);

private:
    std::vector<std::list<std::vector<std::string>>::iterator> findRowsMatchingTheCriteria(std::vector<int> &&indexes, const std::vector<std::string> &operators, const std::vector<std::string> &valuesToCompareWith);
    std::vector<int> getColumnIndexes(const std::vector<std::string> &);
    std::chrono::time_point<std::chrono::system_clock> lastChangedDate;

    std::mutex modificationMutex;
    Table table;
};


int getIndexOfColumn(const std::vector<std::array<std::string, 2>> &tableColumn, std::unique_ptr<Table> &table);