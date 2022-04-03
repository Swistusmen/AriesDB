#include "CommonExecutorHelperFunctions.h"

std::unique_ptr<Table> mergeVectorOfResultTablesIntoOne(std::vector<std::unique_ptr<Table>> &tables)
{
    const int noTables = tables.size();
    if (noTables == 0)
    {
        return nullptr;
    }

    if (noTables == 1)
    {
        return std::move(tables.at(0));
    }

    auto it = tables.begin();
    auto outputTable = std::move(*it);

    int i=0;
    it++;
    
    for (; it != tables.end();it++)
    {
        outputTable->columns.insert(outputTable->columns.end(), (*it)->columns.begin(), (*it)->columns.end());

        for(auto row=outputTable->rows.begin(), add=(*it)->rows.begin();row!=outputTable->rows.end() ;add++,row++){
            row->insert(row->end(),add->begin(),add->end());    
        }

    }

    return outputTable;
}