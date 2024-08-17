#include "../headers/SubSector.h"

SubSector::SubSector(uint16_t segCount, uint16_t firstSegNumber)
        : segCount(segCount), firstSegNumber(firstSegNumber)
    {}

std::ostream& operator<<(std::ostream& os, const SubSector& obj) {
        os << "SubSector{ ";
        os << "segCount: " << obj.segCount << " ";
        os << "firstSegNumber: " << obj.firstSegNumber << " ";
        os << "}";
        return os;
    }