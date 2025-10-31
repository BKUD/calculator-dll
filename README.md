# Calculator with Dynamic Plugins

## Overview

This is a console-based calculator application capable of evaluating mathematical expressions with standard operators (`+`, `-`, `*`, `/`, `^`, parentheses) and dynamically loaded plugin functions.

Plugins are implemented as DLLs, which are automatically loaded at runtime from the `./plugins` directory. This allows extending the calculator with new functions **without recompiling the main application**.

**Example usage:**

```text
Enter expression: 16 + 4 * (3 - 1)
Output: 24

Enter expression: 2^4 + sin(90)
Output: 18
```



---

## Features

- Standard arithmetic operations: `+`, `-`, `*`, `/`, `^`
- Parentheses for grouping
- Dynamically loaded functions from plugins (e.g., `sin`, `cos`, `ln`, `pow`, `sqrt`, `deg`)
- Error handling for invalid expressions, division by zero, invalid plugin calls
- Extensible architecture: add new functions by creating a plugin DLL

---

## How to Build

1. Clone the repository:

```bash
git clone <repository-url>
cd Calculator
```
2. Create a build directory and run CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```
3. Run the calculator:
```bash
./Calculator.exe # Windows
```

---

## Adding new plugins

1. Create a new plugin source file (e.g., funcmyfunc.cpp) in the plugins/ folder:
```c++
#include <cmath>
#include <stdexcept>

extern "C" __declspec(dllexport)
double plugin_function(double* args, int count) {
    if(count != 1) throw std::runtime_error("myfunc() requires exactly one argument");
    return args[0] * 2; // example function
}

extern "C" __declspec(dllexport)
const char* plugin_name() { return "myfunc"; }

extern "C" __declspec(dllexport)
int plugin_argc() { return 1; }
```
2. Compile the plugin as a DLL:
```c++
# Example with g++
g++ -shared -o plugins/funcmyfunc.dll plugins_src/funcmyfunc.cpp
```
 Restart the calculator. The new function will be automatically loaded and available:
```text
Enter expression: myFunc(5)
Output: 20
```

