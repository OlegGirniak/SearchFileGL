#pragma once

#include "pch.h"
#pragma once

#include "pch.h"

namespace fs = std::filesystem;

namespace Lib
{
    std::mutex outputConsoleMutex;

    struct Task
    {
        std::string rootDirectoty;
        std::string searchFileName;
        bool isTaskQuit;
    };

    std::queue<Task> tasks;
    std::mutex tasksMutex;
    std::condition_variable tasksCv;

    bool ifFileIsFound = false;

    void SearchFile(const std::string& rootDir, const std::string& fileName);

    void StartThread();

    void StartSearch(std::string& root, std::string& fileName);
}