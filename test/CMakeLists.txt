cmake_minimum_required(VERSION 3.2.0)
project(Tests)

set(CMAKE_CXX_COMPILER)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

enable_testing()

add_executable(${PROJECT_NAME}
    main.cpp
    Interface/Interface_test.cpp
    SQLCommands/SQLCommandsCreator_test.cpp
    SQLCommands/Select_test.cpp
    SQLCommands/Where_test.cpp
    SQLCommands/From_test.cpp
    SQLCommands/On_test.cpp
    Common/DataBaseTable_test.cpp
    Compiler/Tokenizer_test.cpp
    Compiler/Parser_test.cpp
    MemoryStorage/DataWarehouse_test.cpp
    Mocks/TableMocks.h
    WholeApp/BlackBox.cpp
    )

target_link_libraries(${PROJECT_NAME} ${GTEST_LIBRARIES} pthread)