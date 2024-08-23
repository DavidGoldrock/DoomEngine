#ifndef RGB_H
#define RGB_H

#include <cstdint>
#include <iostream>

struct RGB
{
    uint8_t r;
    uint8_t g;
    uint8_t b;

    // Constructor
    RGB(uint8_t r, uint8_t g,uint8_t b);
    RGB();
    
    friend std::ostream &operator<<(std::ostream &os, const RGB &obj);
};

#endif
