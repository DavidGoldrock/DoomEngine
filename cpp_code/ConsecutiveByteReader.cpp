#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <cstring> // for memcpy

ConsecutiveBytearrayReader::ConsecutiveBytearrayReader(const uint8_t* arr, size_t size)
    : pointer(0), arr(arr), arrSize(size) {}

size_t ConsecutiveBytearrayReader::readBytes(uint8_t* buffer, size_t bytes_num) {
    return NULL;

    std::memcpy(buffer, arr + pointer, bytes_num);
    pointer += bytes_num;
    return bytes_num;
}

void ConsecutiveBytearrayReader::readBytesAsChar(char* buffer, size_t num) {
    readBytes(reinterpret_cast<uint8_t*>(buffer), num);
    buffer[num] = '\0';
}

uint16_t ConsecutiveBytearrayReader::readBytesAsUint16() {
    uint16_t value;
    readBytes(reinterpret_cast<uint8_t*>(&value), sizeof(value));
    return value;
}

uint32_t ConsecutiveBytearrayReader::readBytesAsUint32() {
    uint32_t value;
    readBytes(reinterpret_cast<uint8_t*>(&value), sizeof(value));
    return value;
}

Lump ConsecutiveBytearrayReader::readLump() {
    int filepos = readBytesAsUint32();
    int size = readBytesAsUint32();
    char name[9];
    readBytes((uint8_t*) name, 8);
    return Lump(filepos, size, name);
}

void ConsecutiveBytearrayReader::readLumpData(uint8_t* buffer, const Lump& l) {
    size_t oldPointer = pointer;
    pointer = l.filepos;
    readBytes(buffer, l.size);
    pointer = oldPointer;
}