//
// Created by 79835
//

#include <iostream>
#include <string>

#include "../include/Evaluator.h"
#include "../include/FunctionRegistry.h"
#include "../include/PluginManager.h"

int main() {
    try {
        PluginManager pluginManager("../plugins");
        pluginManager.loadAllPlugins();

        Evaluator evaluator;
        std::string expr;
        std::cout << "Enter expression: ";
        std::getline(std::cin, expr);

        double result = evaluator.evaluate(expr);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
