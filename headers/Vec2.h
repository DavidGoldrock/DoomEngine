#ifndef VEC2_H
#define VEC2_H

#include <cstdint>
#include <iostream>

struct Vec2 {
    double x,y;

    Vec2(double x, double y);
    Vec2();

    friend std::ostream& operator<<(std::ostream& os, const Vec2& obj); 
};

#endif