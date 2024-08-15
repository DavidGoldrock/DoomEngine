#include "./headers/SubSector.h"
#include <cstdint>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const SubSector& obj) {
        os << "SubSector{ ";
        os << "segCount: " << obj.segCount << " ";
        os << "firstSegNumber: " << obj.firstSegNumber << " ";
        os << "}";
        return os;
}