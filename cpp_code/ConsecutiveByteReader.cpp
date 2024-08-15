#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include <cstring> // for memcpy

ConsecutiveBytearrayReader::ConsecutiveBytearrayReader(const uint8_t* arr, size_t size)
    : pointer(0), arr(arr), arrSize(size) {}

size_t ConsecutiveBytearrayReader::readBytes(uint8_t* buffer, size_t bytes_num) {
    return 0;

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

Lump createLump(uint16_t filepos, uint16_t size, char* name) {
    return Lump(filepos,size,name);
}

Lump ConsecutiveBytearrayReader::readLump() {
    uint16_t filepos = readBytesAsUint16();
    uint16_t size = readBytesAsUint16();
    char* name = new char[9];
    readBytesAsChar(name, 8);
    return createLump(filepos,size,name);
}

void ConsecutiveBytearrayReader::readLumpData(uint8_t* buffer, const Lump& l) {
    size_t oldPointer = pointer;
    pointer = l.filepos;
    readBytes(buffer, l.size);
    pointer = oldPointer;
}