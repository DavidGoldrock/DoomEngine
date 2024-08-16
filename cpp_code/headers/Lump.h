#ifndef LUMP_H
#define LUMP_H

#include <cstdint>
#include <iostream>
#include <cstring> // for std::strlen and std::strcpy

struct Lump {
    uint16_t filepos;
    uint16_t size;
    char* name;

    // Constructor
    Lump(uint16_t filepos, uint16_t size, const char* name);

    Lump();

    // Copy constructor
    Lump(const Lump& other);

    // Assignment operator
    Lump& operator=(const Lump& other);

    // Destructor
    ~Lump();

    friend std::ostream& operator<<(std::ostream& os, const Lump& obj);
};

#endif