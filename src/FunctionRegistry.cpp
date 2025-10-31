//
// Created by 79835
//

#include <functional>
#include <string>
#include "FunctionRegistry.h"
#include <stdexcept>

FunctionRegistry& FunctionRegistry::getInstance() {
    static FunctionRegistry instance;
    return instance;
}

void FunctionRegistry::registerFunction(const std::string& name, std::function<double(std::vector<double>)> func) {
    if (functions.count(name)) {
        throw std::runtime_error("Function '" + name + "' already registred");
    }
    functions[name] = func;
}

std::function<double(std::vector<double>)> FunctionRegistry::getFunction(const std::string& name) const {
    auto it = functions.find(name);
    if (it == functions.end()) {
        throw std::runtime_error("Function '" + name + "' not found");
    }
    return it->second;
}