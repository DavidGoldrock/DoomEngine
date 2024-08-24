#include "../headers/LevelData.h"
#include "../headers/UtilFunctions.h"

LevelData::LevelData(std::shared_ptr<Thing[]> things, size_t thingsLength, std::shared_ptr<LineDef[]> lineDefs, size_t lineDefsLength, std::shared_ptr<SideDef[]> sideDefs, size_t sideDefsLength, std::shared_ptr<Seg[]> segs, size_t segsLength, std::shared_ptr<SubSector[]> subSectors, size_t subSectorsLength, std::shared_ptr<Node[]> nodes, size_t nodesLength, std::shared_ptr<Sector[]> sectors, size_t sectorsLength, std::shared_ptr<Vec2[]> vertexes, size_t vertexesLength, std::shared_ptr<Reject> reject, std::shared_ptr<BlockMap> blockmap): 
things(things), thingsLength(thingsLength), lineDefs(lineDefs), lineDefsLength(lineDefsLength), sideDefs(sideDefs), sideDefsLength(sideDefsLength), segs(segs), segsLength(segsLength), subSectors(subSectors), subSectorsLength(subSectorsLength), nodes(nodes), nodesLength(nodesLength), sectors(sectors), sectorsLength(sectorsLength), vertexes(vertexes), vertexesLength(vertexesLength), reject(reject), blockmap(blockmap) {}

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

    os << " reject "  << *obj.reject << std::endl; 

    os << " blockmap "  << *obj.blockmap << std::endl; 
    
    os << "}" << std::endl;
    return os;
}