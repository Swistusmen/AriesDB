project ("DB")
cmake_minimum_required(VERSION "3.9")

set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost 1.74.0 REQUIRED system thread regex)
set(USED_LIBS ${Boost_SYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY})

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
    Interface/WebInterface.h 
    Interface/WebInterface.cpp

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
    MemoryStorage/ModifyStructureExecutor.h 
    MemoryStorage/ModifyStructureExecutor.cpp 

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
    SQLCommands/Create.h 
    SQLCommands/Create.cpp
    
    SQLCommands/SQLCommand.h
    SQLCommands/WriteCommand.h 
    SQLCommands/ReadCommand.h 
    SQLCommands/ReadCommand.cpp 
    SQLCommands/ReorganizeCommand.h

    SQLCommands/SQLCommandCreator.h 
    SQLCommands/SQLCommandCreator.cpp

    TCPServer/Server.h 
    TCPServer/Server.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE ${USED_LIBS})
