#include "../headers/Lump.h"
#include <cstdint>
#include <iostream>

typedef struct Lump  {
    uint16_t filepos;
    uint16_t size;
    char* name;

    // Constructor
    Lump(uint16_t filepos, uint16_t size, char* name)
        : filepos(filepos), size(size), name(name)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Lump& obj) {
        os << "Lump{ ";
        os << "filepos: " << obj.filepos << " ";
        os << "size: " << obj.size << " ";
        os << "}";
        return os;
    }
} Lump;
