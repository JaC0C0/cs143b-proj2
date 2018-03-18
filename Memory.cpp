#include "Memory.h"

//Constructor
Memory::Memory()
{
    this->bitMap.reset();
    this->bitMap.set(0);
    for (int i = 0; i < 4; i++)
    {
        this->TLB.push_back(std::make_tuple(i, "", -1));
    }
}

//Initializes Memory with given inputs.
void Memory::initialize(int s, int f)
{
    this->physicalMem[s] = f;
    if (f > 0)
    {
        this->bitMap.set(f / 512);
        this->bitMap.set((f / 512) + 1);
    }
}

void Memory::initialize(int p, int s, int f)
{
    this->physicalMem[this->physicalMem[s] + p] = f;
    if (f > 0)
    {
        this->bitMap.set(f / 512);
    }
}

//Read operation to the respective virtual address
std::string Memory::readPhysical(int VA)
{
    std::string textOutput = "";
    std::tuple<int, int, int> temp = this->convertVA(VA);
    int s = std::get<0>(temp);
    int p = std::get<1>(temp);
    int w = std::get<2>(temp);
    if (useTLB)
    {
        int PA = this->checkTLB(VA);
        if (PA != -2)
        {
            this->updateTLB(VA, PA);
            return "h " + std::to_string(PA + w);
        }
        textOutput += "m ";
    }
    if (this->physicalMem[s] == -1)
    {
        textOutput += "pf";
        return textOutput;
    }
    else if (this->physicalMem[s] == 0)
    {
        textOutput += "err";
        return textOutput;
    }
    else
    {
        int pageTableNum = this->physicalMem[s];
        if (physicalMem[pageTableNum + p] == -1)
        {
            textOutput += "pf";
            return textOutput;
        }
        else if (physicalMem[pageTableNum + p] == 0)
        {
            textOutput += "err";
            return textOutput;
        }
        else
        {
            if (useTLB) { this->updateTLB(VA, physicalMem[pageTableNum + p]); }
            textOutput += std::to_string(physicalMem[pageTableNum + p]+ w);
            return textOutput;
        }
    }
}

//Write operation to the virtual address
std::string Memory::writePhysical(int VA)
{
    std::string textOutput = "";
    std::tuple<int, int, int> temp = this->convertVA(VA);
    int s = std::get<0>(temp);
    int p = std::get<1>(temp);
    int w = std::get<2>(temp);
    if (useTLB)
    {
        int PA = this->checkTLB(VA);
        if (PA != -2)
        {
            return "h " + std::to_string(PA + w);
        }
        textOutput += "m ";
    }
    if (physicalMem[s] == -1)
    {
        textOutput += "pf";
        return textOutput;
    }
    else
    {
        //Create blank page
        if (physicalMem[s] == 0)
        {
            int freeFrame = this->findDoubleFreeFrame();
            this->physicalMem[s] = freeFrame;
        }
        int pageTableNum = physicalMem[s];
        if (physicalMem[pageTableNum + p] == -1)
        {
            textOutput += "pf";
            return textOutput;
        }
        else if (physicalMem[pageTableNum + p] == 0)
        {
            int freeFrame = findFreeFrame();
            this->physicalMem[pageTableNum + p] = freeFrame;
            textOutput += std::to_string(physicalMem[pageTableNum + p] + w);
            if (useTLB) { this->updateTLB(VA, physicalMem[pageTableNum + p]); }
            return textOutput;
        }
        else
        {
            if (useTLB) { this->updateTLB(VA, physicalMem[pageTableNum + p]); }
            textOutput += std::to_string(physicalMem[pageTableNum + p] + w);
            return textOutput; 
        }
    }
}

void Memory::setUseTLB(bool b)
{
    this->useTLB = b;
}

//Converts a 32-bit integer to a tuple representing Segment, Page, and Page offset
std::tuple<int, int, int> Memory::convertVA(int VA)
{
    std::bitset<32> bitAddress(VA);
    std::string virtualAddress = bitAddress.to_string();
    std::string tempS, tempP, tempW;
    for (int i = 4; i < 13; i++)
    {
        tempS += virtualAddress[i];
        tempP += virtualAddress[i+9];
        tempW += virtualAddress[i+19];
    }
    tempP += virtualAddress[22];
    std::bitset<9> s(tempS);
    std::bitset<10> p(tempP);
    std::bitset<9> w(tempW);
    return std::make_tuple(int(s.to_ulong()), int(p.to_ulong()), int(w.to_ulong()));

}

//Toggles respective bit and returns boolean to inform of the type of change
int Memory::findDoubleFreeFrame()
{
    for (int i = 0; i < 1023; i++)
    {
        if (bitMap.test(i) == false && bitMap.test(i + 1) == false)
        {
            bitMap.set(i);
            bitMap.set(i + 1);
            return i * 512;
        }
    }
    return -1;
}

int Memory::findFreeFrame()
{
    for (int i = 0; i < 1024; i++)
    {
        if (bitMap.test(i) == false) { bitMap.set(i); return i * 512;}
    }
    return -1;
}

static bool compareTLB(std::tuple<int, std::string, int> i, std::tuple<int, std::string, int> j)
{
    return std::get<0>(i) < std::get<0>(j);
}

//Returns Physical Address of VA if stored in TLB, if not, updates TLB with PA 
//and returns "-2"
int Memory::checkTLB(int VA)
{
    std::tuple<int, int, int> temp = convertVA(VA);
    std::bitset<9> s(std::get<0>(temp));
    std::bitset<10> p(std::get<1>(temp));
    std::bitset<9> w(std::get<2>(temp));
    std::string page = s.to_string() + p.to_string();
    for (int i = 0; i < 4; i++)
    {
        if (std::get<1>(this->TLB[i]) == page)
        {
            int PA = std::get<2>(this->TLB[i]);
            int rank = std::get<0>(this->TLB[i]);
            for (int j = 0; j < 4; j++)
            {
                if (std::get<0>(this->TLB[j]) > rank)
                {
                    std::get<0>(this->TLB[j]) -= 1;
                }
            }
            std::get<0>(this->TLB[i]) = 3;
            std::sort(this->TLB.begin(), this->TLB.end(), compareTLB);
            return PA;
        }
    }
    
    return -2;
}

void Memory::updateTLB(int VA, int PA)
{
    std::tuple<int, int, int> temp = convertVA(VA);
    std::bitset<9> s(std::get<0>(temp));
    std::bitset<10> p(std::get<1>(temp));
    std::bitset<9> w(std::get<2>(temp));
    std::string page = s.to_string() + p.to_string();
    bool skip = false;
    for (int g = 0; g < 4; g++)
    {
        if (std::get<1>(this->TLB[g]) == page)
        {
            this->checkTLB(VA);
            skip = true;
        }
    }
    if (!skip)
    {
        this->TLB.erase(this->TLB.begin());
        for (int h = 0; h < 4; h++)
        {
            if (std::get<0>(this->TLB[h]) == 0)
            {
                this->TLB.erase(this->TLB.begin() + h);
            }
        }
        for (int i = 0; i < 3; i++)
        {
            std::get<0>(this->TLB[i]) -= 1;
        }
        this->TLB.push_back(std::make_tuple(3, page, PA));
        std::string temp2 = "";
        for (int i = 0; i<4; i++)
        {
            temp2 += std::get<1>(this->TLB[i]) + " : " + std::to_string(std::get<2>(this->TLB[i])) + " | ";
        }
        std::sort(this->TLB.begin(), this->TLB.end(), compareTLB);
    }
}