#ifndef PLAYPAL_H
#define PLAYPAL_H

#include <cstdint>
#include <iostream>
#include <memory>
#include "RGB.h"

struct PlayPal
{
    std::shared_ptr<RGB[]> rawRGBs;

    // Constructor
    PlayPal(std::shared_ptr<RGB[]> rawRGBs);

    RGB* getPallette(uint8_t index);
    
    friend std::ostream &operator<<(std::ostream &os, const PlayPal &obj);
};

#endif
