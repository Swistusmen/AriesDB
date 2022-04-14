project ("DB")
cmake_minimum_required(VERSION "3.9")

set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(
    Interface
    SQLCommands
    Compiler
    Common 
    MemoryStorage
    MemoryStorage/Pager 
)

add_executable(${PROJECT_NAME}
    main.cpp

    Common/Table.h 
    Common/DBExecResult.h
    Common/DataBaseTable.h 
    Common/DataBaseTable.cpp
    Common/Algorithms.h 
    Common/Algorithms.cpp 
    Common/CommandResult.h 
    Common/CommandResult.cpp 

    Compiler/Grammar.h 
    Compiler/Grammar.cpp
    Compiler/Tokenizer.h 
    Compiler/Tokenizer.cpp 
    Compiler/Parser.h 
    Compiler/Parser.cpp
    Compiler/Compiler.h 
    Compiler/Compiler.cpp
    Compiler/PreCompiledFunctions.h 
    Compiler/PreCompiledFunctions.cpp

    Interface/Interface.h 
    Interface/ConsoleInterface.h
    Interface/ConsoleInterface.cpp

    Logger/Logger.h 
    Logger/Logger.cpp

    MemoryStorage/Pager/OSInterface/FileOperations.h
    MemoryStorage/Pager/OSInterface/FileOperations.cpp
    MemoryStorage/Pager/Pager.h 
    MemoryStorage/DataWarehouse.h
    MemoryStorage/Pager/Pager.cpp
    MemoryStorage/DataWarehouse.cpp 
    MemoryStorage/ReadTaskExecutor.h
    MemoryStorage/ReadTaskExecutor.cpp 
    MemoryStorage/CommonExecutorHelperFunctions.h
    MemoryStorage/CommonExecutorHelperFunctions.cpp
    MemoryStorage/ModifyContentExecutor.h 
    MemoryStorage/ModifyContentExecutor.cpp
    
    SQLCommands/On.cpp 
    SQLCommands/On.h 
    SQLCommands/From.cpp 
    SQLCommands/From.h 
    SQLCommands/Select.cpp 
    SQLCommands/Select.h 
    SQLCommands/Where.cpp 
    SQLCommands/Where.h 
    SQLCommands/Into.h 
    SQLCommands/Into.cpp
    SQLCommands/Update.h 
    SQLCommands/Update.cpp
    SQLCommands/Delete.h 
    SQLCommands/Delete.cpp
    SQLCommands/SQLCommand.h
    SQLCommands/SQLCommandCreator.h 
    SQLCommands/SQLCommandCreator.cpp
)

#target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic -Werror)
