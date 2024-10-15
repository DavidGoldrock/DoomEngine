#include "../headers/Sector.h"

Sector::Sector(uint16_t floorHeight, uint16_t ceilingHeight, std::string floorTextureName, std::string ceilingTextureName, uint16_t lightLevel, uint16_t specialTag, uint16_t tagNumber)
    : floorHeight(floorHeight), ceilingHeight(ceilingHeight), floorTextureName(floorTextureName), ceilingTextureName(ceilingTextureName), lightLevel(lightLevel), specialTag(specialTag), tagNumber(tagNumber)
{
}

Sector::Sector()
    : floorHeight(0), ceilingHeight(0), floorTextureName(""), ceilingTextureName(""), lightLevel(0), specialTag(0), tagNumber(0)
{
}

std::ostream &operator<<(std::ostream &os, const Sector &obj)
{
    os << "Sector{ ";
    os << "floorHeight: " << (int)obj.floorHeight << " ";
    os << "floorTextureName: " << obj.floorTextureName << " ";
    os << "ceilingTextureName: " << obj.ceilingTextureName << " ";
    os << "ceilingHeight: " << (int)obj.ceilingHeight << " ";
    os << "lightLevel: " << (int)obj.lightLevel << " ";
    os << "specialTag: " << (int)obj.specialTag << " ";
    os << "tagNumber: " << (int)obj.tagNumber << " ";
    os << "}";
    return os;
}

std::shared_ptr<Sector[]> SECTORS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Sector[]> levelSector = std::make_shared<Sector[]>(lump.size / 26);
    // Read using format
    for (size_t i = 0; i < lump.size / 26; i++)
    {
        levelSector[i].floorHeight = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].ceilingHeight = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].floorTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSector[i].ceilingTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSector[i].lightLevel = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].specialTag = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].tagNumber = lumpDataByteReader->readBytesAsUint16();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded Sector [" << (i + 1) << "]" << " Out of [" << lump.size / 26 << "]" << levelSector[i] << std::endl;
#endif
    }

    return levelSector;
}