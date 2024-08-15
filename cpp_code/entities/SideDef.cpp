#include "../headers/SideDef.h"
#include <cstdint>
#include <iostream>

struct SideDef {
    uint16_t x;
    uint16_t y;
    char* upperTextureName;
    char* lowerTextureName;
    char* middleTextureName;
    uint16_t sectorNumber;

    // Constructor
    SideDef(uint16_t x, uint16_t y, uint16_t sectorNumber)
        : x(x), y(y), sectorNumber(sectorNumber)
    {}

    friend std::ostream& operator<<(std::ostream& os, const SideDef& obj) {
        os << "SideDef{ ";
        os << "x: " << obj.x << " ";
        os << "y: " << obj.y << " ";
        os << "sectorNumber: " << obj.sectorNumber << " ";
        os << "}";
        return os;
    }
};