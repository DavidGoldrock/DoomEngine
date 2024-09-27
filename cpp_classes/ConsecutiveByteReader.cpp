#include "../headers/ConsecutiveBytearrayReader.h"
#include "../headers/Lump.h"
#include "../headers/CustomException.h"
#include <cstring> // for memcpy

ConsecutiveBytearrayReader::ConsecutiveBytearrayReader(std::shared_ptr<uint8_t[]> arr, size_t size)
    : pointer(0), arr(arr), arrSize(size) {}

size_t ConsecutiveBytearrayReader::readBytes(uint8_t *buffer, size_t bytes_num)
{
    // Validate operation is allowed, if not, throw exception
    if (bytes_num + pointer > arrSize)
    {
        std::string errorMessage;
        errorMessage += "Bytes ammount requested " + std::to_string(bytes_num);
        errorMessage += " while pointer was " + std::to_string(pointer);
        errorMessage += " exceeded maximum bytes in data array " + std::to_string(arrSize);
        throw CustomException(errorMessage);
    }

    // Copy values and advance the pointer
    std::memcpy(buffer, arr.get() + pointer, bytes_num);
    pointer += bytes_num;
    return bytes_num;
}

size_t ConsecutiveBytearrayReader::readBytesAsChar(char *buffer, size_t num)
{
    // It's important to use the null terminator :)
    size_t res = readBytes(reinterpret_cast<uint8_t *>(buffer), num);
    buffer[num] = '\0';
    return res;
}

std::string ConsecutiveBytearrayReader::readBytesAsStr(size_t num)
{
    char buffer[num + 1];
    readBytesAsChar(buffer, num);
    return std::string(buffer);
}

uint8_t ConsecutiveBytearrayReader::readBytesAsUint8()
{
    uint8_t value;
    readBytes(&value, sizeof(value));
    return value;
}

uint16_t ConsecutiveBytearrayReader::readBytesAsUint16()
{
    uint16_t value;
    readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
    return value;
}

uint32_t ConsecutiveBytearrayReader::readBytesAsUint32()
{
    uint32_t value;
    readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
    return value;
}

int8_t ConsecutiveBytearrayReader::readBytesAsInt8()
{
    int8_t value;
    readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
    return value;
}

int16_t ConsecutiveBytearrayReader::readBytesAsInt16()
{
    int16_t value;
    readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
    return value;
}

int32_t ConsecutiveBytearrayReader::readBytesAsInt32()
{
    int32_t value;
    readBytes(reinterpret_cast<uint8_t *>(&value), sizeof(value));
    return value;
}

Lump ConsecutiveBytearrayReader::readLump()
{
    // Read the filePos, size and name, and pass them into the lump
    uint32_t filepos = readBytesAsUint32();
    uint32_t size = readBytesAsUint32();
    std::string name = readBytesAsStr(8);
    Lump l(filepos, size, name);
    return l;
}

void ConsecutiveBytearrayReader::readLumpData(uint8_t *buffer, const Lump &l)
{
    // Save old pointer
    size_t oldPointer = pointer;
    // Go to the position in the descriptor
    pointer = l.filepos;
    // Read the data
    readBytes(buffer, l.size);
    // Return the old pointer
    pointer = oldPointer;
}