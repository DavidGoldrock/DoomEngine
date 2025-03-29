#ifndef COLORMAP_H
#define COLORMAP_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>
#include <memory>

class ColorMap
{
private:
    std::shared_ptr<uint8_t[]> rawIndexes;

public:
    constexpr static uint16_t MAP_DEPTH = 256;
    constexpr static uint8_t COLORMAP_AMMOUNT = 32;

    // Constructor
    ColorMap(std::shared_ptr<uint8_t[]> rawRGBs);

    uint8_t *getMap(uint8_t index);

    friend std::ostream &operator<<(std::ostream &os, const ColorMap &obj);
};

std::shared_ptr<ColorMap> COLORMAP_FROM_READER(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

#endif
