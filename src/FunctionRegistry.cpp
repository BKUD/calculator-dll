//
// Created by 79835
//

#include "../include/FunctionRegistry.h"
#include <stdexcept>

FunctionRegistry& FunctionRegistry::getInstance() {
    static FunctionRegistry instance;
    return instance;
}

void FunctionRegistry::registerFunction(const std::string& name, PluginFunc func, int argCount) {
    functions[name] = {func, argCount};
}

bool FunctionRegistry::hasFunction(const std::string& name) const {
    return functions.find(name) != functions.end();
}

FunctionRegistry::PluginFunc FunctionRegistry::getFunction(const std::string& name) const {
    auto it = functions.find(name);
    if(it == functions.end()) throw std::runtime_error("Unknown function: " + name);
    return it->second.func;
}

int FunctionRegistry::getArgCount(const std::string& name) const {
    auto it = functions.find(name);
    if(it == functions.end()) throw std::runtime_error("Unknown function: " + name);
    return it->second.argCount;
}
