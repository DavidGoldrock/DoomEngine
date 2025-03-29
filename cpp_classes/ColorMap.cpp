#include "../headers/ColorMap.h"

ColorMap::ColorMap(std::shared_ptr<uint8_t[]> rawRGBs) : rawIndexes(rawRGBs) {}

uint8_t *ColorMap::getMap(uint8_t index)
{
    return rawIndexes.get() + (ColorMap::MAP_DEPTH * index);
}

std::ostream &operator<<(std::ostream &os, const ColorMap &obj)
{
    os << "ColorMap {" << std::endl;
    for (uint8_t i = 0; i < ColorMap::COLORMAP_AMMOUNT; i++)
    {
        os << "{" << std::endl;
        for (int j = 0; j < ColorMap::MAP_DEPTH; ++j)
        {
            os << (int) obj.rawIndexes[i * ColorMap::MAP_DEPTH + j] << ", ";
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}

std::shared_ptr<ColorMap> COLORMAP_FROM_READER(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<uint8_t[]> levelPalleteData = std::make_shared<uint8_t[]>(lump.size);
    // Read using format
    for (size_t i = 0; i < lump.size; i ++)
    {
        levelPalleteData[i] = lumpDataByteReader->readBytesAsUint8();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded Indexes [" << ((i) + 1) << "]" << " Out of [" << lump.size << "]" << levelPalleteData[i] << std::endl;
#endif
    }

    std::shared_ptr<ColorMap> returnValue = std::make_shared<ColorMap>(levelPalleteData);

#ifdef debugPrint
    std::cout << "Loaded ColorMap " << *returnValue << std::endl;
    std::cin.get();

#endif
    return returnValue;
}