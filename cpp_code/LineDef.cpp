#include "./headers/LineDef.h"
#include <cstdint>
#include <iostream>

std::ostream& operator<<(std::ostream& os, const LineDef& obj) {
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