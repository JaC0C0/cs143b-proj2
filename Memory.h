#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>

class Memory
{
public:
    Memory();
    int readPhysical(int s, int p, int w);
    int writePhysical(int s, int p, int w);
private:
    int physicalMem[1024][512];
    unsigned int bitMap;
    const unsigned int bitIdentityMap[16] = 
    { 
        0x8000,
        0x4000, 
        0x2000, 
        0x1000, 
        0x0800, 
        0x0400, 
        0x0200, 
        0x0100, 
        0x0080, 
        0x0040, 
        0x0020, 
        0x0010, 
        0x0008, 
        0x0004, 
        0x0002,
        0x0001 
    };
};

#endif //MEMORY_H