//
// Created by 79835
//

#include "PluginManager.h"
#include "FunctionRegistry.h"
#include <filesystem>
#include <iostream>
#include <windows.h>

namespace fs = std::filesystem;

PluginManager::PluginManager(const std::string& dir) : directory(dir) {}

PluginManager::~PluginManager() {
    try {
        unloadAll();
    } catch(...) {
        std::cerr << "Warning: exception during plugin unload\n";
    }
}

void PluginManager::loadAllPlugins() {
    if (!fs::exists(directory)) {
        std::cerr << "Warning: plugins directory does not exist: " << directory << "\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(directory)) {
        if (!entry.is_regular_file()) continue;
        auto ext = entry.path().extension().string();
#ifdef _WIN32
        if (ext == ".dll")
#else
        if (ext == ".so" || ext == ".dylib")
#endif
        {
            try {
                loadPlugin(entry.path().string());
            } catch (const std::exception& e) {
                std::cerr << "Failed to load plugin '" << entry.path().filename().string()
                          << "': " << e.what() << "\n";
            } catch (...) {
                std::cerr << "Unknown error loading plugin '" << entry.path().filename().string() << "'\n";
            }
        }
    }
}

void PluginManager::loadPlugin(const std::string& path) {
#ifdef _WIN32
    HMODULE h = LoadLibraryA(path.c_str());
    if (!h) {
        throw std::runtime_error("LoadLibrary failed");
    }

    using PluginFuncC = double(*)(double*, int);
    using PluginNameC = const char*(*)();
    using PluginArgcC = int(*)();

    auto func = reinterpret_cast<PluginFuncC>(GetProcAddress(h, "plugin_function"));
    auto namef = reinterpret_cast<PluginNameC>(GetProcAddress(h, "plugin_name"));
    auto argcf = reinterpret_cast<PluginArgcC>(GetProcAddress(h, "plugin_argc")); // optional

    if (!func || !namef) {
        FreeLibrary(h);
        throw std::runtime_error("Required exports (plugin_function/plugin_name) missing");
    }

    const char* cname = nullptr;
    try {
        cname = namef();
        if (!cname) throw std::runtime_error("plugin_name returned null");
    } catch (...) {
        FreeLibrary(h);
        throw std::runtime_error("plugin_name() threw or failed");
    }
    std::string fname(cname);

    // если уже есть функция с таким именем — отклоняем плагин
    if (FunctionRegistry::getInstance().hasFunction(fname)) {
        FreeLibrary(h);
        throw std::runtime_error("Function '" + fname + "' already registered");
    }

    // аргументы: если плагин экспортирует plugin_argc use it, иначе require that PluginManager supplies it:
    int argc = 1;
    if (argcf) {
        try { argc = argcf(); } catch (...) { argc = 1; }
    }

    FunctionRegistry::PluginFunc wrapper = [func, fname](const std::vector<double>& args) -> double {
        // plugin_function expects (double*, int)
        double* ptr = nullptr;
        std::vector<double> tmp;
        if (!args.empty()) {
            tmp = args; // make contiguous
            ptr = tmp.data();
        }
        try {
            return func(ptr, (int)args.size());
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Plugin '") + fname + "' error: " + e.what());
        } catch (...) {
            throw std::runtime_error(std::string("Plugin '") + fname + "' unknown error");
        }
    };

    FunctionRegistry::getInstance().registerFunction(fname, wrapper, argc);

    // сохранить handle для unload
    libs.push_back({path, h});
    std::cout << "Loaded plugin: " << fname << " from " << path << "\n";
#else
    // POSIX: dlopen/dlsym/dlclose
    void* h = dlopen(path.c_str(), RTLD_NOW);
    if(!h) throw std::runtime_error(dlerror());

    using PluginFuncC = double(*)(double*, int);
    using PluginNameC = const char*(*)();
    using PluginArgcC = int(*)();

    auto func = reinterpret_cast<PluginFuncC>(dlsym(h, "plugin_function"));
    auto namef = reinterpret_cast<PluginNameC>(dlsym(h, "plugin_name"));
    auto argcf = reinterpret_cast<PluginArgcC>(dlsym(h, "plugin_argc"));

    if(!func || !namef) {
        dlclose(h);
        throw std::runtime_error("Required exports missing");
    }

    const char* cname = namef();
    std::string fname = cname ? cname : "";

    if(FunctionRegistry::getInstance().hasFunction(fname)) {
        dlclose(h);
        throw std::runtime_error("Function '" + fname + "' already registered");
    }

    int argc = 1;
    if(argcf) {
        argc = argcf();
    }

    FunctionRegistry::PluginFunc wrapper = [func, fname](const std::vector<double>& args) -> double {
        std::vector<double> tmp = args;
        double* ptr = tmp.empty() ? nullptr : tmp.data();
        try {
            return func(ptr, (int)args.size());
        } catch (const std::exception& e) {
            throw std::runtime_error(std::string("Plugin '") + fname + "' error: " + e.what());
        } catch (...) {
            throw std::runtime_error(std::string("Plugin '") + fname + "' unknown error");
        }
    };

    FunctionRegistry::getInstance().registerFunction(fname, wrapper, argc);
    libs.push_back({path, h});
    std::cout << "Loaded plugin: " << fname << " from " << path << "\n";
#endif
}

void PluginManager::unloadAll() {
    for (auto &L : libs) {
#ifdef _WIN32
        if (L.handle) FreeLibrary(L.handle);
#else
        if (L.handle) dlclose(L.handle);
#endif
    }
    libs.clear();
}