#include <iostream>
#include "Memory.h"
#include "FileScanner.h"

int main()
{
    Memory virtualMemory;
    FileScanner filescan;
    filescan.processCmd();
    std::cout << "Holla" << std::endl;
    return 0;
}