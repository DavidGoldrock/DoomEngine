#include "../headers/Sector.h"

Sector::Sector(uint16_t floorHeight, uint16_t ceilingHeight, std::string floorTextureName, std::string ceilingTextureName, uint16_t lightLevel, uint16_t specialTag, uint16_t tagNumber)
        : floorHeight(floorHeight), ceilingHeight(ceilingHeight), floorTextureName(floorTextureName), ceilingTextureName(ceilingTextureName), lightLevel(lightLevel), specialTag(specialTag), tagNumber(tagNumber)
    {}

std::ostream& operator<<(std::ostream& os, const Sector& obj) {
        os << "Sector{ ";
        os << "floorHeight: " << obj.floorHeight << " ";
        os << "floorTextureName: " << obj.floorTextureName << " ";
        os << "ceilingTextureName: " << obj.ceilingTextureName << " ";
        os << "ceilingHeight: " << obj.ceilingHeight << " ";
        os << "lightLevel: " << obj.lightLevel << " ";
        os << "specialTag: " << obj.specialTag << " ";
        os << "tagNumber: " << obj.tagNumber << " ";
        os << "}";
        return os;
    }