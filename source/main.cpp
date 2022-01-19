#include "Interface/Interface.h"
#include "Compiler/Compiler.h"
#include "Common/Table.h"
#include "MemoryStorage/DataWarehouse.h"
#include "MemoryStorage/Pager/OSInterface/FileOperations.h"
#include <iostream>

#include <filesystem>

void printTable(std::shared_ptr<Table> tab);

int main()
{
    /*
    std::string test = "select shop, category from Shops where id > 3";
    Compiler compiler;
    auto tokens=compiler.compile(test);

    DataWarehouse db;
    
    auto result =db.executeQuery(std::move(tokens));
    printTable(result);*/

    
    

    return 0;
}

void printTable(std::shared_ptr<Table> tab)
{
    std::for_each(tab->columns.begin(), tab->columns.end(), [](auto a)
                  { std::cout << a << " "; });
    std::cout << std::endl;

    std::for_each(tab->rows.begin(), tab->rows.end(), [](auto row)
                  {
                      std::for_each(row.begin(), row.end(), [](auto element)
                                    { std::cout << element << " "; });
                      std::cout << std::endl;
                  });
}