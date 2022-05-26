#pragma once
#include <iostream>
#include <string>
#include "../Common/CommandResult.h"
#include "ConsoleInterface.h"
#include "../Logger/Logger.h"

class WebInterface{
    public:
        WebInterface(Logger& );
        std::string handleResponse(const CommandResult& );

    private:
        Logger& logger;
};