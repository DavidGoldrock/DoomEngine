#ifndef FLAT_H
#define FLAT_H

#include <cstdint>
#include <iostream>
#include <memory>

struct Flat
{
    static constexpr uint16_t size = 64;

    std::shared_ptr<uint8_t[]> rawPixels;

    // Constructor
    Flat(std::shared_ptr<uint8_t[]> rawPixels);

    uint8_t getPixel(uint8_t x, uint8_t y);
    
    friend std::ostream &operator<<(std::ostream &os, const Flat &obj);
};

#endif
