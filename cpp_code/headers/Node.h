#ifndef NODE_H
#define STRUCT NODE_H

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

    friend std::ostream& operator<<(std::ostream& os, const Node& obj);
};

#endif
