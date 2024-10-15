#ifndef PLAYPAL_H
#define PLAYPAL_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>
#include <memory>

class PlayPal
{
private:
    std::shared_ptr<uint8_t[]> rawRGBs;

public:
    constexpr static uint16_t PALLETE_DEPTH = 256;
    constexpr static uint8_t TRANSPARENT_COLOR = 247;
    constexpr static uint8_t PLAYPAL_AMMOUNT = 14;

    // Constructor
    PlayPal(std::shared_ptr<uint8_t[]> rawRGBs);

    uint8_t *getPallette(uint8_t index);

    friend std::ostream &operator<<(std::ostream &os, const PlayPal &obj);
};

std::shared_ptr<PlayPal> PLAYPAL(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

#endif
