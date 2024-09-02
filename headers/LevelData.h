#ifndef LEVEL_DATA_H
#define LEVEL_DATA_H

#include <cstdint>
#include <memory>
#include <vector>
#include <iostream>
#include "Lump.h"
#include "Thing.h"
#include "LineDef.h"
#include "ConsecutiveBytearrayReader.h"
#include "SideDef.h"
#include "Seg.h"
#include "SubSector.h"
#include "Node.h"
#include "Sector.h"
#include "Vec2.h"
#include "Reject.h"
#include "BlockMap.h"
#include "PlayPal.h"
#include "DoomPicture.h"

struct LevelData {
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
    

    friend std::ostream& operator<<(std::ostream& os, const LevelData& obj);
};

#endif
