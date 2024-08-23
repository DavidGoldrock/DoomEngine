#include "../headers/ProcessLevelData.h"

int findInLumpArray(Lump* arr, size_t arrSize, std::string tagname){
    for(size_t i = 0; i < arrSize; i ++) {
        if (arr[i].name == tagname)
            return i;
    }
    return -1;
}

bool bitAtLocation(size_t byte, size_t n){ 
    return (byte & (2 << n) >> n) == 1;
}

std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t* ansicode, size_t size)
{   
    uint8_t CodeDict[] =  {30,34,32,36,31,35,33,37,90,94, 92, 96, 91, 95, 93, 97};
    std::string ret;
    int lastForeground = -1;
    int lastBackground = -1;

    for (size_t i = 0; i < size; i += 2) {
        char letter = static_cast<char>(ansicode[i]);
        uint8_t code = ansicode[i + 1];
        int foreground = code & 15;
        int background = (code & 112) >> 4;
        bool isBlinking = bitAtLocation(code, 7);

        if (foreground != lastForeground) {
            int foregroundCode = CodeDict[foreground];
            ret += "\033[" + std::to_string(foregroundCode) + "m";
        }

        if (background != lastBackground) {
            int backgroundCode = CodeDict[background] + 10;
            ret += "\033[" + std::to_string(backgroundCode) + "m";
        }

        lastForeground = foreground;
        lastBackground = background;

        ret += letter;
        if ((i / 2 + 1) % 80 == 0) {
            ret += "\033[0m";
            ret += "\n";
            lastForeground = -1;
            lastBackground = -1;
        }
    }

    return ret;

}

void ENDOOM(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps) {
    int index = findInLumpArray(lumps, numlumps,"ENDOOM");
    uint8_t data[lumps[index].size];
    br.readLumpData(data, lumps[index]);
    std::string ENDOOM_text_decoded = VGA_16BIT_COLOR_MEMORY_TO_STRING(data, lumps[index].size);
    std::cout << ENDOOM_text_decoded << std::endl;
}
    
std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps){
    std::string tagname = "THINGS";
    size_t levelThingLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelThingLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelThingLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelThingLumpIndex].size);
    std::shared_ptr<Thing[]> levelThings = std::make_shared<Thing[]>(lumps[levelThingLumpIndex].size / 10);
    for (size_t i = 0; i < lumps[levelThingLumpIndex].size / 10; i++) {
        levelThings[i].x = br2->readBytesAsUint16();
        levelThings[i].y = br2->readBytesAsUint16();
        levelThings[i].angle = br2->readBytesAsUint16();
        levelThings[i].doomType = br2->readBytesAsUint16();
        levelThings[i].flags = br2->readBytesAsUint16();
        levelThings[i].skillLevel12 = bitAtLocation(levelThings[i].flags, 0);
        levelThings[i].skillLevel3 = bitAtLocation(levelThings[i].flags, 1);
        levelThings[i].skillLevel45 = bitAtLocation(levelThings[i].flags, 2);
        levelThings[i].deaf = bitAtLocation(levelThings[i].flags, 3);
        levelThings[i].notSinglePlayer = bitAtLocation(levelThings[i].flags, 4);

        std::cout << "Loaded Thing [" << (i+1) << "]" << " Out of [" << lumps[levelThingLumpIndex].size / 10 << "]" << levelThings[i] << std::endl;
    }
    std::cin.get();
    return levelThings;
}

LineDef* LINEDEFS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps) {
    std::string tagname = "LINEDEFS";
    size_t levelLineDefLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelLineDefLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelLineDefLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelLineDefLumpIndex].size);
    LineDef* levelLineDefs = new LineDef[lumps[levelLineDefLumpIndex].size / 14];

    for (size_t i = 0; i < lumps[levelLineDefLumpIndex].size / 14; i++)
    {
        levelLineDefs[i].startVertex = br2->readBytesAsUint16();
        levelLineDefs[i].endVertex = br2->readBytesAsUint16();
        levelLineDefs[i].flags = br2->readBytesAsUint16();
        levelLineDefs[i].sType = br2->readBytesAsUint16();
        levelLineDefs[i].sTag = br2->readBytesAsUint16();
        levelLineDefs[i].fSideDef = br2->readBytesAsUint16();
        levelLineDefs[i].bSideDef = br2->readBytesAsUint16();
        levelLineDefs[i].blocksPM = bitAtLocation(levelLineDefs[i].flags, 0);
        levelLineDefs[i].blocksM = bitAtLocation(levelLineDefs[i].flags, 1);
        levelLineDefs[i].ts = bitAtLocation(levelLineDefs[i].flags, 2);
        levelLineDefs[i].upperTextureUnpegged = bitAtLocation(levelLineDefs[i].flags, 3);
        levelLineDefs[i].lowerTextureUnpegged = bitAtLocation(levelLineDefs[i].flags, 4);
        levelLineDefs[i].secret = bitAtLocation(levelLineDefs[i].flags, 5);
        levelLineDefs[i].blocksSound = bitAtLocation(levelLineDefs[i].flags, 6);
        levelLineDefs[i].neverAutoMap = bitAtLocation(levelLineDefs[i].flags, 7);
        levelLineDefs[i].alwaysAutoMap = bitAtLocation(levelLineDefs[i].flags, 8);

        //std::cout << "Loaded LineDef [" << (i+1) << "]" << " Out of [" << lumps[levelLineDefLumpIndex].size / 10 << "]" << levelLineDefs[i] << std::endl;
    }
    return levelLineDefs;
}

SideDef* SIDEDEFS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps){
    std::string tagname = "SIDEDEFS";
    size_t levelSideDefLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSideDefLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelSideDefLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSideDefLumpIndex].size);
    SideDef* levelSideDefs = new SideDef[lumps[levelSideDefLumpIndex].size / 30];
    for (size_t i = 0; i < lumps[levelSideDefLumpIndex].size / 30; i++) {
        levelSideDefs[i].x = br2->readBytesAsUint16();
        levelSideDefs[i].y = br2->readBytesAsUint16();
        levelSideDefs[i].upperTextureName = br2->readBytesAsStr(8);
        levelSideDefs[i].lowerTextureName = br2->readBytesAsStr(8);
        levelSideDefs[i].middleTextureName = br2->readBytesAsStr(8);
        levelSideDefs[i].sectorNumber = br2->readBytesAsUint16();

        std::cout << "Loaded SideDef [" << (i+1) << "]" << " Out of [" << lumps[levelSideDefLumpIndex].size / 10 << "]" << levelSideDefs[i] << std::endl;
    }
    return levelSideDefs;
}


Seg* SEGS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps){
    std::string tagname = "SEGS";
    size_t levelSegLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSegLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelSegLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSegLumpIndex].size);
    Seg* levelSeg = new Seg[lumps[levelSegLumpIndex].size / 12];
    for (size_t i = 0; i < lumps[levelSegLumpIndex].size / 12; i++) {
        levelSeg[i].startingVertexNumber = br2->readBytesAsUint16();
        levelSeg[i].endingVertexNumber = br2->readBytesAsUint16();
        levelSeg[i].angle = br2->readBytesAsUint16();
        levelSeg[i].lineDefNumber = br2->readBytesAsUint16();
        levelSeg[i].directionSameAsLineDef = br2->readBytesAsUint16();
        levelSeg[i].offset = br2->readBytesAsUint16();

        std::cout << "Loaded Seg [" << (i+1) << "]" << " Out of [" << lumps[levelSegLumpIndex].size / 10 << "]" << levelSeg[i] << std::endl;
    }
    return levelSeg;
}

SubSector* SSECTORS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps) {
    std::string tagname = "SSECTORS";
    size_t levelSubSectorLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSubSectorLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelSubSectorLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSubSectorLumpIndex].size);
    SubSector* levelSubSector = new SubSector[lumps[levelSubSectorLumpIndex].size / 12];
    for (size_t i = 0; i < lumps[levelSubSectorLumpIndex].size / 12; i++) {
        levelSubSector[i].segCount = br2->readBytesAsUint16();
        levelSubSector[i].firstSegNumber = br2->readBytesAsUint16();

        std::cout << "Loaded SubSector [" << (i+1) << "]" << " Out of [" << lumps[levelSubSectorLumpIndex].size / 10 << "]" << levelSubSector[i] << std::endl;
    }
    return levelSubSector;
}

Node* NODES(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps) {
    std::string tagname = "NODES";
    size_t levelNodeLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelNodeLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelNodeLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelNodeLumpIndex].size);
    Node* levelNode = new Node[lumps[levelNodeLumpIndex].size / 28];
    for (size_t i = 0; i < lumps[levelNodeLumpIndex].size / 28; i++) {
        levelNode[i].x = br2->readBytesAsUint16();
        levelNode[i].y = br2->readBytesAsUint16();
        levelNode[i].deltaX = br2->readBytesAsUint16();
        levelNode[i].deltaY = br2->readBytesAsUint16();
        levelNode[i].rightBoundingBoxTop = br2->readBytesAsUint16();
        levelNode[i].rightBoundingBoxBottom = br2->readBytesAsUint16();
        levelNode[i].rightBoundingBoxLeft = br2->readBytesAsUint16();
        levelNode[i].rightBoundingBoxRight = br2->readBytesAsUint16();
        levelNode[i].leftBoundingBoxTop = br2->readBytesAsUint16();
        levelNode[i].leftBoundingBoxBottom = br2->readBytesAsUint16();
        levelNode[i].leftBoundingBoxLeft = br2->readBytesAsUint16();
        levelNode[i].leftBoundingBoxRight = br2->readBytesAsUint16();
        levelNode[i].rightChildIndex = br2->readBytesAsUint16();
        levelNode[i].leftChildIndex = br2->readBytesAsUint16();

        std::cout << "Loaded Node [" << (i+1) << "]" << " Out of [" << lumps[levelNodeLumpIndex].size / 10 << "]" << levelNode[i] << std::endl;
    }
    return levelNode;
}

Sector* SECTORS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps) {
    std::string tagname = "SECTORS";
    size_t levelSectorLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSectorLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelSectorLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSectorLumpIndex].size);
    Sector* levelSector = new Sector[lumps[levelSectorLumpIndex].size / 26];
    for (size_t i = 0; i < lumps[levelSectorLumpIndex].size / 26; i++) {
        levelSector[i].floorHeight = br2->readBytesAsUint16();
        levelSector[i].ceilingHeight = br2->readBytesAsUint16();
        levelSector[i].floorTextureName = br2->readBytesAsStr(8);
        levelSector[i].ceilingTextureName = br2->readBytesAsStr(8);
        levelSector[i].lightLevel = br2->readBytesAsUint16();
        levelSector[i].specialTag = br2->readBytesAsUint16();
        levelSector[i].tagNumber = br2->readBytesAsUint16();

        std::cout << "Loaded Sector [" << (i+1) << "]" << " Out of [" << lumps[levelSectorLumpIndex].size / 10 << "]" << levelSector[i] << std::endl;
    }
    return levelSector;
}

Vec2* VERTEXES(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps) {
    std::string tagname = "VERTEXES";
    size_t levelVertexLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelVertexLumpIndex].size);
    br.readLumpData(data.get(), lumps[levelVertexLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> br2 = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelVertexLumpIndex].size);
    Vec2* levelVertex = new Vec2[lumps[levelVertexLumpIndex].size / 26];
    for (size_t i = 0; i < lumps[levelVertexLumpIndex].size / 26; i++) {
        levelVertex[i].x = br2->readBytesAsUint16();
        levelVertex[i].y = br2->readBytesAsUint16();

        std::cout << "Loaded Vertex [" << (i+1) << "]" << " Out of [" << lumps[levelVertexLumpIndex].size / 10 << "]" << levelVertex[i] << std::endl;
    }
    return levelVertex;
}