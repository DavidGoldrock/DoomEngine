#ifndef CONSECUTIVE_BYTEARRAY_READER_H
#define CONSECUTIVE_BYTEARRAY_READER_H

#include <cstdint>
#include <memory>
#include <cstring> // for std::memcpy
#include "Lump.h"

class ConsecutiveBytearrayReader
{
public:
    ConsecutiveBytearrayReader(std::shared_ptr<uint8_t[]> arr, size_t size);

    /**
     * @brief reads a number of bytes into a buffer and advances its pointer that same ammount
     *
     * @param buffer buffer to write to
     * @param num how many bytes
     * @return size_t how many bytes were changed
     */
    size_t readBytes(uint8_t *buffer, size_t num);

    // wrapper to read into a char array (string like)
    size_t readBytesAsChar(char *buffer, size_t num);

    // wrapper to read into a returned string
    std::string readBytesAsStr(size_t num);

    // wrapper to read 2 bytes as little endian uint8
    uint8_t readBytesAsUint8();

    // wrapper to read 2 bytes as little endian uint16
    uint16_t readBytesAsUint16();

    // wrapper to read 2 bytes as little endian uint32
    uint32_t readBytesAsUint32();

    // wrapper to read 2 bytes as little endian uint8
    int8_t readBytesAsInt8();

    // wrapper to read 2 bytes as little endian int16
    int16_t readBytesAsInt16();

    // wrapper to read 2 bytes as little endian int32
    int32_t readBytesAsInt32();

    // wrapper to read a lump description
    Lump readLump();

    // copies the data of a lump as described in its descriptor into a uint8 array
    void readLumpData(uint8_t *buffer, const Lump &l);

    // pointer to the next byte to read in the array
    size_t pointer;

    // the size of the entire array
    size_t arrSize;

    // the data
    std::shared_ptr<uint8_t[]> arr;
};

#endif // CONSECUTIVE_BYTEARRAY_READER_H