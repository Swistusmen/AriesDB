#include "WebInterface.h"

WebInterface::WebInterface(Logger& _logger):logger(_logger){}

std::string WebInterface::handleResponse(const CommandResult& result )
    {
        switch(result.getResult()){
        case CommandResult::Result::Failure:{
            std::string output{""};
            logger.log("Inernal Database error: could not process query, result is a nullptr",0);
            const auto& log=logger.getLog(0);
            for(int i=1;i<log.communicates.size();i++){
                output+=log.communicates[i];
                output+="\n";
            }
            return output;
        }break;
        case CommandResult::Result::Success:{
            switch (result.getExecutionType())
            {
            case Commands::ExecutionType::READONLY:{
                return stringifyTable(result.getTable());
            }break;
            default:
                return "error\n";
                break;
            }
        }
    }
    return "error\n";
    }
