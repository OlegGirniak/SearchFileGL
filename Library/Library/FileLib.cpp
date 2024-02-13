#include "pch.h"
#include "FileLib.h"


void Lib::SearchFile(const std::string& rootDir, const std::string& fileName)
{
    try
    {
        if (!fs::exists(rootDir) || !fs::is_directory(rootDir))
        {
            return;
        }

        for (const auto& entry : fs::directory_iterator(rootDir))
        {
            if (fs::is_directory(entry))
            {
                try
                {
                    fs::directory_iterator it(entry);
                }
                catch (const fs::filesystem_error& ex)
                {
                    continue;
                }


                {
                    std::lock_guard<std::mutex> lock(tasksMutex);
                    tasks.push({ entry.path().string(), fileName, false });
                }

                tasksCv.notify_one();

            }
            else if (fs::is_regular_file(entry))
            {
                if (entry.path().filename() == fileName)
                {
                    std::lock_guard<std::mutex> lock(outputConsoleMutex);
                    std::cout << "File path: " << entry.path() << '\n';
                    ifFileIsFound = true;
                }
            }
        }
    }
    catch (const std::exception& e)
    {
        //std::cout << "Error: " << e.what() << "\n";
    }
}

void Lib::StartThread()
{
    while (!ifFileIsFound)
    {
        Task task;

        std::unique_lock<std::mutex> lock(tasksMutex);

        tasksCv.wait(lock, [] { return !tasks.empty(); });

        task = tasks.front();

        if (task.isTaskQuit)
        {
            break;
        }

        tasks.pop();

        lock.unlock();

        SearchFile(task.rootDirectoty, task.searchFileName);
    }
}

void Lib::StartSearch(std::string& root, std::string& fileName)
{
    std::vector<std::thread> threads;

    for (int i = 0; i < 8; ++i)
    {
        threads.emplace_back(StartThread);
    }


    {
        std::lock_guard<std::mutex> lock(tasksMutex);
        tasks.push({ root, fileName, false });
    }

    tasksCv.notify_one();


    for (auto& thread : threads)
    {
        thread.join();
    }

    tasksCv.notify_all();
}
