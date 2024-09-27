#ifndef SUB_SECTOR_H
#define SUB_SECTOR_H

#include <cstdint>
#include <iostream>

struct SubSector
{
    uint16_t segCount;
    uint16_t firstSegNumber;

    // Constructor
    SubSector(uint16_t segCount, uint16_t firstSegNumber);
    SubSector();

    friend std::ostream &operator<<(std::ostream &os, const SubSector &obj);
};

#endif
