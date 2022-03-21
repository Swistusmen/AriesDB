#pragma once

#include <iostream>
#include <string>
#include <thread>
#include "../Logger/Logger.h"

//IMPROVE: can work more nicely- ending signs when backspace or enter

class ConsoleInterface{
    public:
        ConsoleInterface(Logger& _logger);

        std::string userInput(const int _member);
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
        const int enter{13};
};