#include "../headers/Patch.h"

Patch::Patch(int16_t originX, int16_t originY, int16_t patchNum) : originX(originX), originY(originY), patchNum(patchNum) {}
Patch::Patch()
    : originX(0), originY(0), patchNum(0) {}

std::ostream &operator<<(std::ostream &os, const Patch &obj)
{
    os << "Patch{ ";
    os << "originX: " << (int)obj.originX << " ";
    os << "originY: " << (int)obj.originY << " ";
    os << "patchNum: " << (int)obj.patchNum;
    os << "}";
    return os;
}