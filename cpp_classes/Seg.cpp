#include "../headers/Seg.h"
Seg::Seg(uint16_t startingVertexNumber, uint16_t endingVertexNumber, uint16_t angle, uint16_t lineDefNumber, bool directionSameAsLineDef, uint16_t offset)
    : startingVertexNumber(startingVertexNumber), endingVertexNumber(endingVertexNumber), angle(angle), lineDefNumber(lineDefNumber), directionSameAsLineDef(directionSameAsLineDef), offset(offset)
{
}

Seg::Seg()
    : startingVertexNumber(0), endingVertexNumber(0), angle(0), lineDefNumber(0), directionSameAsLineDef(false), offset(0)
{
}

std::ostream &operator<<(std::ostream &os, const Seg &obj)
{
    os << "Seg{ ";
    os << "startingVertexNumber: " << (int)obj.startingVertexNumber << " ";
    os << "endingVertexNumber: " << (int)obj.endingVertexNumber << " ";
    os << "angle: " << (int)obj.angle << " ";
    os << "lineDefNumber: " << (int)obj.lineDefNumber << " ";
    os << "directionSameAsLineDef: " << obj.directionSameAsLineDef << " ";
    os << "offset: " << (int)obj.offset << " ";
    os << "}";
    return os;
}

std::shared_ptr<Seg[]> SEGS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Seg[]> levelSeg = std::make_shared<Seg[]>(lump.size / 12);
    // Read using format
    for (size_t i = 0; i < lump.size / 12; i++)
    {
        levelSeg[i].startingVertexNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].endingVertexNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].angle = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].lineDefNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].directionSameAsLineDef = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].offset = lumpDataByteReader->readBytesAsUint16();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded Seg [" << (i + 1) << "]" << " Out of [" << lump.size / 12 << "]" << levelSeg[i] << std::endl;
#endif
    }

    return levelSeg;
}