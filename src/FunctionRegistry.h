//
// Created by 79835
//

#ifndef CALCULATOR_FUNCTIONREGISTRY_H
#define CALCULATOR_FUNCTIONREGISTRY_H

#endif //CALCULATOR_FUNCTIONREGISTRY_H

#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

class FunctionRegistry {
public:
    static FunctionRegistry& getInstance();

    void registerFunction(const std::string& name,
                          std::function<double(std::vector<double>)> func);

    std::function<double(std::vector<double>)> getFunction(const std::string& name) const;

private:
    FunctionRegistry() = default;
    std::unordered_map<std::string, std::function<double(std::vector<double>)>> functions;
};
