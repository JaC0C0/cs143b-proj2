#include "Memory.h"

Memory::Memory()
{
    for (int i = 0; i < *(&physicalMem[0]+1)-physicalMem[0]; i++)
    {
        this->physicalMem[0][i] = 0;
    }
}

int Memory::readPhysical(int s, int p, int w)
{
    if (s > 511 || p > 1023 || w > 511)
    {
        std::cout << "error, out of bounds" << std::endl;
        return -1;
    }
    if (physicalMem[0][s] == -1)
    {
        std::cout << "pf" << std::endl;
        return -1;
    }
    else if (physicalMem[0][s] == 0)
    {
        std::cout << "err" << std::endl;
        return 0;
    }
    else
    {
        int pOffset = 0;
        int pageTableNum = physicalMem[0][s];
        if (p > 511)
        {
            pageTableNum += 1;
            p = p - 512;
        }
        if (physicalMem[pageTableNum][p] == -1)
        {
            std::cout << "pf" << std::endl;
            return -1;
        }
        else if (physicalMem[pageTableNum][p] == 0)
        {
            std::cout << "err" << std::endl;
            return 0;
        }
        else
        {
            // int physicalAddress = physicalMem[pageTableNum + p][w];
            return physicalMem[pageTableNum + p][w];
        }
    }
}

int Memory::writePhysical(int s, int p, int w)
{
    if (s > 511 || p > 1023 || w > 511)
    {
        std::cout << "error, out of bounds" << std::endl;
        return -1;
    }
    else if (physicalMem[0][s] == -1)
    {
        std::cout << "pf" << std::endl;
        return -1;
    }
    else
    {
        if (physicalMem[0][s] == 0)
        {
            //find empty page, set physicalMem[0][s] to new location, proceed
        }
        int pOffset = 0;
        int pageTableNum = physicalMem[0][s];
        if (p > 511)
        {
            pageTableNum += 1;
            p = p - 512;
        }
        if (physicalMem[pageTableNum][p] == -1)
        {
            std::cout << "pf" << std::endl;
            return -1;
        }
        else if (physicalMem[pageTableNum][p] == 0)
        {
            std::cout << "err" << std::endl;
            return 0;
        }
        else
        {
            // int physicalAddress = physicalMem[pageTableNum + p][w];
            return physicalMem[pageTableNum + p][w];
        }
    }
}