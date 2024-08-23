#include <iostream>
#include "./headers/Lump.h"
#include <fstream>
#include <memory>
#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include "./headers/Vec2.h"
#include "./headers/ProcessLevelData.h"
#include "./headers/UtilFunctions.h"


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
    // File header found in the begginning of the file, should be IWAD or PWAD
    char header[5];

    fileByteReader->readBytesAsChar(header,4);
    std::cout << "Header is: " << header << std::endl;

    if(!(strcmp(header, "IWAD") == 0 || strcmp(header, "PWAD") == 0)) {
        std::cout << "Header must be IWAD or PWAD. header is: " << header << std::endl;
        return -1;
    }

    // Number of LUMP objects in the file 
    uint32_t numlumps = fileByteReader->readBytesAsUint32();
    // Offset to the infotables, the place where the lumps descriptions are found
    uint32_t infotableofs = fileByteReader->readBytesAsUint32();   

    std::cout << "Numlumps is: " << numlumps << " and infotablesOffset is: " << infotableofs << std::endl; 

    // Go to the infotables
    fileByteReader->pointer = infotableofs;
    // array of all Lump descriptions in the file
    std::shared_ptr<Lump[]> lumps = std::make_shared<Lump[]>(numlumps);
    for(int i = 0; i < numlumps; i++) {
        lumps[i] = fileByteReader->readLump();
        std::cout << "Loaded Lump[" << (i+1) << "] out of ["<< (numlumps) << "] <" << lumps[i] << ">" << std::endl;
    }
    std::cout << "Finished loading Lumps" << std::endl;

    // The end message of the file. written in ANSI compatible syntax
    std::string endoom = ENDOOM(*fileByteReader, lumps, numlumps);

     std::cout << endoom << std::endl;
    #ifdef debugPrint
        std::cin.get();
    #endif
    // Every "thing" object (monster, weapon, key etc.)
    std::shared_ptr<Thing[]> things = THINGS(*fileByteReader, lumps, numlumps);

    // When I understand them I will comment them lol.
    std::shared_ptr<LineDef[]> lineDefs = LINEDEFS(*fileByteReader, lumps, numlumps);
    std::shared_ptr<SideDef[]> sideDefs = SIDEDEFS(*fileByteReader, lumps, numlumps);
    std::shared_ptr<Seg[]> segs = SEGS(*fileByteReader, lumps, numlumps);
    std::shared_ptr<SubSector[]> subSectors = SSECTORS(*fileByteReader, lumps, numlumps);
    std::shared_ptr<Node[]> nodes = NODES(*fileByteReader, lumps, numlumps);
    std::shared_ptr<Sector[]> sectors = SECTORS(*fileByteReader, lumps, numlumps);
    std::shared_ptr<Vec2[]> vertexes = VERTEXES(*fileByteReader, lumps, numlumps);
    std::shared_ptr<Reject> reject = REJECT(*fileByteReader, lumps, numlumps);
    return 0;
}