#include "../headers/Seg.h"
Seg::Seg(uint16_t startingVertexNumber, uint16_t endingVertexNumber, uint16_t angle, uint16_t lineDefNumber, bool directionSameAsLineDef, uint16_t offset)
        : startingVertexNumber(startingVertexNumber), endingVertexNumber(endingVertexNumber), angle(angle), lineDefNumber(lineDefNumber), directionSameAsLineDef(directionSameAsLineDef), offset(offset)
    {}

Seg::Seg()
        : startingVertexNumber(0), endingVertexNumber(0), angle(0), lineDefNumber(0), directionSameAsLineDef(false), offset(0)
    {}

std::ostream& operator<<(std::ostream& os, const Seg& obj) {
        os << "Seg{ ";
        os << "startingVertexNumber: " << (int) obj.startingVertexNumber << " ";
        os << "endingVertexNumber: " << (int) obj.endingVertexNumber << " ";
        os << "angle: " << (int) obj.angle << " ";
        os << "lineDefNumber: " << (int) obj.lineDefNumber << " ";
        os << "directionSameAsLineDef: " << obj.directionSameAsLineDef << " ";
        os << "offset: " << (int) obj.offset << " ";
        os << "}";
        return os;
    }