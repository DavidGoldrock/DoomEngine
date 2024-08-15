#ifndef SEG_H
#define STRUCT SEG_H

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
    Seg(uint16_t startingVertexNumber, uint16_t endingVertexNumber, uint16_t angle, uint16_t lineDefNumber, bool directionSameAsLineDef, uint16_t offset)
        : startingVertexNumber(startingVertexNumber), endingVertexNumber(endingVertexNumber), angle(angle), lineDefNumber(lineDefNumber), directionSameAsLineDef(directionSameAsLineDef), offset(offset)
    {}

    friend std::ostream& operator<<(std::ostream& os, const Seg& obj);
};

#endif
