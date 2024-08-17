#ifndef LINEDEF_H
#define LINEDEF_H

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

    // Constructor
    LineDef(uint8_t startVertex, uint8_t endVertex, uint8_t flags, uint8_t sType, uint8_t sTag,
            uint8_t fSideDef, uint8_t bSideDef, bool blocksPM, bool blocksM, bool ts, 
            bool upperTextureUnpegged, bool lowerTextureUnpegged, bool secret, bool blocksSound, 
            bool neverAutoMap, bool alwaysAutoMap);
    

    friend std::ostream& operator<<(std::ostream& os, const LineDef& obj);
};

#endif
