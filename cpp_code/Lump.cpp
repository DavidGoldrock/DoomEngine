#include "./headers/Lump.h"

// Definition of the << operator
std::ostream& operator<<(std::ostream& os, const Lump& obj) {
    os << "Lump{ ";
    os << "filepos: " << obj.filepos << " ";
    os << "size: " << obj.size << " ";
    os << "name: " << (obj.name ? obj.name : "nullptr") << " ";
    os << "}";
    return os;
}