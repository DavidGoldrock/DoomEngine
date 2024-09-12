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
    #ifdef debugPrint
        std::cin.get();
    #endif
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

    auto getTitlePicPixel = [titlePic](size_t x, size_t y) {return titlePic->getPixel(x,y);};

    writeToBMP(outputFileName, titlePic->width, titlePic->height, getTitlePicPixel, playpal, 0);


    size_t spriteStartIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "S_START");
    size_t spriteEndIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "S_END");

    std::shared_ptr<DoomSprite> pic;
    auto getPicPixel = [pic](size_t x, size_t y) {return pic->getPixel(x,y);};
    

    for (size_t picIndex = spriteStartIndex + 1; picIndex < spriteEndIndex; picIndex++)
    {
        pic = SPRITE(fileByteReader, lumps[picIndex]);
        outputFileName = folder + "SPRITE_" + lumps[picIndex].name +  ".bmp";
        writeToBMP(outputFileName, pic->width, pic->height, getPicPixel, playpal, 0);
    }

    size_t patchStartIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "P1_START");
    size_t patchEndIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "P1_END");

    #ifdef debugPrint
        std::cout << "patchStartIndex" << patchStartIndex << std::endl;
        std::cout << "patchEndIndex" << patchEndIndex << std::endl;
    #endif

    for (size_t picIndex = patchStartIndex + 1; picIndex < patchEndIndex; picIndex++)
    {
        pic = SPRITE(fileByteReader, lumps[picIndex]);
        outputFileName = folder + "PATCH_" + lumps[picIndex].name +  ".bmp";
        writeToBMP(outputFileName, pic->width, pic->height, getPicPixel, playpal, 0);
    }

    patchStartIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "P2_START");
    patchEndIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "P2_END");

    #ifdef debugPrint
        std::cout << "patchStartIndex" << patchStartIndex << std::endl;
        std::cout << "patchEndIndex" << patchEndIndex << std::endl;
    #endif
    
    for (size_t picIndex = patchStartIndex + 1; picIndex < patchEndIndex; picIndex++)
    {
        pic = SPRITE(fileByteReader, lumps[picIndex]);
        outputFileName = folder + "PATCH_" + lumps[picIndex].name +  ".bmp";
        writeToBMP(outputFileName, pic->width, pic->height, getPicPixel, playpal, 0);
    }

    size_t flatStartIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "F1_START");
    size_t flatEndIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "F1_END");

    #ifdef debugPrint
        std::cout << "flatStartIndex" << flatStartIndex << std::endl;
        std::cout << "flatEndIndex" << flatEndIndex << std::endl;
    #endif

    std::shared_ptr<Flat> flat;
    auto getFlatPixel = [&](size_t x, size_t y) {return (x,y);};

    for (size_t picIndex = flatStartIndex + 1; picIndex < flatEndIndex; picIndex++)
    {
        flat = FLAT(fileByteReader, lumps[picIndex]);
        outputFileName = folder + "FLAT_" + lumps[picIndex].name +  ".bmp";
        writeToBMP(outputFileName, Flat::size, Flat::size, getFlatPixel, playpal, 0);
    }

    flatStartIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "F2_START");
    flatEndIndex = findInLumpArray(lumps, 0, wadHeader.numlumps, "F2_END");

    #ifdef debugPrint
        std::cout << "flatStartIndex" << flatStartIndex << std::endl;
        std::cout << "flatEndIndex" << flatEndIndex << std::endl;
    #endif

    for (size_t picIndex = flatStartIndex + 1; picIndex < flatEndIndex; picIndex++)
    {
        flat = FLAT(fileByteReader, lumps[picIndex]);
        outputFileName = folder + "FLAT_" + lumps[picIndex].name +  ".bmp";
        writeToBMP(outputFileName, Flat::size, Flat::size, getFlatPixel, playpal, 0);
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

 std::shared_ptr<std::vector<std::shared_ptr<LevelData>>> GenerateLevels(ConsecutiveBytearrayReader& fileByteReader, WADHeader& wadHeader, std::shared_ptr<Lump[]> lumps) {
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

        if (level1Map1Index != -1) {
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
            if (level1Map1Index != -1) {
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

    tagname = "TEXTURE1";
    size_t texture1LumpIndex = findInLumpArray(lumps, 0, wadHeader->numlumps, tagname);
    std::shared_ptr<Texture[]> texture1 = TEXTURE(*fileByteReader, lumps[texture1LumpIndex], 0, wadHeader->numlumps);

    std::cout << endoom << std::endl;
    #ifdef debugPrint
        std::cin.get();
    #endif

    SaveAllPictures(*fileByteReader, *wadHeader, lumps, *playpal);
    
    auto levels = GenerateLevels(*fileByteReader, *wadHeader, lumps);
    
    std::cin.get();
    for (auto level : *levels)
    {
        // TODO: Code lol
    }
    
    
    return 0;
}