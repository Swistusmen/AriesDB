#include "Interface/Interface.h"
#include "Interface/ConsoleInterface.h"
#include "Compiler/Compiler.h"
#include "MemoryStorage/DataWarehouse.h"
#include "Logger/Logger.h"
#include "TCPServer/Server.h"
#include <iostream>
#include <filesystem>

#if defined(WEB_INTERFACE)
#include "Interface/WebInterface.h"
#endif

int main()
{
    Logger logger("/home/michal/Documents/Programming/Database/Logs/logs.txt",NUMBER_OF_SLOTS);
    Compiler compiler(logger);
    DataWarehouse dataWarehouse(logger);
    dataWarehouse.setDeviceStroageLocation("/home/michal/Documents/Programming/Database/source/Tables");
    std::string input{""};
#if defined(WEB_INTERFACE)
    WebInterface console(logger);
    Server server(9000);
    server.run();
    while(true)
    {
    auto val=server.waitForRequest();
    while(!val.has_value()){
        val=server.waitForRequest();
    }
    input=val.value();
    logger.beginSession(0);
    logger.log(input,0);
#else
    ConsoleInterface console(logger);
    while ((input=console.userInput(0)) != "exit")
    {
#endif
        auto commands = compiler.compile(input);
        auto response = dataWarehouse.executeQuery(std::move(commands));
#if defined(WEB_INTERFACE)
        server.setResponse(console.handleResponse(response));
#else
        console.handleResponse(response);
#endif
        logger.endSession(0);
    }
    logger.endSession(0);

    return 0;
}