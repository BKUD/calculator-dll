//
// Created by 79835
//


#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if (count != 1)
        throw std::runtime_error("sqrt() requires exactly one argument");
    if (args[0] < 0)
        throw std::runtime_error("sqrt() domain error: negative value");
    return std::sqrt(args[0]);
}

extern "C" __declspec(dllexport)
const char* plugin_name() {
    return "sqrt";
}

extern "C" __declspec(dllexport)
int plugin_argc() {
    return 1;
}