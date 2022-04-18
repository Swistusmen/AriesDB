#pragma once

#include <iostream>
#include <string>
#include <thread>
#include "../Logger/Logger.h"
#include "../Config.h"
#include "../Common/CommandResult.h"

void printTable(const std::unique_ptr<Table>& tab);

class ConsoleInterface{
    public:
        ConsoleInterface(Logger& _logger);

        std::string userInput(const int _member);
        //TODO:in the future replace with class reposnsible only for handling reposnses, and agreagate such a class within Intefrace classes
        void handleResponse(const CommandResult& );
    private:
        void revertLineToBeginState(std::string& buffer);
        void readLogsHistory(const int member);
        const std::string& getPreviousLog();
        const std::string& getNextLog();
        void removeCharFromConsole();

        Logger& logger;
        std::vector<std::string>logs;

        int logIndex{-1};
        const int arrowUp{65};
        const int arrowDown{66};
        const int backspace{127};
        const int arrowLeft{68};
        const int arrowRight{67};
        const int enter{13};
};