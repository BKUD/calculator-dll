//
// Created by 79835
//

#include <complex>
#include <stdexcept>

extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if (count != 1)
        throw std::runtime_error("ln() requires exactly one argument");
    if (args[0] <= 0.0)
        throw std::runtime_error("ln() argument must be positive");

    return std::log(args[0]);
}

extern "C" __declspec(dllexport)
const char* plugin_name() {
    return "ln";
}

extern "C" __declspec(dllexport)
int plugin_argc() {
    return 1;
}