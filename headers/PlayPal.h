#ifndef PLAYPAL_H
#define PLAYPAL_H

#include <cstdint>
#include <iostream>
#include <memory>

struct PlayPal
{
    constexpr static uint8_t TRANSPARENT_COLOR = 247;

    std::shared_ptr<uint8_t[]> rawRGBs;

    // Constructor
    PlayPal(std::shared_ptr<uint8_t[]> rawRGBs);

    uint8_t *getPallette(uint8_t index);

    friend std::ostream &operator<<(std::ostream &os, const PlayPal &obj);
};

#endif
