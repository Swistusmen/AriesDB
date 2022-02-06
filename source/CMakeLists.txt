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
    Interface/Interface.h 

    Common/Table.h 
    Common/DBExecResult.h
    Common/DataBaseTable.h 
    Common/DataBaseTable.cpp

    Compiler/Tokenizer.h 
    Compiler/Tokenizer.cpp 
    Compiler/Parser.h 
    Compiler/Parser.cpp
    Compiler/Compiler.h 
    Compiler/Compiler.cpp

    MemoryStorage/Pager/OSInterface/FileOperations.h
    MemoryStorage/Pager/OSInterface/FileOperations.cpp
    MemoryStorage/Pager/Pager.h 
    MemoryStorage/DataWarehouse.h
    MemoryStorage/Pager/Pager.cpp
    MemoryStorage/DataWarehouse.cpp 
    
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
