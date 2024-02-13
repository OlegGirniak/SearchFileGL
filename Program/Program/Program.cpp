#include <iostream>
#include <FileLib.h>

int main()
{

    std::string root = "C:";

    std::string searchFile;

    std::cout << "Enter file name: ";

    std::cin >> searchFile;

    Lib::StartSearch(root, searchFile);

    return 0;

}
