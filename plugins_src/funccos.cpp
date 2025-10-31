//
// Created by 79835
//

#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if (count != 1)
        throw std::runtime_error("cos() requires exactly one argument");

    return std::cos(args[0]);
}

extern "C" __declspec(dllexport)
const char* plugin_name() {
    return "cos";
}

extern "C" __declspec(dllexport)
int plugin_argc() {
    return 1;
}
