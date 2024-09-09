#ifndef TEXTURE_H
#define TEXTURE_H

#include <cstdint>
#include <iostream>
#include <memory>
#include "Patch.h"

struct Texture {
    std::string name;
    bool masked;
    int16_t width;
    int16_t height;
    int16_t patchCount;
    std::shared_ptr<Patch[]> patches;

    // Constructor
    Texture(std::string name, bool masked, int16_t width, int16_t height, int16_t patchCount);
    Texture();

    friend std::ostream& operator<<(std::ostream& os, const Texture& obj);
};

#endif
