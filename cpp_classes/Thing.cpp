#include "../headers/Thing.h"
#include "../headers/UtilFunctions.h"

Thing::Thing(uint16_t x, uint16_t y, uint16_t angle, uint16_t doomType, uint16_t flags, bool skillLevel12, bool skillLevel3, bool skillLevel45, bool deaf, bool notSinglePlayer)
    : x(x), y(y), angle(angle), doomType(doomType), flags(flags), skillLevel12(skillLevel12), skillLevel3(skillLevel3), skillLevel45(skillLevel45), deaf(deaf), notSinglePlayer(notSinglePlayer)
{
}

Thing::Thing()
{
    this->x = 0;
    this->y = 0;
    this->angle = 0;
    this->doomType = 0;
    this->flags = 0;
    this->skillLevel12 = false;
    this->skillLevel3 = false;
    this->skillLevel45 = false;
    this->deaf = false;
    this->notSinglePlayer = false;
}

std::ostream &operator<<(std::ostream &os, const Thing &obj)
{
    os << "Thing{ ";
    os << "x: " << (int)obj.x << " ";
    os << "y: " << (int)obj.y << " ";
    os << "angle: " << (int)obj.angle << " ";
    os << "doomType: " << (int)obj.doomType << " ";
    os << "flags: " << (int)obj.flags << " ";
    os << "skillLevel12: " << obj.skillLevel12 << " ";
    os << "skillLevel3: " << obj.skillLevel3 << " ";
    os << "skillLevel45: " << obj.skillLevel45 << " ";
    os << "deaf: " << obj.deaf << " ";
    os << "notSinglePlayer: " << obj.notSinglePlayer << " ";
    os << "}";
    return os;
}

std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Thing[]> levelThings = std::make_shared<Thing[]>(lump.size / 10);
    // Read using format
    for (size_t i = 0; i < lump.size / 10; i++)
    {
        levelThings[i].x = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].y = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].angle = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].doomType = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].flags = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].skillLevel12 = bitAtLocation(levelThings[i].flags, 0);
        levelThings[i].skillLevel3 = bitAtLocation(levelThings[i].flags, 1);
        levelThings[i].skillLevel45 = bitAtLocation(levelThings[i].flags, 2);
        levelThings[i].deaf = bitAtLocation(levelThings[i].flags, 3);
        levelThings[i].notSinglePlayer = bitAtLocation(levelThings[i].flags, 4);

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded Thing [" << (i + 1) << "]" << " Out of [" << lump.size / 10 << "]" << levelThings[i] << std::endl;
#endif
    }

    return levelThings;
}