cmake_minimum_required(VERSION 4.0)
project(Calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Calculator src/main.cpp
        src/main.cpp
        src/main.cpp
        src/PluginManager.h
        src/FunctionRegistry.h
        src/ExpressionParser.h
        src/Evaluator.h
        src/FunctionRegistry.cpp
        src/PluginManager.cpp
        src/ExpressionParser.cpp
        src/Evaluator.cpp
        )


set(PLUGIN_OUTPUT_DIR ${CMAKE_BINARY_DIR}/plugins)
file(MAKE_DIRECTORY ${PLUGIN_OUTPUT_DIR})

add_library(funcsin SHARED plugins_src/funcsin.cpp)
set_target_properties(funcsin PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})

add_library(funcdeg SHARED plugins_src/funcdeg.cpp)
set_target_properties(funcdeg PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})

add_library(funcln SHARED plugins_src/funcln.cpp)
set_target_properties(funcln PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})

add_library(funccos SHARED plugins_src/funccos.cpp
        plugins_src/funcpow.cpp
        plugins_src/funcsqrt.cpp)
set_target_properties(funccos PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR})