#ifndef SIDE_DEF_H
#define STRUCT SIDE_DEF_H

#include <cstdint>
#include <iostream>

struct SideDef {
    uint16_t x;
    uint16_t y;
    std::string upperTextureName;
    std::string lowerTextureName;
    std::string middleTextureName;
    uint16_t sectorNumber;

    // Constructor
    SideDef(uint16_t x, uint16_t y, uint16_t sectorNumber, std::string upperTextureName, std::string lowerTextureName, std::string middleTextureName);

    friend std::ostream& operator<<(std::ostream& os, const SideDef& obj);
};

#endif
