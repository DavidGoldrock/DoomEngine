#ifndef SECTOR_H
#define STRUCT SECTOR_H

#include <cstdint>
#include <iostream>

struct Sector {
    uint16_t floorHeight;
    uint16_t ceilingHeight;
    std::string floorTextureName;
    std::string ceilingTextureName;
    uint16_t lightLevel;
    uint16_t specialTag;
    uint16_t tagNumber;

    // Constructor
    Sector(uint16_t floorHeight, uint16_t ceilingHeight, std::string floorTextureName, std::string ceilingTextureName, uint16_t lightLevel, uint16_t specialTag, uint16_t tagNumber);

    friend std::ostream& operator<<(std::ostream& os, const Sector& obj);
};

#endif
