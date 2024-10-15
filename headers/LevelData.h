#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include "Thing.h"
#include "LineDef.h"
#include "SideDef.h"
#include "Seg.h"
#include "SubSector.h"
#include "Node.h"
#include "Sector.h"
#include "Vec2.h"
#include "Reject.h"
#include "BlockMap.h"
#include "PlayPal.h"
#include "DoomSprite.h"
#include "SpecialClassFunctions.h"

struct LevelData
{
    std::shared_ptr<Thing[]> things;
    size_t thingsLength;
    std::shared_ptr<LineDef[]> lineDefs;
    size_t lineDefsLength;
    std::shared_ptr<SideDef[]> sideDefs;
    size_t sideDefsLength;
    std::shared_ptr<Seg[]> segs;
    size_t segsLength;
    std::shared_ptr<SubSector[]> subSectors;
    size_t subSectorsLength;
    std::shared_ptr<Node[]> nodes;
    size_t nodesLength;
    std::shared_ptr<Sector[]> sectors;
    size_t sectorsLength;
    std::shared_ptr<Vec2[]> vertexes;
    size_t vertexesLength;
    std::shared_ptr<Reject> reject;
    std::shared_ptr<BlockMap> blockmap;

    // Constructor
    LevelData(std::shared_ptr<Thing[]> things, size_t thingsLength, std::shared_ptr<LineDef[]> lineDefs, size_t lineDefsLength, std::shared_ptr<SideDef[]> sideDefs, size_t sideDefsLength, std::shared_ptr<Seg[]> segs, size_t segsLength, std::shared_ptr<SubSector[]> subSectors, size_t subSectorsLength, std::shared_ptr<Node[]> nodes, size_t nodesLength, std::shared_ptr<Sector[]> sectors, size_t sectorsLength, std::shared_ptr<Vec2[]> vertexes, size_t vertexesLength, std::shared_ptr<Reject> reject, std::shared_ptr<BlockMap> blockmap);

    friend std::ostream &operator<<(std::ostream &os, const LevelData &obj);
};

std::shared_ptr<LevelData> GenerateLevelData(ConsecutiveBytearrayReader &fileByteReader, WADHeader &wadHeader, size_t from, size_t to);

std::shared_ptr<std::vector<std::shared_ptr<LevelData>>> GenerateLevels(ConsecutiveBytearrayReader &fileByteReader, WADHeader &wadHeader);

#endif
