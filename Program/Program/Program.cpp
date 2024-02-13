#include <iostream>
#include <string>
#include <FileLib.h>

int main()
{

    std::string root = "C:";

    std::string searchFile;

    std::cout << "Enter file name: ";

    std::getline(std::cin, searchFile);

    Lib::StartSearch(root, searchFile);

    return 0;

}
