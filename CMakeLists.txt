cmake_minimum_required(VERSION 4.0)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32)
        set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()

add_executable(Calculator src/main.cpp
        src/main.cpp
        src/main.cpp
        include/PluginManager.h
        include/FunctionRegistry.h
        include/ExpressionParser.h
        include/Evaluator.h
        src/FunctionRegistry.cpp
        src/PluginManager.cpp
        src/ExpressionParser.cpp
        src/Evaluator.cpp
        )

target_include_directories(Calculator PRIVATE include)

add_custom_command(TARGET Calculator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/plugins $<TARGET_FILE_DIR:Calculator>/plugins
)
