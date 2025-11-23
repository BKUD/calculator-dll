//
// Created by 79835
//

#ifndef CALCULATOR_PLUGINMANAGER_H
#define CALCULATOR_PLUGINMANAGER_H
#include <memory>
#include <vector>
#include <Windows.h>

#endif //CALCULATOR_PLUGINMANAGER_H

#pragma once
#include <string>

class PluginManager {
public:
    explicit PluginManager(const std::string& directory);
    ~PluginManager();

    PluginManager(const PluginManager&) = delete;
    PluginManager& operator=(const PluginManager&) = delete;

    PluginManager(PluginManager&&) noexcept = default;
    PluginManager& operator=(PluginManager&&) noexcept = default;

    void loadAllPlugins();


private:
    struct LoadedLib {
        std::string path;
#ifdef _WIN32
        HMODULE handle;
#else
        void* handle;
#endif
    };

    std::string directory;
    std::vector<LoadedLib> libs;

    void loadPlugin(const std::string& path);
    void unloadAll();
};
