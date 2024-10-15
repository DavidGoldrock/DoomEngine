#ifndef SECTOR_H
#define SECTOR_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>

struct Sector
{
    uint16_t floorHeight;
    uint16_t ceilingHeight;
    std::string floorTextureName;
    std::string ceilingTextureName;
    uint16_t lightLevel;
    uint16_t specialTag;
    uint16_t tagNumber;

    // Constructor
    Sector(uint16_t floorHeight, uint16_t ceilingHeight, std::string floorTextureName, std::string ceilingTextureName, uint16_t lightLevel, uint16_t specialTag, uint16_t tagNumber);
    Sector();

    friend std::ostream &operator<<(std::ostream &os, const Sector &obj);
};

std::shared_ptr<Sector[]> SECTORS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

#endif
