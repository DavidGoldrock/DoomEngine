#include "../headers/PlayPal.h"

PlayPal::PlayPal(std::shared_ptr<uint8_t[]> rawRGBs) : rawRGBs(rawRGBs) {}

uint8_t *PlayPal::getPallette(uint8_t index)
{
    return rawRGBs.get() + (PALLETE_DEPTH * index) * 3;
}

std::ostream &operator<<(std::ostream &os, const PlayPal &obj)
{
    os << "PlayPal {" << std::endl;
    for (uint8_t i = 0; i < PlayPal::PLAYPAL_AMMOUNT; i++)
    {
        os << "{" << std::endl;
        for (int j = 0; j < PlayPal::PALLETE_DEPTH; ++j)
        {
            os << (int) obj.rawRGBs[i * PlayPal::PALLETE_DEPTH + j] << ", ";
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}

std::shared_ptr<PlayPal> PLAYPAL(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<uint8_t[]> levelPalleteData = std::make_shared<uint8_t[]>(lump.size);
    // Read using format
    for (size_t i = 0; i < lump.size; i += 3)
    {
        levelPalleteData[i] = lumpDataByteReader->readBytesAsUint8();
        levelPalleteData[i + 1] = lumpDataByteReader->readBytesAsUint8();
        levelPalleteData[i + 2] = lumpDataByteReader->readBytesAsUint8();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded RGB Value [" << ((i / 3) + 1) << "]" << " Out of [" << lump.size / 3 << "]" << levelPalleteData[i] << std::endl;
#endif
    }

    std::shared_ptr<PlayPal> returnValue = std::make_shared<PlayPal>(levelPalleteData);

#ifdef debugPrint
    std::cout << "Loaded PlayPal " << *returnValue << std::endl;

#endif
    return returnValue;
}