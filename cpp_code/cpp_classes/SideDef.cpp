#include "../headers/SideDef.h"

SideDef::SideDef(uint16_t x, uint16_t y, uint16_t sectorNumber, std::string upperTextureName, std::string lowerTextureName, std::string middleTextureName)
        : x(x), y(y), sectorNumber(sectorNumber), upperTextureName(upperTextureName), lowerTextureName(lowerTextureName), middleTextureName(middleTextureName)
    {}
std::ostream& operator<<(std::ostream& os, const SideDef& obj) {
    os << "SideDef{ ";
    os << "x: " << (int) obj.x << " ";
    os << "y: " << (int) obj.y << " ";
    os << "upperTextureName: " << obj.upperTextureName << " ";
    os << "lowerTextureName: " << obj.lowerTextureName << " ";
    os << "middleTextureName: " << obj.middleTextureName << " ";
    os << "sectorNumber: " << (int) obj.sectorNumber << " ";
    os << "}";
    return os;
}