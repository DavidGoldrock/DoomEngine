#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include "./headers/Vec2.h"
#include "./headers/ProcessLevelData.h"
#include "./headers/UtilFunctions.h"
#include "./headers/LevelData.h"
#include "WADHeader.h"


std::shared_ptr<LevelData> GenerateLevelData(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to) {
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

    return std::make_shared<LevelData>(things, lumps[levelThingLumpIndex].size / 10, lineDefs, lumps[levelLineDefLumpIndex].size / 14, sideDefs, lumps[levelSideDefLumpIndex].size / 30, segs, lumps[levelSegLumpIndex].size / 12, subSectors, lumps[levelSubSectorLumpIndex].size / 4, nodes, lumps[levelNodeLumpIndex].size / 28, sectors, lumps[levelSectorLumpIndex].size / 26, vertexes, lumps[levelVertexLumpIndex].size / 4, reject, blockmap);
}

std::shared_ptr<Lump[]> GenerateLumps(ConsecutiveBytearrayReader& fileByteReader, size_t numlumps) {
    // array of all Lump descriptions in the file
    std::shared_ptr<Lump[]> lumps = std::make_shared<Lump[]>(numlumps);
    for(int i = 0; i < numlumps; i++) {
        lumps[i] = fileByteReader.readLump();
        #ifdef debugPrint
            std::cout << "Loaded Lump[" << (i+1) << "] out of ["<< (numlumps) << "] <" << lumps[i] << ">" << std::endl;
        #endif
    }

    #ifdef debugPrint
        std::cout << "Finished loading Lumps" << std::endl;
        std::cin.get();
    #endif

    return lumps;
}

void SaveAllPictures(ConsecutiveBytearrayReader& fileByteReader, WADHeader& wadHeader, std::shared_ptr<Lump[]> lumps, PlayPal& playpal) {
    size_t titlePicIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "TITLEPIC");
    std::shared_ptr<DoomSprite> titlePic = SPRITE(fileByteReader, lumps[titlePicIndex]);

    const std::string folder = "./results/";

    std::string outputFileName = folder + lumps[titlePicIndex].name +  ".bmp";

    writeBMP(outputFileName , *titlePic, playpal, 0);


    size_t spriteStartIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "S_START");
    size_t spriteEndIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "S_END");

    std::shared_ptr<DoomSprite> pic;

    for (size_t picIndex = spriteStartIndex + 1; picIndex < spriteEndIndex; picIndex++)
    {
        pic = SPRITE(fileByteReader, lumps[picIndex]);
        outputFileName = folder + lumps[picIndex].name +  ".bmp";
        writeBMP(outputFileName , *pic, playpal, 0);
    }
}

std::shared_ptr<WADHeader> GenerateWADHeader(ConsecutiveBytearrayReader& fileByteReader) {
    // File header found in the begginning of the file, should be IWAD or PWAD
    std::string header = fileByteReader.readBytesAsStr(4);
    std::cout << "Header is: " << header << std::endl;

    if(!(header == "IWAD" || header == "PWAD")) {
        std::cout << "Header must be IWAD or PWAD. header is: " << header << std::endl;
        return nullptr;
    }

    // Number of LUMP objects in the file 
    uint32_t numlumps = fileByteReader.readBytesAsUint32();
    // Offset to the infotables, the place where the lumps descriptions are found
    uint32_t infotableofs = fileByteReader.readBytesAsUint32();   

    #ifdef debugPrint
        std::cout << "Numlumps is: " << numlumps << " and infotablesOffset is: " << infotableofs << std::endl; 
        std::cin.get();
    #endif

    return std::make_shared<WADHeader>(header,numlumps,infotableofs);
}

int main() {
    // The name of the wad. might be picked from directory or something in the future
    const std::string filename = "./resources/DOOM.wad";
    // the size of the file data. set by readFileToUint8Array
    size_t fileSize = 0;
    std::shared_ptr<uint8_t[]> fileData = readFileToUint8Array(filename, fileSize);

    // If the file couldn't be read for some reason, quit.
    if (fileSize == 0 or fileData == nullptr) {
        return -1;
    }

    std::cout << "File read successfully. Size: " << fileSize << " bytes." << std::endl;

    // a consecutive byte reader for the file, used by various functions 
    std::unique_ptr<ConsecutiveBytearrayReader> fileByteReader = std::make_unique<ConsecutiveBytearrayReader>(fileData, fileSize);

    // Go to the infotables

    auto wadHeader = GenerateWADHeader(*fileByteReader);

    fileByteReader->pointer = wadHeader->infotableofs;
    auto lumps = GenerateLumps(*fileByteReader, wadHeader->numlumps);

    // The end message of the file. written in ANSI compatible syntax

    std::string tagname = "ENDOOM";
    size_t endoomLumpIndex = findInLumpArray(lumps, 0, wadHeader->numlumps, tagname);

    std::string endoom = ENDOOM(*fileByteReader, lumps[endoomLumpIndex], 0, wadHeader->numlumps);

    tagname = "PLAYPAL";
    size_t palleteLumpIndex = findInLumpArray(lumps, 0, wadHeader->numlumps, tagname);
    std::shared_ptr<PlayPal> playpal = PLAYPAL(*fileByteReader, lumps[palleteLumpIndex], 0, wadHeader->numlumps);

    tagname = "PNAMES";
    size_t pnamesLumpIndex = findInLumpArray(lumps, 0, wadHeader->numlumps, tagname);
    std::shared_ptr<std::string[]> pnames = PNAMES(*fileByteReader, lumps[pnamesLumpIndex], 0, wadHeader->numlumps);
    size_t pnameAmmount = (lumps[pnamesLumpIndex].size - 4) / 8;

    std::cout << endoom << std::endl;
    #ifdef debugPrint
        std::cin.get();
    #endif

    SaveAllPictures(*fileByteReader, *wadHeader, lumps, *playpal);

    size_t level1Map1Index = findInLumpArray(lumps, 0, wadHeader->numlumps, "E1M1");
    auto level1 = GenerateLevelData(*fileByteReader, lumps, level1Map1Index, level1Map1Index + 11);
    std::cout << *level1 << std::endl;
    return 0;
}