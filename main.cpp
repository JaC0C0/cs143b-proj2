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
        //If first value is "-3", implies that the commands are VA translations to PA for respective 
        //read or write functions
        if (std::get<0>(cmd) == -3)
        {
            switch (std::get<1>(cmd))
            {
                case 0 : virtualMemory.readPhysical(std::get<2>(cmd));
                break;
                case 1 : virtualMemory.writePhysical(std::get<2>(cmd));
                break;
            }
        }
        //First value as "-2" implies that segment starts at get<1> and the page table starts at
        //address get<2> 
        else if (std::get<0>(cmd) == -2)
        {
            virtualMemory.initialize(std::get<1>(cmd), std::get<2>(cmd));
        }
        //First value as any positive integer implies that page get<0> of segment <get1> starts at 
        //address get<2>
        else
        {
            virtualMemory.initialize(std::get<0>(cmd), std::get<1>(cmd), std::get<2>(cmd));
        }
    }

    std::tuple<int, int, int> temp = virtualMemory.convertVA(1048576);
    std::tuple<int, int, int> temp1 = virtualMemory.convertVA(1048586);
    std::tuple<int, int, int> temp2 = virtualMemory.convertVA(1049088);

    std::cout << std::get<0>(temp) << " " << std::get<1>(temp) << " " << std::get<2>(temp) << std::endl;
    std::cout << std::get<0>(temp1) << " " << std::get<1>(temp1) << " " << std::get<2>(temp1) << std::endl;
    std::cout << std::get<0>(temp2) << " " << std::get<1>(temp2) << " " << std::get<2>(temp2) << std::endl;
    std::cout << "Holla" << std::endl;
















        // int temp = 4294967295;
    // std::bitset<32> temp(4294967295);
    // std::cout << temp;
    // const unsigned int bitIdentityMap[32] = 
    // { 
    //     0x00000001,
    //     0x00000002,
    //     0x00000004,
    //     0x00000008,
    //     0x00000010,   
    //     0x00000020, 
    //     0x00000040, 
    //     0x00000080, 
    //     0x00000100, 
    //     0x00000200, 
    //     0x00000400, 
    //     0x00000800, 
    //     0x00001000, 
    //     0x00002000, 
    //     0x00004000, 
    //     0x00008000,
    //     0x00010000,
    //     0x00020000,
    //     0x00040000, 
    //     0x00080000, 
    //     0x00100000, 
    //     0x00200000, 
    //     0x00400000, 
    //     0x00800000, 
    //     0x01000000, 
    //     0x02000000, 
    //     0x04000000, 
    //     0x08000000, 
    //     0x10000000, 
    //     0x20000000, 
    //     0x40000000, 
    //     0x80000000,         
    // };

    return 0;
}