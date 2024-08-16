#include "./headers/Thing.h"
#include <cstdint>
#include <iostream>


Thing::Thing() {
    Thing(0,0,0,0,0,false,false,false,false,false);
}

std::ostream& operator<< (std::ostream& os, const Thing& obj) {
        os << "Thing{ ";
        os << "x: " << obj.x << " ";
        os << "y: " << obj.y << " ";
        os << "angle: " << obj.angle << " ";
        os << "doomType: " << obj.doomType << " ";
        os << "flags: " << obj.flags << " ";
        os << "skillLevel12: " << obj.skillLevel12 << " ";
        os << "skillLevel3: " << obj.skillLevel3 << " ";
        os << "skillLevel45: " << obj.skillLevel45 << " ";
        os << "deaf: " << obj.deaf << " ";
        os << "notSinglePlayer: " << obj.notSinglePlayer << " ";
        os << "}";
        return os;
    }  