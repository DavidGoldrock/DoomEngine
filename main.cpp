#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include "./headers/Vec2.h"
#include "./headers/SpecialClassFunctions.h"
#include "./headers/UtilFunctions.h"
#include "./headers/LevelData.h"
#include "./headers/WADHeader.h"

int main()
{
    // The name of the wad. might be picked from directory or something in the future
    const std::string filename = "./resources/DOOM.wad";
    // the size of the file data. set by readFileToUint8Array
    size_t fileSize = 0;
    std::shared_ptr<uint8_t[]> fileData = readFileToUint8Array(filename, fileSize);

    // If the file couldn't be read for some reason, quit.
    if (fileSize == 0 or fileData == nullptr)
    {
        return -1;
    }

    std::cout << "File read successfully. Size: " << fileSize << " bytes." << std::endl;

    // a consecutive byte reader for the file, used by various functions
    std::unique_ptr<ConsecutiveBytearrayReader> fileByteReader = std::make_unique<ConsecutiveBytearrayReader>(fileData, fileSize);

    // Go to the infotables

    auto wadHeader = GenerateWADHeader(*fileByteReader);


    // The end message of the file. written in ANSI compatible syntax

    std::string tagname = "ENDOOM";
    size_t endoomLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);

    std::string endoom = ENDOOM(*fileByteReader, wadHeader->lumps[endoomLumpIndex], 0, wadHeader->numLumps);

    tagname = "PLAYPAL";
    size_t palleteLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    std::shared_ptr<PlayPal> playpal = PLAYPAL(*fileByteReader, wadHeader->lumps[palleteLumpIndex], 0, wadHeader->numLumps);

    tagname = "COLORMAP";
    size_t colorMapLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    std::shared_ptr<ColorMap> colorMap = COLORMAP(*fileByteReader, wadHeader->lumps[colorMapLumpIndex], 0, wadHeader->numLumps);

    tagname = "PNAMES";
    size_t pnamesLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    std::shared_ptr<std::string[]> pnames = PNAMES(*fileByteReader, wadHeader->lumps[pnamesLumpIndex], 0, wadHeader->numLumps);
    size_t pnameAmmount = (wadHeader->lumps[pnamesLumpIndex].size - 4) / 8;

    auto textures = std::vector<Texture>();

    tagname = "TEXTURE1";
    size_t texture1LumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    TEXTURE(*fileByteReader, wadHeader->lumps[texture1LumpIndex], 0, wadHeader->numLumps, textures);

    tagname = "TEXTURE2";
    size_t texture2LumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    TEXTURE(*fileByteReader, wadHeader->lumps[texture2LumpIndex], 0, wadHeader->numLumps, textures);

    std::cout << endoom << std::endl;
#ifdef debugPrint
    std::cin.get();
#endif

    // SaveAllPictures(*fileByteReader, *wadHeader, *playpal, *colorMap, pnames, pnameAmmount, textures);
    SaveAllSounds(*fileByteReader, *wadHeader);
    auto levels = GenerateLevels(*fileByteReader, *wadHeader);

    for (auto level : *levels)
    {
        // TODO: Code lol
    }

    return 0;
}