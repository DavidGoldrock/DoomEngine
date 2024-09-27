#include "../headers/Lump.h"

Lump::Lump(uint32_t filepos, uint32_t size, std::string name) : filepos(filepos), size(size)
{
    this->name = name;
}

Lump::Lump()
{
    this->filepos = 0;
    this->size = 0;
    this->name = "";
}

Lump::Lump(const Lump &other)
    : filepos(other.filepos), size(other.size), name(other.name)
{
    // Allocate memory and copy the name
}

Lump &Lump::operator=(const Lump &other)
{
    if (this != &other)
    { // self-assignment check
        filepos = other.filepos;
        size = other.size;
        name = other.name;
    }
    return *this;
}

Lump::~Lump()
{
}

std::ostream &operator<<(std::ostream &os, const Lump &obj)
{
    os << "Lump{ ";
    os << "filepos: " << (int)obj.filepos << " ";
    os << "size: " << (int)obj.size << " ";
    os << "name: " << obj.name << " ";
    os << "}";
    return os;
}