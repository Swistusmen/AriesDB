#pragma once

namespace Commands{
    
    enum class ExecutionType{
        READONLY, 
        MODIFY_CONTENT, //only 1 comman is created from this, the rest is precompile
        MODIFY_STRUCTURE,
    };
}