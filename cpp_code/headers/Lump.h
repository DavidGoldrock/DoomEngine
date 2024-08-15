#ifndef STRUCT LUMP_H
#define STRUCT LUMP_H

#include <cstdint>
#include <iostream>

struct Lump {
    uint16_t filepos;
    uint16_t size;
    char* name;

    // Constructor
    Lump(uint16_t filepos, uint16_t size, char* name);

    friend std::ostream& operator<<(std::ostream& os, const Lump& obj);
};

#endif
