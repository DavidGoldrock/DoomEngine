#include "../headers/Sector.h"

Sector::Sector(uint16_t floorHeight, uint16_t ceilingHeight, std::string floorTextureName, std::string ceilingTextureName, uint16_t lightLevel, uint16_t specialTag, uint16_t tagNumber)
        : floorHeight(floorHeight), ceilingHeight(ceilingHeight), floorTextureName(floorTextureName), ceilingTextureName(ceilingTextureName), lightLevel(lightLevel), specialTag(specialTag), tagNumber(tagNumber)
    {}

std::ostream& operator<<(std::ostream& os, const Sector& obj) {
        os << "Sector{ ";
        os << "floorHeight: " << (int) obj.floorHeight << " ";
        os << "floorTextureName: " << obj.floorTextureName << " ";
        os << "ceilingTextureName: " << obj.ceilingTextureName << " ";
        os << "ceilingHeight: " << (int) obj.ceilingHeight << " ";
        os << "lightLevel: " << (int) obj.lightLevel << " ";
        os << "specialTag: " << (int) obj.specialTag << " ";
        os << "tagNumber: " <<(int)  obj.tagNumber << " ";
        os << "}";
        return os;
    }