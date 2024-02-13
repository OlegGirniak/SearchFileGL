#pragma once

#include "pch.h"

namespace fs = std::filesystem;

namespace Lib
{
    void SearchFile(const std::string& rootDir, const std::string& fileName);

    void StartThread();

    void StartSearch(std::string& root, std::string& fileName);
}