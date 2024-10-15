#ifndef DOOM_SPRITE_H
#define DOOM_SPRITE_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <memory>
#include <vector>
#include <iostream>

#include "PlayPal.h"

struct DoomSprite
{
    uint16_t width;
    uint16_t height;
    int16_t leftOffset;
    int16_t topOffset;
    std::shared_ptr<uint8_t[]> pixels;

    uint8_t getPixel(uint8_t x, uint8_t y);
    // Constructor
    DoomSprite(uint16_t width, uint16_t height, int16_t leftOffset, int16_t topOffset, std::shared_ptr<uint8_t[]> pixels);

    friend std::ostream &operator<<(std::ostream &os, const DoomSprite &obj);
};

std::shared_ptr<DoomSprite> SPRITE(ConsecutiveBytearrayReader &fileByteReader, Lump &lump);

#endif
