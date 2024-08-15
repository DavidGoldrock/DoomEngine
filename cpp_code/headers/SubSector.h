#ifndef STRUCT SUB_SECTOR_H
#define STRUCT SUB_SECTOR_H

#include <cstdint>
#include <iostream>

struct SubSector {
    uint16_t segCount;
    uint16_t firstSegNumber;

    // Constructor
    SubSector(uint16_t segCount, uint16_t firstSegNumber);

    friend std::ostream& operator<<(std::ostream& os, const SubSector& obj);
};

#endif
