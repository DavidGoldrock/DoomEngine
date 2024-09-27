#ifndef BLOCKMAP_H
#define BLOCKMAP_H

#include <cstdint>
#include <memory>
#include <iostream>
#include <vector>

struct BlockMap
{
    uint16_t gridX;
    uint16_t gridY;
    uint16_t columnNumber;
    uint16_t rowNumber;
    std::shared_ptr<std::vector<uint16_t>[]> blocklists;

    // Constructor
    BlockMap(uint16_t gridX, uint16_t gridY, uint16_t columnNumber, uint16_t rowNumber, std::shared_ptr<std::vector<uint16_t>[]> blocklists);

    friend std::ostream &operator<<(std::ostream &os, const BlockMap &obj);
};

#endif
