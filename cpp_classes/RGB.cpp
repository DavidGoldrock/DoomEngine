#include "../headers/RGB.h"

RGB::RGB(uint8_t r, uint8_t g,uint8_t b): r(r), g(g), b(b) {}
RGB::RGB(): r(0), g(0), b(0) {}

std::ostream &operator<<(std::ostream &os, const RGB &obj) {
        os << "RGB{ ";
        os << "r: " << (int) obj.r << " ";
        os << "g: " << (int) obj.g << " ";
        os << "b: " << (int) obj.b << " ";
        os << "}";
        return os;
}