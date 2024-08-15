#include "./headers/Seg.h"
#include <cstdint>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Seg& obj) {
        os << "Seg{ ";
        os << "startingVertexNumber: " << obj.startingVertexNumber << " ";
        os << "endingVertexNumber: " << obj.endingVertexNumber << " ";
        os << "angle: " << obj.angle << " ";
        os << "lineDefNumber: " << obj.lineDefNumber << " ";
        os << "directionSameAsLineDef: " << obj.directionSameAsLineDef << " ";
        os << "offset: " << obj.offset << " ";
        os << "}";
        return os;
    }