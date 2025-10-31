//
// Created by 79835
//

#include "PluginManager.h"
#include "FunctionRegistry.h"
#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <windows.h>

namespace fs = std::filesystem;

PluginManager::PluginManager(const std::string& dir) : directory(dir) {}

void PluginManager::loadAllPlugins() {
    if (!fs::exists(directory)) {
        std::cerr << "Plugins directory does not exist: " << directory << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".dll") {
            try {
                loadPlugin(entry.path().string());
            } catch (const std::exception& e) {
                std::cerr << "Failed to load plugin " << entry.path().filename()
                          << ": " << e.what() << std::endl;
            }
        }
    }
}

void PluginManager::loadPlugin(const std::string &path) {
    HMODULE lib = LoadLibraryA(path.c_str());
    if (!lib) throw std::runtime_error("Failed to load library");

    typedef double (*PluginFunc)(double *, int);
    auto func = (PluginFunc) GetProcAddress(lib, "plugin_function");
    if (!func) {
        FreeLibrary(lib);
        throw std::runtime_error("DLL missing plugin_function export");
    }

    typedef const char * (*PluginNameFunc)();
    auto nameFunc = (PluginNameFunc) GetProcAddress(lib, "plugin_name");
    if (!nameFunc) {
        FreeLibrary(lib);
        throw std::runtime_error("DLL missing plugin_name function export");
    }

    std::string funcName = nameFunc();

    FunctionRegistry::getInstance().registerFunction(funcName, [func](std::vector<double> args) -> double {
        try {
            return func(args.data(), (int) args.size());
        } catch (const std::exception &e) {
            throw std::runtime_error("Error in plugin function: " + std::string(e.what()));
        }}
    );

    std::cout << "Loaded plugin: " << funcName << " from " << path << std::endl;
}
