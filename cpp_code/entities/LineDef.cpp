#include "../headers/LineDef.h"
#include <cstdint>
#include <iostream>

struct LineDef {
    uint8_t startVertex;
    uint8_t endVertex;
    uint8_t flags;
    uint8_t sType;
    uint8_t sTag;
    uint8_t fSideDef;
    uint8_t bSideDef;
    bool blocksPM;
    bool blocksM;
    bool ts;
    bool upperTextureUnpegged;
    bool lowerTextureUnpegged;
    bool secret;
    bool blocksSound;
    bool neverAutoMap;
    bool alwaysAutoMap;

    LineDef(uint8_t startVertex, uint8_t endVertex, uint8_t flags, uint8_t sType, uint8_t sTag,
            uint8_t fSideDef, uint8_t bSideDef, bool blocksPM, bool blocksM, bool ts, 
            bool upperTextureUnpegged, bool lowerTextureUnpegged, bool secret, bool blocksSound, 
            bool neverAutoMap, bool alwaysAutoMap)
        : startVertex(startVertex), endVertex(endVertex), flags(flags), sType(sType), sTag(sTag),
          fSideDef(fSideDef), bSideDef(bSideDef), blocksPM(blocksPM), blocksM(blocksM), ts(ts),
          upperTextureUnpegged(upperTextureUnpegged), lowerTextureUnpegged(lowerTextureUnpegged), 
          secret(secret), blocksSound(blocksSound), neverAutoMap(neverAutoMap), alwaysAutoMap(alwaysAutoMap)
    {}

    friend std::ostream& operator<<(std::ostream& os, const LineDef& obj) {
        os << "LineDef{ ";
        os << "startVertex: " << obj.startVertex << " ";
        os << "endVertex: " << obj.endVertex << " ";
        os << "flags: " << obj.flags << " ";
        os << "sType: " << obj.sType << " ";
        os << "sTag: " << obj.sTag << " ";
        os << "fSideDef: " << obj.fSideDef << " ";
        os << "bSideDef: " << obj.bSideDef << " ";
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
};