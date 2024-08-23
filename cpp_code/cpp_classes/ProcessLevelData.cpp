#include "../headers/ProcessLevelData.h"
#include "../headers/UtilFunctions.h"

/**
 * @fileByteReaderief gets from a DOS screen format using ansi codes and implied \n to colored text running in CMD
 * 
 * @param ansicode 
 * @param size 
 * @return std::string 
 */
std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t* ansicode, size_t size)
{   
    // Replaces the original code (0-15) with ANSI version of same code
    uint8_t CodeDict[] =  {30,34,32,36,31,35,33,37,90,94, 92, 96, 91, 95, 93, 97};
    // string to be returned
    std::string ret;

    // Used to not place the color code for every letter, but rather for every change
    int lastForeground = -1;
    int lastBackground = -1;

    // Every character takes 2 bytes, first is character, second is color code
    for (size_t i = 0; i < size; i += 2) {
        // Get character
        char letter = static_cast<char>(ansicode[i]);
        // Get code
        uint8_t code = ansicode[i + 1];
        // First 4 bits: foreground color code
        uint8_t foreground = code & 15;
        // 3 bytes after that: background color code
        uint8_t background = (code & 112) >> 4;
        // Final bit: should text blink (unimplemented)
        bool isBlinking = bitAtLocation(code, 7);

        // if color changed from last character, add the correct ANSI code
        if (foreground != lastForeground) {
            uint8_t foregroundCode = CodeDict[foreground];
            ret += "\033[" + std::to_string(foregroundCode) + "m";
        }

        if (background != lastBackground) {
            uint8_t backgroundCode = CodeDict[background] + 10;
            ret += "\033[" + std::to_string(backgroundCode) + "m";
        }

        // Remember last color
        lastForeground = foreground;
        lastBackground = background;

        // Add letter
        ret += letter;
        
        // Add implicit \n. also reset colors for next line
        if ((i / 2 + 1) % 80 == 0) {
            ret += "\033[0m";
            ret += "\n";
            lastForeground = -1;
            lastBackground = -1;
        }
    }

    return ret;

}

/**
 * @fileByteReaderief reads the ENDOOM message in the correct format
 * 
 * @param fileByteReader The byte reader with the file bytearray contained
 * @param lumps descriptions of every lump object
 * @param numlumps the number of lumps in the file
 * @return the ENDOOM message in the correct format
 */
std::string ENDOOM(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    size_t index = findInLumpArray(lumps, numlumps,"ENDOOM");
    uint8_t data[lumps[index].size];
    fileByteReader.readLumpData(data, lumps[index]);
    return VGA_16BIT_COLOR_MEMORY_TO_STRING(data, lumps[index].size);
}

/* 
 * Every Function from this point on works in the same way
 * The Lump with the correct tagname is found in the lump array
 * Its data is read, place inside a ConsecutiveBytearrayReader
 * An array of the appropriate size is created
 * The data of each object is read in its regular format
*/

std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps){
    // Lump tagName
    std::string tagname = "THINGS";
    // Lump index
    size_t levelThingLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelThingLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelThingLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelThingLumpIndex].size);
    // Create array
    std::shared_ptr<Thing[]> levelThings = std::make_shared<Thing[]>(lumps[levelThingLumpIndex].size / 10);
    // Read using format
    for (size_t i = 0; i < lumps[levelThingLumpIndex].size / 10; i++) {
        levelThings[i].x = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].y = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].angle = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].doomType = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].flags = lumpDataByteReader->readBytesAsUint16();
        levelThings[i].skillLevel12 = bitAtLocation(levelThings[i].flags, 0);
        levelThings[i].skillLevel3 = bitAtLocation(levelThings[i].flags, 1);
        levelThings[i].skillLevel45 = bitAtLocation(levelThings[i].flags, 2);
        levelThings[i].deaf = bitAtLocation(levelThings[i].flags, 3);
        levelThings[i].notSinglePlayer = bitAtLocation(levelThings[i].flags, 4);

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Thing [" << (i+1) << "]" << " Out of [" << lumps[levelThingLumpIndex].size / 10 << "]" << levelThings[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelThings;
}

std::shared_ptr<LineDef[]> LINEDEFS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    // Lump tagName
    std::string tagname = "LINEDEFS";
    // Lump index
    size_t levelLineDefLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelLineDefLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelLineDefLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelLineDefLumpIndex].size);
    // Create array
    std::shared_ptr<LineDef[]> levelLineDefs = std::make_shared<LineDef[]>(lumps[levelLineDefLumpIndex].size / 14);
    // Read using format

    for (size_t i = 0; i < lumps[levelLineDefLumpIndex].size / 14; i++)
    {
        levelLineDefs[i].startVertex = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].endVertex = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].flags = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].sType = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].sTag = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].fSideDef = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].bSideDef = lumpDataByteReader->readBytesAsUint16();
        levelLineDefs[i].blocksPM = bitAtLocation(levelLineDefs[i].flags, 0);
        levelLineDefs[i].blocksM = bitAtLocation(levelLineDefs[i].flags, 1);
        levelLineDefs[i].ts = bitAtLocation(levelLineDefs[i].flags, 2);
        levelLineDefs[i].upperTextureUnpegged = bitAtLocation(levelLineDefs[i].flags, 3);
        levelLineDefs[i].lowerTextureUnpegged = bitAtLocation(levelLineDefs[i].flags, 4);
        levelLineDefs[i].secret = bitAtLocation(levelLineDefs[i].flags, 5);
        levelLineDefs[i].blocksSound = bitAtLocation(levelLineDefs[i].flags, 6);
        levelLineDefs[i].neverAutoMap = bitAtLocation(levelLineDefs[i].flags, 7);
        levelLineDefs[i].alwaysAutoMap = bitAtLocation(levelLineDefs[i].flags, 8);

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded LineDef [" << (i+1) << "]" << " Out of [" << lumps[levelLineDefLumpIndex].size / 14 << "]" << levelLineDefs[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelLineDefs;
}

std::shared_ptr<SideDef[]> SIDEDEFS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps){
    // Lump tagName
    std::string tagname = "SIDEDEFS";
    // Lump index
    size_t levelSideDefLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSideDefLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelSideDefLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSideDefLumpIndex].size);
    // Create array
    std::shared_ptr<SideDef[]> levelSideDefs = std::make_shared<SideDef[]>(lumps[levelSideDefLumpIndex].size / 30);
    // Read using format
    for (size_t i = 0; i < lumps[levelSideDefLumpIndex].size / 30; i++) {
        levelSideDefs[i].x = lumpDataByteReader->readBytesAsUint16();
        levelSideDefs[i].y = lumpDataByteReader->readBytesAsUint16();
        levelSideDefs[i].upperTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].lowerTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].middleTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].sectorNumber = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded SideDef [" << (i+1) << "]" << " Out of [" << lumps[levelSideDefLumpIndex].size / 30 << "]" << levelSideDefs[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSideDefs;
}


std::shared_ptr<Seg[]> SEGS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps){
    // Lump tagName
    std::string tagname = "SEGS";
    // Lump index
    size_t levelSegLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSegLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelSegLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSegLumpIndex].size);
    // Create array
    std::shared_ptr<Seg[]> levelSeg = std::make_shared<Seg[]>(lumps[levelSegLumpIndex].size / 12);
    // Read using format
    for (size_t i = 0; i < lumps[levelSegLumpIndex].size / 12; i++) {
        levelSeg[i].startingVertexNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].endingVertexNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].angle = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].lineDefNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].directionSameAsLineDef = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].offset = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Seg [" << (i+1) << "]" << " Out of [" << lumps[levelSegLumpIndex].size / 12 << "]" << levelSeg[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSeg;
}

std::shared_ptr<SubSector[]> SSECTORS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    // Lump tagName
    std::string tagname = "SSECTORS";
    // Lump index
    size_t levelSubSectorLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSubSectorLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelSubSectorLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSubSectorLumpIndex].size);
    // Create array
    std::shared_ptr<SubSector[]> levelSubSector = std::make_shared<SubSector[]>(lumps[levelSubSectorLumpIndex].size / 4);
    // Read using format
    for (size_t i = 0; i < lumps[levelSubSectorLumpIndex].size / 4; i++) {
        levelSubSector[i].segCount = lumpDataByteReader->readBytesAsUint16();
        levelSubSector[i].firstSegNumber = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded SubSector [" << (i+1) << "]" << " Out of [" << lumps[levelSubSectorLumpIndex].size / 4 << "]" << levelSubSector[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSubSector;
}

std::shared_ptr<Node[]> NODES(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    // Lump tagName
    std::string tagname = "NODES";
    // Lump index
    size_t levelNodeLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelNodeLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelNodeLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelNodeLumpIndex].size);
    // Create array
    std::shared_ptr<Node[]> levelNode = std::make_shared<Node[]>(lumps[levelNodeLumpIndex].size / 28);
    // Read using format
    for (size_t i = 0; i < lumps[levelNodeLumpIndex].size / 28; i++) {
        levelNode[i].x = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].y = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].deltaX = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].deltaY = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxTop = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxBottom = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxLeft = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxRight = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxTop = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxBottom = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxLeft = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxRight = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightChildIndex = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftChildIndex = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Node [" << (i+1) << "]" << " Out of [" << lumps[levelNodeLumpIndex].size / 28 << "]" << levelNode[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelNode;
}

std::shared_ptr<Sector[]> SECTORS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    // Lump tagName
    std::string tagname = "SECTORS";
    // Lump index
    size_t levelSectorLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelSectorLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelSectorLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelSectorLumpIndex].size);
    // Create array
    std::shared_ptr<Sector[]> levelSector = std::make_shared<Sector[]>(lumps[levelSectorLumpIndex].size / 26);
    // Read using format
    for (size_t i = 0; i < lumps[levelSectorLumpIndex].size / 26; i++) {
        levelSector[i].floorHeight = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].ceilingHeight = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].floorTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSector[i].ceilingTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSector[i].lightLevel = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].specialTag = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].tagNumber = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Sector [" << (i+1) << "]" << " Out of [" << lumps[levelSectorLumpIndex].size / 26 << "]" << levelSector[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSector;
}

std::shared_ptr<Vec2[]> VERTEXES(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    // Lump tagName
    std::string tagname = "VERTEXES";
    // Lump index
    size_t levelVertexLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelVertexLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelVertexLumpIndex]);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lumps[levelVertexLumpIndex].size);
    // Create array
    std::shared_ptr<Vec2[]> levelVertex = std::make_shared<Vec2[]>(lumps[levelVertexLumpIndex].size / 4);
    // Read using format
    for (size_t i = 0; i < lumps[levelVertexLumpIndex].size / 4; i++) {
        levelVertex[i].x = lumpDataByteReader->readBytesAsUint16();
        levelVertex[i].y = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Vertex [" << (i+1) << "]" << " Out of [" << lumps[levelVertexLumpIndex].size / 4 << "]" << levelVertex[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelVertex;
}

std::shared_ptr<Reject> REJECT(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t numlumps) {
    // Sector Lump tagname
    std::string tagname = "SECTORS";
    // Sector Lump index
    size_t levelSectorLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Reject Lump tagName
    tagname = "REJECT";
    // Reject Lump index
    size_t levelRejectLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lumps[levelRejectLumpIndex].size);
    fileByteReader.readLumpData(data.get(), lumps[levelRejectLumpIndex]);
    std::shared_ptr<Reject> rejectPointer = std::make_shared<Reject>(data , lumps[levelSectorLumpIndex].size / 26);

    #ifdef debugPrint
        std::cout << "Loaded Reject map " << *rejectPointer << std::endl;
        std::cin.get();
    #endif

    return rejectPointer;
}