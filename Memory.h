#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <tuple>
#include <bitset>
#include <vector>
#include <iostream>
#include <string>

class Memory
{
public:
    Memory();
    void initialize(int s, int f);
    void initialize(int p, int s, int f);
    int readPhysical(int VA);
    int writePhysical(int VA);
    void setUseTLB(bool b);
    std::tuple<int, int, int> convertVA(int VA);
    int getTraceBit(int b);
    bool toggleBitMap(int b);
    int checkTLB(int VA);
private:
    std::vector<std::tuple<int, std::string, int>> TLB;
    bool useTLB = true;
    int physicalMem[524288] = {0};
    unsigned int bitMap[32];
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
};

#endif //MEMORY_H