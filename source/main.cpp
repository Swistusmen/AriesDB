#include "Interface/Interface.h"
#include "Compiler/Compiler.h"
#include "MemoryStorage/DataWarehouse.h"

#include <iostream>

#include <filesystem>

void printTable(std::unique_ptr<Table> tab);

int main()
{
    Compiler compiler;
    DataWarehouse dataWarehouse;
    dataWarehouse.setDeviceStroageLocation("/home/michal/Documents/Programming/Database/source/Tables");
    std::string input = takeInputFromKeyboard();
    while (input != "exit")
    {
        auto commands = compiler.compile(input);
        auto response = dataWarehouse.executeQuery(std::move(commands));
        printTable(std::move(response));
        input = takeInputFromKeyboard();
    }
    return 0;
}

void printTable(std::unique_ptr<Table> tab)
{
    std::for_each(tab->columns.begin(), tab->columns.end(), [](auto a)
                  { std::cout << a << " "; });
    std::cout << std::endl;

    std::for_each(tab->rows.begin(), tab->rows.end(), [](auto row)
                  {
                      std::for_each(row.begin(), row.end(), [](auto element)
                                    { std::cout << element << " "; });
                      std::cout << std::endl; });
}