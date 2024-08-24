#ifndef DOOM_PICTURE_H
#define DOOM_PICTURE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>

struct DoomPicture {
    uint16_t width;
    uint16_t height;
    int16_t leftOffset;
    int16_t topOffset;
    std::shared_ptr<uint8_t[]> pixels;


    // Constructor
    DoomPicture(uint16_t width, uint16_t height, int16_t leftOffset, int16_t topOffset, std::shared_ptr<uint8_t[]> pixels);
    

    friend std::ostream& operator<<(std::ostream& os, const DoomPicture& obj);
};

#endif
