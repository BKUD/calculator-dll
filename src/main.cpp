//
// Created by 79835
//

#include <iostream>
#include <string>

#include "FunctionRegistry.h"
#include "PluginManager.h"

int main() {
    try {
        PluginManager pluginManager("./plugins");
        pluginManager.loadAllPlugins();

        auto& registry = FunctionRegistry::getInstance();
        auto sinFunc = registry.getFunction("sin");
        std::cout << "sin(45) = " << sinFunc({90}) << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
