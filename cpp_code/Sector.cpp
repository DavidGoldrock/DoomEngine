#include "./headers/Sector.h"
#include <cstdint>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Sector& obj) {
        os << "Sector{ ";
        os << "floorHeight: " << obj.floorHeight << " ";
        os << "ceilingHeight: " << obj.ceilingHeight << " ";
        os << "lightLevel: " << obj.lightLevel << " ";
        os << "specialTag: " << obj.specialTag << " ";
        os << "tagNumber: " << obj.tagNumber << " ";
        os << "}";
        return os;
    }