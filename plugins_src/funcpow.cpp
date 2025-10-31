//
// Created by 79835
//

#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if(count != 2) throw std::runtime_error("pow() requires exactly two arguments");
    return std::pow(args[0], args[1]);
}
extern "C" __declspec(dllexport)
const char* plugin_name() {
    return "pow";
}
extern "C" __declspec(dllexport)
int plugin_argc() {
    return 2;
}
