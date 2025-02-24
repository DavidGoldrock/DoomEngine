#include "../headers/Flat.h"
#include "../headers/CustomException.h"

Flat::Flat(std::shared_ptr<uint8_t[]> rawPixels) : rawPixels(rawPixels) {}

uint8_t Flat::getPixel(uint8_t x, uint8_t y)
{
    if (y > 64 || x > 64)
    {
        std::string msg = "Out of bounds. y = " + std::to_string((int)y) + ", x = " + std::to_string((int)x);
        throw CustomException(msg);
    }
    return rawPixels.get()[y * size + x];
}

std::ostream &operator<<(std::ostream &os, const Flat &obj)
{
    os << "Flat {" << std::endl;
    for (uint8_t i = 0; i < 14; i++)
    {
        os << "{" << std::endl;
        for (int j = 0; j < Flat::size; ++j)
        {
            os << "    ";
            os << obj.rawPixels[i * Flat::size + j] << std::endl;
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}

std::shared_ptr<Flat> FLAT(ConsecutiveBytearrayReader &fileByteReader, Lump &lump)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    return std::make_shared<Flat>(data);
}