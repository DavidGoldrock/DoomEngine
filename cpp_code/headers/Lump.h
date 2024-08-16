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

    Lump() {
        this->filepos = 0;
        this->size = 0;
        this->name = nullptr;
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
            name = nullptr;
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
        try
        {
            delete[] name;
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
        
        name = nullptr;
    }

    friend std::ostream& operator<<(std::ostream& os, const Lump& obj) {
        os << "Lump{ ";
        os << "filepos: " << obj.filepos << " ";
        os << "size: " << obj.size << " ";
        os << "name: " << (obj.name ? obj.name : "nullptr") << " ";
        os << "}";
        return os;
    }
};

#endif