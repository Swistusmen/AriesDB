#include "Interface/Interface.h"
#include "Interface/ConsoleInterface.h"
#include "Compiler/Compiler.h"
#include "MemoryStorage/DataWarehouse.h"
#include "Logger/Logger.h"
#include <iostream>
#include <filesystem>

void printTable(std::unique_ptr<Table> tab);

int main()
{
    Logger logger("/home/michal/Documents/Programming/Database/Logs/logs.txt",1);
    Compiler compiler(logger);
    DataWarehouse dataWarehouse(logger);
    ConsoleInterface console(logger);
    dataWarehouse.setDeviceStroageLocation("/home/michal/Documents/Programming/Database/source/Tables");

    std::string input{""};
    while ((input=console.userInput(0)) != "exit")
    {
        auto commands = compiler.compile(input);
        auto response = dataWarehouse.executeQuery(std::move(commands));
        if(response==nullptr){
            logger.log("Inernal Database error: could not process query, result is a nullptr",0);
        }
        if(logger.wasQuerySuccessful(0)){
            printTable(std::move(response));
        }else{
            const auto& log=logger.getLog(0);
            for(int i=1;i<log.communicates.size();i++){
                std::cout<<log.communicates[i]<<std::endl;
            }
        }
        logger.endSession(0);
    }
    //this is temporary as I know that if i put exit for nw, there is only one member
    logger.endSession(0);

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