#ifndef SIDE_DEF_H
#define SIDE_DEF_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>

struct SideDef
{
    uint16_t x;
    uint16_t y;
    std::string upperTextureName;
    std::string lowerTextureName;
    std::string middleTextureName;
    uint16_t sectorNumber;

    // Constructor
    SideDef(uint16_t x, uint16_t y, uint16_t sectorNumber, std::string upperTextureName, std::string lowerTextureName, std::string middleTextureName);
    SideDef();

    friend std::ostream &operator<<(std::ostream &os, const SideDef &obj);
};

std::shared_ptr<SideDef[]> SIDEDEFS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

#endif
