//
// Created by 79835
//

#pragma once
#include <string>
#include <unordered_map>
#include <functional>
#include <vector>

class FunctionRegistry {
public:
    using PluginFunc = std::function<double(const std::vector<double>&)>;

    static FunctionRegistry& getInstance();

    void registerFunction(const std::string& name, PluginFunc func, int argCount = 1);
    bool hasFunction(const std::string& name) const;
    PluginFunc getFunction(const std::string& name) const;
    int getArgCount(const std::string& name) const;

    void clearAllFunctions() {
        functions.clear();
    };

private:
    FunctionRegistry() = default;

    struct FuncInfo {
        PluginFunc func;
        int argCount;
    };

    std::unordered_map<std::string, FuncInfo> functions;
};
