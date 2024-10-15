#include "../headers/LevelData.h"
#include "../headers/UtilFunctions.h"

LevelData::LevelData(std::shared_ptr<Thing[]> things, size_t thingsLength, std::shared_ptr<LineDef[]> lineDefs, size_t lineDefsLength, std::shared_ptr<SideDef[]> sideDefs, size_t sideDefsLength, std::shared_ptr<Seg[]> segs, size_t segsLength, std::shared_ptr<SubSector[]> subSectors, size_t subSectorsLength, std::shared_ptr<Node[]> nodes, size_t nodesLength, std::shared_ptr<Sector[]> sectors, size_t sectorsLength, std::shared_ptr<Vec2[]> vertexes, size_t vertexesLength, std::shared_ptr<Reject> reject, std::shared_ptr<BlockMap> blockmap) : things(things), thingsLength(thingsLength), lineDefs(lineDefs), lineDefsLength(lineDefsLength), sideDefs(sideDefs), sideDefsLength(sideDefsLength), segs(segs), segsLength(segsLength), subSectors(subSectors), subSectorsLength(subSectorsLength), nodes(nodes), nodesLength(nodesLength), sectors(sectors), sectorsLength(sectorsLength), vertexes(vertexes), vertexesLength(vertexesLength), reject(reject), blockmap(blockmap) {}

std::ostream &operator<<(std::ostream &os, const LevelData &obj)
{
    os << "Level Data {" << std::endl;

    os << " things {" << std::endl;
    for (size_t i = 0; i < obj.thingsLength; i++)
    {
        os << "    " << obj.things[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " lineDefs {" << std::endl;
    for (size_t i = 0; i < obj.lineDefsLength; i++)
    {
        os << "    " << obj.lineDefs[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " sideDefs {" << std::endl;
    for (size_t i = 0; i < obj.sideDefsLength; i++)
    {
        os << "    " << obj.sideDefs[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " segs {" << std::endl;
    for (size_t i = 0; i < obj.segsLength; i++)
    {
        os << "    " << obj.segs[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " subSectors {" << std::endl;
    for (size_t i = 0; i < obj.subSectorsLength; i++)
    {
        os << "    " << obj.subSectors[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " nodes {" << std::endl;
    for (size_t i = 0; i < obj.nodesLength; i++)
    {
        os << "    " << obj.nodes[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " sectors {" << std::endl;
    for (size_t i = 0; i < obj.sectorsLength; i++)
    {
        os << "    " << obj.sectors[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " vertexes {" << std::endl;
    for (size_t i = 0; i < obj.vertexesLength; i++)
    {
        os << "    " << obj.vertexes[i] << std::endl;
    }
#ifdef debugPrint
    std::cin.get();
#endif

    os << "}" << std::endl;

    os << " reject " << *obj.reject << std::endl;

    os << " blockmap " << *obj.blockmap << std::endl;

    os << "}" << std::endl;
    return os;
}

std::shared_ptr<LevelData> GenerateLevelData(ConsecutiveBytearrayReader &fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to)
{
    std::string tagname = "THINGS";

    size_t levelThingLumpIndex = findInLumpArray(lumps, from, to, tagname);
    std::shared_ptr<Thing[]> things = THINGS(fileByteReader, lumps[levelThingLumpIndex], from, to);

    // When I understand them I will comment them lol.

    tagname = "LINEDEFS";
    size_t levelLineDefLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<LineDef[]> lineDefs = LINEDEFS(fileByteReader, lumps[levelLineDefLumpIndex], from, to);

    tagname = "SIDEDEFS";
    size_t levelSideDefLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<SideDef[]> sideDefs = SIDEDEFS(fileByteReader, lumps[levelSideDefLumpIndex], from, to);

    tagname = "SEGS";
    size_t levelSegLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<Seg[]> segs = SEGS(fileByteReader, lumps[levelSegLumpIndex], from, to);

    tagname = "SSECTORS";
    size_t levelSubSectorLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<SubSector[]> subSectors = SSECTORS(fileByteReader, lumps[levelSubSectorLumpIndex], from, to);

    tagname = "NODES";
    size_t levelNodeLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<Node[]> nodes = NODES(fileByteReader, lumps[levelNodeLumpIndex], from, to);

    tagname = "SECTORS";
    size_t levelSectorLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<Sector[]> sectors = SECTORS(fileByteReader, lumps[levelSectorLumpIndex], from, to);

    tagname = "VERTEXES";
    size_t levelVertexLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<Vec2[]> vertexes = VERTEXES(fileByteReader, lumps[levelVertexLumpIndex], from, to);

    // Reject Lump tagName
    tagname = "REJECT";
    // Reject Lump index
    size_t levelRejectLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<Reject> reject = REJECT(fileByteReader, lumps[levelRejectLumpIndex], lumps[levelSectorLumpIndex].size / 26, from, to);

    tagname = "BLOCKMAP";
    size_t levelBlockMapLumpIndex = findInLumpArray(lumps, from, to, tagname);

    std::shared_ptr<BlockMap> blockmap = BLOCKMAP(fileByteReader, lumps[levelBlockMapLumpIndex], from, to);
#ifdef debugPrint
    std::cin.get();
#endif
    return std::make_shared<LevelData>(things, lumps[levelThingLumpIndex].size / 10, lineDefs, lumps[levelLineDefLumpIndex].size / 14, sideDefs, lumps[levelSideDefLumpIndex].size / 30, segs, lumps[levelSegLumpIndex].size / 12, subSectors, lumps[levelSubSectorLumpIndex].size / 4, nodes, lumps[levelNodeLumpIndex].size / 28, sectors, lumps[levelSectorLumpIndex].size / 26, vertexes, lumps[levelVertexLumpIndex].size / 4, reject, blockmap);
}

std::shared_ptr<std::vector<std::shared_ptr<LevelData>>> GenerateLevels(ConsecutiveBytearrayReader &fileByteReader, WADHeader &wadHeader, std::shared_ptr<Lump[]> lumps)
{
    auto levels = std::make_shared<std::vector<std::shared_ptr<LevelData>>>();
    size_t level1Map1Index;
    // Name of level lump
    char mapname[] = {'M', 'A', 'P', '0', '0', 0};

    // First pass, if the name is in the MAPXX format
    for (size_t i = 0; i < 32; i++)
    {
        // str(i)
        mapname[3] = '0' + (i / 10);
        mapname[4] = '0' + (i % 10);

        level1Map1Index = findInLumpArray(lumps, 0, wadHeader.numlumps, mapname);

        if (level1Map1Index != -1)
        {
#ifdef debugPrint
            std::cout << mapname << std::endl;
            std::cin.get();
#endif

            levels->push_back(GenerateLevelData(fileByteReader, lumps, level1Map1Index, level1Map1Index + 11));
        }
    }

    mapname[0] = 'E';
    mapname[1] = '0';
    mapname[2] = 'M';
    mapname[3] = '0';
    mapname[4] = 0;

    for (size_t i = 1; i < 9; i++)
    {
        // Increase level's index
        mapname[1]++;
        for (size_t j = 1; j < 9; j++)
        {
            mapname[3]++;
            level1Map1Index = findInLumpArray(lumps, 0, wadHeader.numlumps, mapname);
            if (level1Map1Index != -1)
            {
#ifdef debugPrint
                std::cout << mapname << std::endl;
                std::cin.get();
#endif

                levels->push_back(GenerateLevelData(fileByteReader, lumps, level1Map1Index, level1Map1Index + 11));
            }
        }
    }
    return levels;
}