#ifndef BLOCKMAP_H
#define BLOCKMAP_H

#include <cstdint>
#include <iostream>

struct BlockMap {
    uint16_t gridX;
    uint16_t gridY;
    uint16_t columnNumber;
    uint16_t rowNumber;
    uint16_t  offsets;
    uint16_t  lineDefIndexByBlock;

    // Constructor
    BlockMap(uint16_t gridX, uint16_t gridY, uint16_t columnNumber, uint16_t rowNumber, 
             uint16_t offsets, uint16_t lineDefIndexByBlock);

    friend std::ostream& operator<<(std::ostream& os, const BlockMap& obj);
};

#endif


