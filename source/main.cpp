#include "Interface/Interface.h"
#include "Compiler/Compiler.h"
#include "MemoryStorage/DataWarehouse.h"

#include <iostream>

#include <filesystem>

void printTable(std::unique_ptr<Table> tab);

int main()
{
    /*Table tab("Shops", "1");
        tab.columns = std::vector<std::string>{"id", "shop", "category", "floor"};
        std::vector<std::string> a{"1", "Rossman", "Beauty", "1"};
        std::vector<std::string> b{"2", "H&M", "Fashion", "1"};
        std::vector<std::string> c{"3", "C&A", "Fashion", "1"};
        std::vector<std::string> d{"4", "NewYorker", "Fashion", "2"};
        std::vector<std::string> e{"5", "Biedronka", "Supermarket", "2"};
        tab.rows.push_back(a);
        tab.rows.push_back(b);
        tab.rows.push_back(c);
        tab.rows.push_back(d);
        tab.rows.push_back(e);
        saveATableIntoATextFile("/home/michal/Documents/Programming/Database/source/","shops.txt",tab);*/

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