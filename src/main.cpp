//
// Created by 79835
//

#include <iostream>
#include <string>

#include "FunctionRegistry.h"

int main() {
    try {
        auto& registry = FunctionRegistry::getInstance();


        registry.registerFunction("add", [](std::vector<double> args) -> double {
            if (args.size() != 2)
                throw std::invalid_argument("add(x, y) requires exactly 2 arguments");
            return args[0] + args[1];
        });


        auto addFunc = registry.getFunction("add");
        std::cout << "add(5, 4) = " << addFunc({5, 4}) << std::endl;

        registry.registerFunction("add", [](std::vector<double>){ return 0; });
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
