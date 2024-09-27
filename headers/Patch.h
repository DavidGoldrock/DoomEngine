#ifndef PATCH_H
#define PATCH_H

#include <cstdint>
#include <iostream>

struct Patch
{
    int16_t originX;
    int16_t originY;
    int16_t patchNum;
    // Constructor
    Patch(int16_t originX, int16_t originY, int16_t patchNum);
    Patch();

    friend std::ostream &operator<<(std::ostream &os, const Patch &obj);
};

#endif
