//
// Created by 79835
//

#include <math.h>
#include <stdexcept>


extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if (count != 1)
        throw std::runtime_error("sin() requires exactly one argument");

    // sin ожидает радианы
    return std::sin(args[0]);
}

extern "C" __declspec(dllexport)
const char* plugin_name() {
    return "sin";
}

extern "C" __declspec(dllexport)
int plugin_argc() {
    return 1;
}
