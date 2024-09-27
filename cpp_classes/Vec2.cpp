#include "../headers/Vec2.h"
#include <cmath>

Vec2::Vec2(double x, double y) : x(x), y(y) {}
Vec2::Vec2() : x(0), y(0) {}

std::ostream &operator<<(std::ostream &os, const Vec2 &obj)
{
    os << "Vec2{ ";
    os << "x: " << (int)obj.x << " ";
    os << "y: " << (int)obj.y << " ";
    os << "}";
    return os;
}