#ifndef THING_H
#define THING_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>

struct Thing
{
    uint16_t x;
    uint16_t y;
    uint16_t angle;
    uint16_t doomType;
    uint16_t flags;
    bool skillLevel12;
    bool skillLevel3;
    bool skillLevel45;
    bool deaf;
    bool notSinglePlayer;

    // Constructor
    Thing(uint16_t x, uint16_t y, uint16_t angle, uint16_t doomType, uint16_t flags, bool skillLevel12, bool skillLevel3, bool skillLevel45, bool deaf, bool notSinglePlayer);

    Thing();

    friend std::ostream &operator<<(std::ostream &os, const Thing &obj);
};

std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

#endif
