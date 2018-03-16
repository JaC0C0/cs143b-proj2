#include <iostream>
#include "Memory.h"
#include "FileScanner.h"
#include <bitset>

int main()
{
    // int temp = 4294967295;
    std::bitset<32> temp(4294967295);
    std::cout << temp;
    const unsigned int bitIdentityMap[32] = 
    { 
        0x00000001,
        0x00000002,
        0x00000004,
        0x00000008,
        0x00000010,   
        0x00000020, 
        0x00000040, 
        0x00000080, 
        0x00000100, 
        0x00000200, 
        0x00000400, 
        0x00000800, 
        0x00001000, 
        0x00002000, 
        0x00004000, 
        0x00008000,
        0x00010000,
        0x00020000,
        0x00040000, 
        0x00080000, 
        0x00100000, 
        0x00200000, 
        0x00400000, 
        0x00800000, 
        0x01000000, 
        0x02000000, 
        0x04000000, 
        0x08000000, 
        0x10000000, 
        0x20000000, 
        0x40000000, 
        0x80000000,         
    };















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
    // std::tuple<int, int, int> temp = virtualMemory.convertVA(0);
    // std::cout << std::get<0>(temp) << " " << std::get<1>(temp) << " " << std::get<2>(temp) << std::endl;
    std::cout << "Holla" << std::endl;
    return 0;
}