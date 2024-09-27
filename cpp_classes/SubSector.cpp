#include "../headers/SubSector.h"

SubSector::SubSector(uint16_t segCount, uint16_t firstSegNumber)
    : segCount(segCount), firstSegNumber(firstSegNumber)
{
}
SubSector::SubSector()
    : segCount(0), firstSegNumber(0)
{
}

std::ostream &operator<<(std::ostream &os, const SubSector &obj)
{
    os << "SubSector{ ";
    os << "segCount: " << (int)obj.segCount << " ";
    os << "firstSegNumber: " << (int)obj.firstSegNumber << " ";
    os << "}";
    return os;
}