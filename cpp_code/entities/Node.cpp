#include "../headers/Node.h"
#include <cstdint>
#include <iostream>

struct Node {
    uint16_t x;
    uint16_t y;
    uint16_t deltaX;
    uint16_t deltaY;
    uint16_t rightBoundingBoxTop;
    uint16_t rightBoundingBoxBottom;
    uint16_t rightBoundingBoxLeft;
    uint16_t rightBoundingBoxRight;
    uint16_t leftBoundingBoxTop;
    uint16_t leftBoundingBoxBottom;
    uint16_t leftBoundingBoxLeft;
    uint16_t leftBoundingBoxRight;
    void* rightChild;
    void* leftChild;

    // Constructor
    Node(uint16_t x, uint16_t y, uint16_t deltaX, uint16_t deltaY, uint16_t rightBoundingBoxTop, uint16_t rightBoundingBoxBottom, uint16_t rightBoundingBoxLeft, uint16_t rightBoundingBoxRight, uint16_t leftBoundingBoxTop, uint16_t leftBoundingBoxBottom, uint16_t leftBoundingBoxLeft, uint16_t leftBoundingBoxRight)
        : x(x), y(y), deltaX(deltaX), deltaY(deltaY), rightBoundingBoxTop(rightBoundingBoxTop), rightBoundingBoxBottom(rightBoundingBoxBottom), rightBoundingBoxLeft(rightBoundingBoxLeft), rightBoundingBoxRight(rightBoundingBoxRight), leftBoundingBoxTop(leftBoundingBoxTop), leftBoundingBoxBottom(leftBoundingBoxBottom), leftBoundingBoxLeft(leftBoundingBoxLeft), leftBoundingBoxRight(leftBoundingBoxRight)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Node& obj) {
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
};