#include "../headers/LineDef.h"
#include "../headers/UtilFunctions.h"
LineDef::LineDef(uint8_t startVertex, uint8_t endVertex, uint8_t flags, uint8_t sType, uint8_t sTag,
                 uint8_t fSideDef, uint8_t bSideDef, bool blocksPM, bool blocksM, bool ts,
                 bool upperTextureUnpegged, bool lowerTextureUnpegged, bool secret, bool blocksSound,
                 bool neverAutoMap, bool alwaysAutoMap)
    : startVertex(startVertex), endVertex(endVertex), flags(flags), sType(sType), sTag(sTag),
      fSideDef(fSideDef), bSideDef(bSideDef), blocksPM(blocksPM), blocksM(blocksM), ts(ts),
      upperTextureUnpegged(upperTextureUnpegged), lowerTextureUnpegged(lowerTextureUnpegged),
      secret(secret), blocksSound(blocksSound), neverAutoMap(neverAutoMap), alwaysAutoMap(alwaysAutoMap)
{
}

LineDef::LineDef()
    : startVertex(0), endVertex(0), flags(0), sType(0), sTag(0),
      fSideDef(0), bSideDef(0), blocksPM(false), blocksM(false), ts(false),
      upperTextureUnpegged(false), lowerTextureUnpegged(false),
      secret(false), blocksSound(false), neverAutoMap(false), alwaysAutoMap(false)
{
}

std::ostream &operator<<(std::ostream &os, const LineDef &obj)
{
    os << "LineDef{ ";
    os << "startVertex: " << (int)obj.startVertex << " ";
    os << "endVertex: " << (int)obj.endVertex << " ";
    os << "flags: " << (int)obj.flags << " ";
    os << "sType: " << (int)obj.sType << " ";
    os << "sTag: " << (int)obj.sTag << " ";
    os << "fSideDef: " << (int)obj.fSideDef << " ";
    os << "bSideDef: " << (int)obj.bSideDef << " ";
    os << "blocksPM: " << obj.blocksPM << " ";
    os << "blocksM: " << obj.blocksM << " ";
    os << "ts: " << obj.ts << " ";
    os << "upperTextureUnpegged: " << obj.upperTextureUnpegged << " ";
    os << "lowerTextureUnpegged: " << obj.lowerTextureUnpegged << " ";
    os << "secret: " << obj.secret << " ";
    os << "blocksSound: " << obj.blocksSound << " ";
    os << "neverAutoMap: " << obj.neverAutoMap << " ";
    os << "alwaysAutoMap: " << obj.alwaysAutoMap << " ";
    os << "}";
    return os;
}

std::shared_ptr<LineDef[]> LINEDEFS(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<LineDef[]> levelLineDefs = std::make_shared<LineDef[]>(lump.size / 14);
    // Read using format

    for (size_t i = 0; i < lump.size / 14; i++)
    {
        levelLineDefs[i].startVertex = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].endVertex = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].flags = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].sType = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].sTag = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].fSideDef = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].bSideDef = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].blocksPM = bitAtLocation(levelLineDefs[i].flags, 0);
        levelLineDefs[i].blocksM = bitAtLocation(levelLineDefs[i].flags, 1);
        levelLineDefs[i].ts = bitAtLocation(levelLineDefs[i].flags, 2);
        levelLineDefs[i].upperTextureUnpegged = bitAtLocation(levelLineDefs[i].flags, 3);
        levelLineDefs[i].lowerTextureUnpegged = bitAtLocation(levelLineDefs[i].flags, 4);
        levelLineDefs[i].secret = bitAtLocation(levelLineDefs[i].flags, 5);
        levelLineDefs[i].blocksSound = bitAtLocation(levelLineDefs[i].flags, 6);
        levelLineDefs[i].neverAutoMap = bitAtLocation(levelLineDefs[i].flags, 7);
        levelLineDefs[i].alwaysAutoMap = bitAtLocation(levelLineDefs[i].flags, 8);

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded LineDef [" << (i + 1) << "]" << " Out of [" << lump.size / 14 << "]" << levelLineDefs[i] << std::endl;
#endif
    }

    return levelLineDefs;
}