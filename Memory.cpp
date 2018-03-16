#include "Memory.h"

Memory::Memory()
{
    for (int i = 0; i < *(&physicalMem[0]+1)-physicalMem[0]; i++)
    {
        this->physicalMem[0][i] = 0;
    }
}

int Memory::readPhysical(int VA)
{
    std::tuple<int, int, int> temp = this->convertVA(VA);
    int s = std::get<0>(temp);
    int p = std::get<1>(temp);
    int w = std::get<2>(temp);
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

int Memory::writePhysical(int VA)
{
    std::tuple<int, int, int> temp = this->convertVA(VA);
    int s = std::get<0>(temp);
    int p = std::get<1>(temp);
    int w = std::get<2>(temp);
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

void Memory::setUseTLB(bool b)
{
    this->useTLB = b;
}

std::tuple<int, int, int> Memory::convertVA(int VA)
{
    std::bitset<32> bitAddress(VA);
    std::string virtualAddress = bitAddress.to_string();
    std::cout << virtualAddress << std::endl;
    std::string tempS, tempP, tempW;
    for (int i = 4; i < 13; i++)
    {
        tempS += virtualAddress[i];
        tempP += virtualAddress[i+9];
        tempW += virtualAddress[i+19];
    }
    tempP += virtualAddress[22];
    std::cout << tempS << "|" << tempP << "|" << tempW << std::endl;
    std::bitset<9> s(tempS);
    std::bitset<10> p(tempP);
    std::bitset<9> w(tempW);

    return std::make_tuple(int(s.to_ulong()), int(p.to_ulong()), int(w.to_ulong()));

}