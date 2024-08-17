#ifndef CONSECUTIVE_BYTEARRAY_READER_H
#define CONSECUTIVE_BYTEARRAY_READER_H

#include <cstdint>
#include <cstring> // for std::memcpy
#include "Lump.h"

class ConsecutiveBytearrayReader {
public:
    ConsecutiveBytearrayReader(const uint8_t* arr, size_t size);

    size_t readBytes(uint8_t* buffer, size_t num);
    void readBytesAsChar(char* buffer, size_t num);
    std::string readBytesAsStr(size_t num);
    uint16_t readBytesAsUint16();
    uint32_t readBytesAsUint32();
    Lump readLump();
    void readLumpData(uint8_t* buffer, const Lump& l);
    size_t pointer;
    const uint8_t* arr;
    size_t arrSize;
};

#endif // CONSECUTIVE_BYTEARRAY_READER_H