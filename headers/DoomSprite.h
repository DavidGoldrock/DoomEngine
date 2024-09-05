#ifndef DOOM_SPRITE_H
#define DOOM_SPRITE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>

struct DoomSprite {
    uint16_t width;
    uint16_t height;
    int16_t leftOffset;
    int16_t topOffset;
    std::shared_ptr<uint8_t[]> pixels;


    // Constructor
    DoomSprite(uint16_t width, uint16_t height, int16_t leftOffset, int16_t topOffset, std::shared_ptr<uint8_t[]> pixels);
    

    friend std::ostream& operator<<(std::ostream& os, const DoomSprite& obj);
};

#endif
