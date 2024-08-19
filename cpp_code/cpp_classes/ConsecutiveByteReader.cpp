#include "../headers/ConsecutiveBytearrayReader.h"
#include "../headers/Lump.h"
#include <cstring> // for memcpy

ConsecutiveBytearrayReader::ConsecutiveBytearrayReader(const uint8_t* arr, size_t size)
    : pointer(0), arr(arr), arrSize(size) {}

size_t ConsecutiveBytearrayReader::readBytes(uint8_t* buffer, size_t bytes_num) {
    std::memcpy(buffer, arr + pointer, bytes_num);
    pointer += bytes_num;
    return bytes_num;
}


void ConsecutiveBytearrayReader::readBytesAsChar(char* buffer, size_t num) {
    readBytes(reinterpret_cast<uint8_t*>(buffer), num);
    buffer[num] = '\0';
}

std::string ConsecutiveBytearrayReader::readBytesAsStr(size_t num) {
    char buffer[num + 1];
    readBytesAsChar(buffer, num);
    return std::string(buffer);
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
    uint32_t filepos = readBytesAsUint32();
    uint32_t size = readBytesAsUint32();
    char name[9];
    readBytesAsChar(name, 8);
    Lump l(filepos,size,std::string(name));
    return l;
}

void ConsecutiveBytearrayReader::readLumpData(uint8_t* buffer, const Lump& l) {
    size_t oldPointer = pointer;
    pointer = l.filepos;
    readBytes(buffer, l.size);
    pointer = oldPointer;
}