#include "./headers/Node.h"
#include <cstdint>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const Node& obj) {
        os << "Node{ ";
        os << "x: " << obj.x << " ";
        os << "y: " << obj.y << " ";
        os << "deltaX: " << obj.deltaX << " ";
        os << "deltaY: " << obj.deltaY << " ";
        os << "rightBoundingBoxTop: " << obj.rightBoundingBoxTop << " ";
        os << "rightBoundingBoxBottom: " << obj.rightBoundingBoxBottom << " ";
        os << "rightBoundingBoxLeft: " << obj.rightBoundingBoxLeft << " ";
        os << "rightBoundingBoxRight: " << obj.rightBoundingBoxRight << " ";
        os << "leftBoundingBoxTop: " << obj.leftBoundingBoxTop << " ";
        os << "leftBoundingBoxBottom: " << obj.leftBoundingBoxBottom << " ";
        os << "leftBoundingBoxLeft: " << obj.leftBoundingBoxLeft << " ";
        os << "leftBoundingBoxRight: " << obj.leftBoundingBoxRight << " ";
        os << "}";
        return os;
    }