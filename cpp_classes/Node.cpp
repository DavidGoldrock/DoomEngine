#include "../headers/Node.h"

Node::Node(uint16_t x, uint16_t y, uint16_t deltaX, uint16_t deltaY, uint16_t rightBoundingBoxTop, uint16_t rightBoundingBoxBottom, uint16_t rightBoundingBoxLeft, uint16_t rightBoundingBoxRight, uint16_t leftBoundingBoxTop, uint16_t leftBoundingBoxBottom, uint16_t leftBoundingBoxLeft, uint16_t leftBoundingBoxRight, uint16_t rightChildIndex, uint16_t leftChildIndex)
    : x(x), y(y), deltaX(deltaX), deltaY(deltaY), rightBoundingBoxTop(rightBoundingBoxTop), rightBoundingBoxBottom(rightBoundingBoxBottom), rightBoundingBoxLeft(rightBoundingBoxLeft), rightBoundingBoxRight(rightBoundingBoxRight), leftBoundingBoxTop(leftBoundingBoxTop), leftBoundingBoxBottom(leftBoundingBoxBottom), leftBoundingBoxLeft(leftBoundingBoxLeft), leftBoundingBoxRight(leftBoundingBoxRight), rightChildIndex(rightChildIndex), leftChildIndex(leftChildIndex)
{
}

Node::Node()
    : x(0), y(0), deltaX(0), deltaY(0), rightBoundingBoxTop(0), rightBoundingBoxBottom(0), rightBoundingBoxLeft(0), rightBoundingBoxRight(0), leftBoundingBoxTop(0), leftBoundingBoxBottom(0), leftBoundingBoxLeft(0), leftBoundingBoxRight(0), rightChildIndex(0), leftChildIndex(0)
{
}

std::ostream &operator<<(std::ostream &os, const Node &obj)
{
    os << "Node{ ";
    os << "x: " << (int)obj.x << " ";
    os << "y: " << (int)obj.y << " ";
    os << "deltaX: " << (int)obj.deltaX << " ";
    os << "deltaY: " << (int)obj.deltaY << " ";
    os << "rightBoundingBoxTop: " << (int)obj.rightBoundingBoxTop << " ";
    os << "rightBoundingBoxBottom: " << (int)obj.rightBoundingBoxBottom << " ";
    os << "rightBoundingBoxLeft: " << (int)obj.rightBoundingBoxLeft << " ";
    os << "rightBoundingBoxRight: " << (int)obj.rightBoundingBoxRight << " ";
    os << "leftBoundingBoxTop: " << (int)obj.leftBoundingBoxTop << " ";
    os << "leftBoundingBoxBottom: " << (int)obj.leftBoundingBoxBottom << " ";
    os << "leftBoundingBoxLeft: " << (int)obj.leftBoundingBoxLeft << " ";
    os << "leftBoundingBoxRight: " << (int)obj.leftBoundingBoxRight << " ";
    os << "rightChildIndex: " << (int)obj.rightChildIndex << " ";
    os << "leftChildindex: " << (int)obj.leftChildIndex << " ";
    os << "}";
    return os;
}