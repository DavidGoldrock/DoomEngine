#include "../headers/BlockMap.h"
BlockMap::BlockMap(uint16_t gridX, uint16_t gridY, uint16_t columnNumber, uint16_t rowNumber, std::shared_ptr<std::vector<uint16_t>[]> blocklists)
    : gridX(gridX), gridY(gridY), columnNumber(columnNumber), rowNumber(rowNumber), blocklists(blocklists)
{
}

std::ostream &operator<<(std::ostream &os, const BlockMap &obj)
{
    os << "BlockMap{ " << std::endl;
    os << "gridX: " << obj.gridX << " " << std::endl;
    os << "gridY: " << obj.gridY << " " << std::endl;
    os << "columnNumber: " << obj.columnNumber << " " << std::endl;
    os << "rowNumber: " << obj.rowNumber << " " << std::endl;

    os << "blocklists: [" << std::endl;
    for (int i = 0; i < obj.columnNumber * obj.rowNumber; ++i)
    {
        os << "    [ ";
        for (const auto &val : obj.blocklists[i])
        {
            os << val << " ";
        }
        os << "]" << std::endl;
    }
    os << "] " << std::endl;

    os << "}";
    return os;
}

std::shared_ptr<BlockMap> BLOCKMAP(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    uint16_t gridX = lumpDataByteReader->readBytesAsUint16();
    uint16_t gridY = lumpDataByteReader->readBytesAsUint16();
    uint16_t columnNumber = lumpDataByteReader->readBytesAsUint16();
    uint16_t rowNumber = lumpDataByteReader->readBytesAsUint16();
    size_t offsets[rowNumber * columnNumber];

    for (size_t i = 0; i < rowNumber * columnNumber; i++)
    {
        offsets[i] = lumpDataByteReader->readBytesAsUint16() * 2;
    }

    std::shared_ptr<std::vector<uint16_t>[]> blocklists = std::make_shared<std::vector<uint16_t>[]>(rowNumber * columnNumber);

    uint8_t temp;

    for (size_t i = 0; i < rowNumber * columnNumber; i++)
    {
        lumpDataByteReader->pointer = offsets[i];

        temp = lumpDataByteReader->readBytesAsUint16();

        // First is always 0
        if (temp != 0)
        {
            std::cerr << "BLOCKLIST FAULTY" << std::endl;
        }

        // Add until value is -1
        temp = lumpDataByteReader->readBytesAsUint16();
        while (temp != 255)
        {
            blocklists[i].push_back(temp);
            temp = lumpDataByteReader->readBytesAsUint16();
        }
    }

    std::shared_ptr<BlockMap> blockMapPointer = std::make_shared<BlockMap>(gridX, gridY, columnNumber, rowNumber, blocklists);
#ifdef debugPrint
    std::cout << "Loaded BlockMap map " << *blockMapPointer << std::endl;

#endif

    return blockMapPointer;
}