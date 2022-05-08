#include "Interface/Interface.h"
#include "Interface/ConsoleInterface.h"
#include "Compiler/Compiler.h"
#include "MemoryStorage/DataWarehouse.h"
#include "Logger/Logger.h"
#include <iostream>
#include <filesystem>

int main()
{
    Logger logger("/home/michal/Documents/Programming/Database/Logs/logs.txt",NUMBER_OF_SLOTS);
    Compiler compiler(logger);
    DataWarehouse dataWarehouse(logger);
    ConsoleInterface console(logger);
    dataWarehouse.setDeviceStroageLocation("/home/michal/Documents/Programming/Database/source/Tables");

    std::string input{""};
    while ((input=console.userInput(0)) != "exit")
    {
        auto commands = compiler.compile(input);
        auto response = dataWarehouse.executeQuery(std::move(commands));
        console.handleResponse(response);
        logger.endSession(0);
    }
    //this is temporary as I know that if i put exit for nw, there is only one member
    logger.endSession(0);

    return 0;
}