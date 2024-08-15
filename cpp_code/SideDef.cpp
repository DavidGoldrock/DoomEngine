#include "./headers/SideDef.h"
#include <cstdint>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const SideDef& obj) {
        os << "SideDef{ ";
        os << "x: " << obj.x << " ";
        os << "y: " << obj.y << " ";
        os << "sectorNumber: " << obj.sectorNumber << " ";
        os << "}";
        return os;
    }