#include "../headers/SubSector.h"

SubSector::SubSector(uint16_t segCount, uint16_t firstSegNumber)
    : segCount(segCount), firstSegNumber(firstSegNumber)
{
}
SubSector::SubSector()
    : segCount(0), firstSegNumber(0)
{
}

std::ostream &operator<<(std::ostream &os, const SubSector &obj)
{
    os << "SubSector{ ";
    os << "segCount: " << (int)obj.segCount << " ";
    os << "firstSegNumber: " << (int)obj.firstSegNumber << " ";
    os << "}";
    return os;
}

std::shared_ptr<SubSector[]> SSECTORS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{

    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<SubSector[]> levelSubSector = std::make_shared<SubSector[]>(lump.size / 4);
    // Read using format
    for (size_t i = 0; i < lump.size / 4; i++)
    {
        levelSubSector[i].segCount = lumpDataByteReader->readBytesAsUint16();
        levelSubSector[i].firstSegNumber = lumpDataByteReader->readBytesAsUint16();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded SubSector [" << (i + 1) << "]" << " Out of [" << lump.size / 4 << "]" << levelSubSector[i] << std::endl;
#endif
    }

    return levelSubSector;
}