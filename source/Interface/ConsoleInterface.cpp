#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface(Logger &_logger) : logger(_logger){};

std::string ConsoleInterface::userInput(const int _member)
{
    readLogsHistory(_member);
    std::string buffer{""};
    std::cout<<"db > ";
    while (true)
    {
        system("stty raw");
        char input = getchar();
        
        if (input == arrowUp)
        {
            revertLineToBeginState(buffer);
            buffer=getPreviousLog();
            std::cout<<buffer;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else if (input == arrowDown)
        {
            revertLineToBeginState(buffer);
            buffer=getNextLog();
            std::cout<<buffer;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        else if(input==backspace){
            if(!buffer.empty()){
            removeCharFromConsole();
            removeCharFromConsole();
            removeCharFromConsole();
            buffer.pop_back();
            }else{
            removeCharFromConsole();
            removeCharFromConsole();
            }
            
        }
        else if(input==enter){
            system("stty cooked");
            removeCharFromConsole();
            removeCharFromConsole();
            break;
        }
        else
        {
            buffer += input;
        }
        system("stty cooked");
    }
    
    std::cout<<"\n";
    system("stty cooked");
    logIndex=-1;
    logger.beginSession(_member);
    logger.log(buffer, _member);

    return buffer;
}

void ConsoleInterface::revertLineToBeginState(std::string& buffer)
{
    while(!buffer.empty())
    {
        removeCharFromConsole();
        buffer.pop_back();
    }
}

void ConsoleInterface::readLogsHistory(const int member)
{
    logs.clear();
    logs=logger.getHistory(member);
}

const std::string &ConsoleInterface::getPreviousLog()
{
    if(logs.empty()){
        return "";
    }
    if(logIndex==-1){
        logIndex=logs.size()-1;
        return logs[logIndex];
    }
    logIndex--;
    return logs[logIndex];
}

const std::string &ConsoleInterface::getNextLog()
{
    if(logs.empty()){
        return "";
    }
    if(logIndex==-1){
        logIndex=logs.size()-1;
        return logs[logIndex];
    }
    if(logIndex>=logs.size()){
        logIndex=0;
        return logs[logIndex];
    }
    logIndex++;
    return logs[logIndex];
}

void ConsoleInterface::removeCharFromConsole()
{
    std::cout << "\x1B[1D";
    std::cout << "\x1B[1P";
}