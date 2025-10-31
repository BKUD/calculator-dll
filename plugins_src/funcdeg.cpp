//
// Created by 79835
//

#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if (count != 1)
        throw std::runtime_error("deg() requires exactly one argument");


    return args[0] * (180.0 / M_PI);
}

extern "C" __declspec(dllexport)
const char* plugin_name() {
    return "deg";
}

extern "C" __declspec(dllexport)
int plugin_argc() {
    return 1;
}
