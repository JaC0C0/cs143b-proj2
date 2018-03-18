#include <iostream>
#include "Memory.h"
#include "FileScanner.h"
#include <bitset>
#include <fstream>

int main()
{
    Memory virtualMemory;
    FileScanner filescan;
    std::vector<std::tuple<int, int, int>> cmdVector = filescan.processCmd();
    std::ofstream outfile;
    if (std::get<0>(cmdVector[0]) == -5)
    {
        virtualMemory.setUseTLB(false);
        outfile.open("32422520.txt");
    }
    else
    {
        outfile.open("32422520_tlb.txt");
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
                case 0 : outfile << virtualMemory.readPhysical(std::get<2>(cmd)) << " ";
                break;
                case 1 : outfile << virtualMemory.writePhysical(std::get<2>(cmd)) << " ";
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
    outfile.close();
    return 0;
}