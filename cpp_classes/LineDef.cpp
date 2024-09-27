#include "../headers/LineDef.h"
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
