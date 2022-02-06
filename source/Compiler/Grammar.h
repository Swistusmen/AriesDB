#pragma once
#include <string>
#include "../SQLCommands/Commands.h"

namespace Grammar{
    static unsigned int getValidity(const Commands::Code& code){
        switch(code){
            case Commands::Code::FROM:{
                return 0;
            }break;
            case Commands::Code::WHERE:{
                return 1;
            }break;
            case Commands::Code::SELECT:{
                return 2;
            }
        }
    }
}