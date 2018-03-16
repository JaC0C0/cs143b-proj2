#include <iostream>
#include "Memory.h"
#include "FileScanner.h"
#include <bitset>

int main()
{
    Memory virtualMemory;
    FileScanner filescan;
    std::vector<std::tuple<int, int, int>> cmdVector = filescan.processCmd();
    if (std::get<0>(cmdVector[0]) == -5)
    {
        virtualMemory.setUseTLB(false);
    }
    cmdVector.erase(cmdVector.begin());
    for (auto cmd : cmdVector)
    {
        /*if (std::get<0>(cmd) == -3)
        {
            switch (std::get<1>(cmd))
            {
                case 0 : virtualMemory.readPhysical(std::get<2>(cmd));
                break;
                case 1 : virtualMemory.writePhysical(std::get<2>(cmd));
                break;
            }
        }*/
    }

/*
    std::bitset<32> foo = 1343423;
    std::string temp = "";
    for (int i = 0; i < 8; i++)
    {
        temp += std::to_string(foo[i]);
    }
    std::bitset<32> thebit(temp);
    std::cout << thebit << std::endl;*/
    std::tuple<int, int, int> temp = virtualMemory.convertVA(3423049);
    std::cout << std::get<0>(temp) << " " << std::get<1>(temp) << " " << std::get<2>(temp) << std::endl;
    std::cout << "Holla" << std::endl;
    return 0;
}