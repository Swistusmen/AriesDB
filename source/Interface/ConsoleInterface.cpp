#include "ConsoleInterface.h"

ConsoleInterface::ConsoleInterface(Logger &_logger) : logger(_logger){};

std::string ConsoleInterface::userInput(const int _member)
{
#ifdef RELEASE_CLI
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
        else if(input==arrowLeft){
            removeCharFromConsole();
            removeCharFromConsole();
            removeCharFromConsole();
            removeCharFromConsole();
            std::cout << "\x1B[1D";
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
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

    std::cout<<buffer<<std::endl;
    return buffer;
#else
    std::cout << "db > ";
    std::string input;
    std::getline(std::cin,input);
    logger.beginSession(_member);
    logger.log(input, _member);
    return input;
#endif
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

std::string ConsoleInterface::getPreviousLog()
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

std::string ConsoleInterface::getNextLog()
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

void ConsoleInterface::handleResponse(const CommandResult& _result)
{
    switch(_result.getResult()){
        case CommandResult::Result::Failure:{
            logger.log("Inernal Database error: could not process query, result is a nullptr",0);
            const auto& log=logger.getLog(0);
            for(int i=1;i<log.communicates.size();i++){
                std::cout<<log.communicates[i]<<std::endl;
            }
        }break;
        case CommandResult::Result::Success:{
            switch (_result.getExecutionType())
            {
            case Commands::ExecutionType::READONLY:{
                printTable(_result.getTable());
            }break;
            default:
                break;
            }
        }
    }
}

void printTable(const std::unique_ptr<Table>& tab)
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