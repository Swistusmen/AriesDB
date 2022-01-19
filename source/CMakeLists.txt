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
)

add_executable(${PROJECT_NAME}
    main.cpp
    Interface/Interface.h 

    Common/Table.h 
    Common/DBExecResult.h

    Compiler/Tokenizer.h 
    Compiler/Tokenizer.cpp 
    Compiler/Parser.h 
    Compiler/Parser.cpp
    Compiler/Compiler.h 
    Compiler/Compiler.cpp

    MemoryStorage/DataWarehouse.h 
    MemoryStorage/DataWarehouse.cpp

    MemoryStorage/Pager/OSInterface/FileOperations.h

    SQLCommands/Creator.h 
    SQLCommands/From.cpp 
    SQLCommands/From.h 
    SQLCommands/FromCreator.h 
    SQLCommands/Select.cpp 
    SQLCommands/Select.h 
    SQLCommands/SelectCreator.h 
    SQLCommands/Where.cpp 
    SQLCommands/Where.h 
    SQLCommands/WhereCreator.h 
    SQLCommands/SQLCommand.h
    SQLCommands/SQLCommandCreator.h 
    SQLCommands/SQLCommandCreator.cpp
)
