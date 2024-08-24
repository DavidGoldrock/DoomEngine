#ifndef SEG_H
#define SEG_H

#include <cstdint>
#include <iostream>

struct Seg {
    uint16_t startingVertexNumber;
    uint16_t endingVertexNumber;
    uint16_t angle;
    uint16_t lineDefNumber;
    bool directionSameAsLineDef;
    uint16_t offset;

    // Constructor
    Seg(uint16_t startingVertexNumber, uint16_t endingVertexNumber, uint16_t angle, uint16_t lineDefNumber, bool directionSameAsLineDef, uint16_t offset);
    Seg();
    friend std::ostream& operator<<(std::ostream& os, const Seg& obj);
};

#endif
