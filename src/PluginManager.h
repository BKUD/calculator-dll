//
// Created by 79835
//

#ifndef CALCULATOR_PLUGINMANAGER_H
#define CALCULATOR_PLUGINMANAGER_H

#endif //CALCULATOR_PLUGINMANAGER_H

#pragma once
#include <string>

class PluginManager {
public:
    explicit PluginManager(const std::string& directory);
    void loadAllPlugins();

private:
    std::string directory;
    void loadPlugin(const std::string& path);
};
