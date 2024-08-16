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
    Lump(uint16_t filepos, uint16_t size, const char* name)
    : filepos(filepos), size(size) {
        // Allocate memory for name and copy the string
        this->name = new char[std::strlen(name) + 1];
        std::strcpy(this->name, name);
    }

    // Copy constructor
    Lump(const Lump& other)
    : filepos(other.filepos), size(other.size) {
        // Allocate memory and copy the name
        name = new char[std::strlen(other.name) + 1];
        std::strcpy(name, other.name);
    }

    // Assignment operator
    Lump& operator=(const Lump& other) {
        if (this != &other) { // self-assignment check
            // Free existing resource
            delete[] name;

            // Copy data from other
            filepos = other.filepos;
            size = other.size;
            name = new char[std::strlen(other.name) + 1];
            std::strcpy(name, other.name);
        }
        return *this;
    }

    // Destructor
    ~Lump() {
        delete[] name;
    }

    friend std::ostream& operator<<(std::ostream& os, const Lump& obj);
};

#endif