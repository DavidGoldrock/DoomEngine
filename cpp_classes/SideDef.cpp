#include "../headers/SideDef.h"

SideDef::SideDef(uint16_t x, uint16_t y, uint16_t sectorNumber, std::string upperTextureName, std::string lowerTextureName, std::string middleTextureName)
    : x(x), y(y), sectorNumber(sectorNumber), upperTextureName(upperTextureName), lowerTextureName(lowerTextureName), middleTextureName(middleTextureName)
{
}

SideDef::SideDef()
    : x(0), y(0), sectorNumber(0), upperTextureName(""), lowerTextureName("0"), middleTextureName("0")
{
}

std::ostream &operator<<(std::ostream &os, const SideDef &obj)
{
    os << "SideDef{ ";
    os << "x: " << (int)obj.x << " ";
    os << "y: " << (int)obj.y << " ";
    os << "upperTextureName: " << obj.upperTextureName << " ";
    os << "lowerTextureName: " << obj.lowerTextureName << " ";
    os << "middleTextureName: " << obj.middleTextureName << " ";
    os << "sectorNumber: " << (int)obj.sectorNumber << " ";
    os << "}";
    return os;
}

std::shared_ptr<SideDef[]> SIDEDEFS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<SideDef[]> levelSideDefs = std::make_shared<SideDef[]>(lump.size / 30);
    // Read using format
    for (size_t i = 0; i < lump.size / 30; i++)
    {
        levelSideDefs[i].x = lumpDataByteReader->readBytesAsUint16();
        levelSideDefs[i].y = lumpDataByteReader->readBytesAsUint16();
        levelSideDefs[i].upperTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].lowerTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].middleTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].sectorNumber = lumpDataByteReader->readBytesAsUint16();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded SideDef [" << (i + 1) << "]" << " Out of [" << lump.size / 30 << "]" << levelSideDefs[i] << std::endl;
#endif
    }

    return levelSideDefs;
}