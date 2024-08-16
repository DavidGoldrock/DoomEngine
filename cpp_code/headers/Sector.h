#ifndef SECTOR_H
#define STRUCT SECTOR_H

#include <cstdint>
#include <iostream>

struct Sector {
    uint16_t floorHeight;
    uint16_t ceilingHeight;
    char* floorTextureName;
    char* ceilingTextureName;
    uint16_t lightLevel;
    uint16_t specialTag;
    uint16_t tagNumber;

    // Constructor
    Sector(uint16_t floorHeight, uint16_t ceilingHeight, uint16_t lightLevel, uint16_t specialTag, uint16_t tagNumber)
        : floorHeight(floorHeight), ceilingHeight(ceilingHeight), lightLevel(lightLevel), specialTag(specialTag), tagNumber(tagNumber)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Sector& obj) {
        os << "Sector{ ";
        os << "floorHeight: " << obj.floorHeight << " ";
        os << "ceilingHeight: " << obj.ceilingHeight << " ";
        os << "lightLevel: " << obj.lightLevel << " ";
        os << "specialTag: " << obj.specialTag << " ";
        os << "tagNumber: " << obj.tagNumber << " ";
        os << "}";
        return os;
    }
};

#endif
