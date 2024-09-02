#include "../headers/UtilFunctions.h"
#include "../headers/ProcessLevelData.h"
#include <PlayPal.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include <cstring>
#include <iostream>

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
        uint8_t foreground = code & 0b00001111;
        // 3 bytes after that: background color code
        uint8_t background = (code & 0b01110000) >> 4;
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
std::string ENDOOM(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    uint8_t data[lump.size];
    fileByteReader.readLumpData(data, lump);
    return VGA_16BIT_COLOR_MEMORY_TO_STRING(data, lump.size);
}

/* 
 * Every Function from this point on works in the same way
 * The Lump with the correct tagname is found in the lump array
 * Its data is read, place inside a ConsecutiveBytearrayReader
 * An array of the appropriate size is created
 * The data of each object is read in its regular format
*/

std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to){
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Thing[]> levelThings = std::make_shared<Thing[]>(lump.size / 10);
    // Read using format
    for (size_t i = 0; i < lump.size / 10; i++) {
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
            std::cout << "Loaded Thing [" << (i+1) << "]" << " Out of [" << lump.size / 10 << "]" << levelThings[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelThings;
}

std::shared_ptr<LineDef[]> LINEDEFS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<LineDef[]> levelLineDefs = std::make_shared<LineDef[]>(lump.size / 14);
    // Read using format

    for (size_t i = 0; i < lump.size / 14; i++)
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
            std::cout << "Loaded LineDef [" << (i+1) << "]" << " Out of [" << lump.size / 14 << "]" << levelLineDefs[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelLineDefs;
}

std::shared_ptr<SideDef[]> SIDEDEFS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to){
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<SideDef[]> levelSideDefs = std::make_shared<SideDef[]>(lump.size / 30);
    // Read using format
    for (size_t i = 0; i < lump.size / 30; i++) {
        levelSideDefs[i].x = lumpDataByteReader->readBytesAsUint16();
        levelSideDefs[i].y = lumpDataByteReader->readBytesAsUint16();
        levelSideDefs[i].upperTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].lowerTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].middleTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSideDefs[i].sectorNumber = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded SideDef [" << (i+1) << "]" << " Out of [" << lump.size / 30 << "]" << levelSideDefs[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSideDefs;
}


std::shared_ptr<Seg[]> SEGS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to){
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Seg[]> levelSeg = std::make_shared<Seg[]>(lump.size / 12);
    // Read using format
    for (size_t i = 0; i < lump.size / 12; i++) {
        levelSeg[i].startingVertexNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].endingVertexNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].angle = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].lineDefNumber = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].directionSameAsLineDef = lumpDataByteReader->readBytesAsUint16();
        levelSeg[i].offset = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Seg [" << (i+1) << "]" << " Out of [" << lump.size / 12 << "]" << levelSeg[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSeg;
}

std::shared_ptr<SubSector[]> SSECTORS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {

    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<SubSector[]> levelSubSector = std::make_shared<SubSector[]>(lump.size / 4);
    // Read using format
    for (size_t i = 0; i < lump.size / 4; i++) {
        levelSubSector[i].segCount = lumpDataByteReader->readBytesAsUint16();
        levelSubSector[i].firstSegNumber = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded SubSector [" << (i+1) << "]" << " Out of [" << lump.size / 4 << "]" << levelSubSector[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSubSector;
}

std::shared_ptr<Node[]> NODES(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Node[]> levelNode = std::make_shared<Node[]>(lump.size / 28);
    // Read using format
    for (size_t i = 0; i < lump.size / 28; i++) {
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
            std::cout << "Loaded Node [" << (i+1) << "]" << " Out of [" << lump.size / 28 << "]" << levelNode[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelNode;
}

std::shared_ptr<Sector[]> SECTORS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Sector[]> levelSector = std::make_shared<Sector[]>(lump.size / 26);
    // Read using format
    for (size_t i = 0; i < lump.size / 26; i++) {
        levelSector[i].floorHeight = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].ceilingHeight = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].floorTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSector[i].ceilingTextureName = lumpDataByteReader->readBytesAsStr(8);
        levelSector[i].lightLevel = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].specialTag = lumpDataByteReader->readBytesAsUint16();
        levelSector[i].tagNumber = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Sector [" << (i+1) << "]" << " Out of [" << lump.size / 26 << "]" << levelSector[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelSector;
}

std::shared_ptr<Vec2[]> VERTEXES(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Vec2[]> levelVertex = std::make_shared<Vec2[]>(lump.size / 4);
    // Read using format
    for (size_t i = 0; i < lump.size / 4; i++) {
        levelVertex[i].x = lumpDataByteReader->readBytesAsUint16();
        levelVertex[i].y = lumpDataByteReader->readBytesAsUint16();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded Vertex [" << (i+1) << "]" << " Out of [" << lump.size / 4 << "]" << levelVertex[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return levelVertex;
}

std::shared_ptr<Reject> REJECT(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t sectorAmmount, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::shared_ptr<Reject> rejectPointer = std::make_shared<Reject>(data , sectorAmmount);

    #ifdef debugPrint
        std::cout << "Loaded Reject map " << *rejectPointer << std::endl;
        std::cin.get();
    #endif

    return rejectPointer;
}

std::shared_ptr<BlockMap> BLOCKMAP(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    uint16_t gridX = lumpDataByteReader->readBytesAsUint16();
    uint16_t gridY = lumpDataByteReader->readBytesAsUint16();
    uint16_t columnNumber = lumpDataByteReader->readBytesAsUint16();
    uint16_t rowNumber = lumpDataByteReader->readBytesAsUint16();
    size_t offsets[rowNumber * columnNumber];

    for (size_t i = 0; i < rowNumber * columnNumber; i++)
    {
        offsets[i] = lumpDataByteReader->readBytesAsUint16() * 2;
    }

    std::shared_ptr<std::vector<uint16_t>[]> blocklists = std::make_shared<std::vector<uint16_t>[]>(rowNumber * columnNumber);

    uint8_t temp;

    for (size_t i = 0; i < rowNumber * columnNumber; i++)
    {
        lumpDataByteReader->pointer = offsets[i];

        temp = lumpDataByteReader->readBytesAsUint16();

        // First is always 0
        if (temp != 0) {
            std::cerr << "BLOCKLIST FAULTY" << std::endl;
        }

        // Add until value is -1
        temp = lumpDataByteReader->readBytesAsUint16();
        while(temp != 255) {
            blocklists[i].push_back(temp);
            temp = lumpDataByteReader->readBytesAsUint16();
        }

    }

    std::shared_ptr<BlockMap> blockMapPointer = std::make_shared<BlockMap>(gridX, gridY,columnNumber,rowNumber, blocklists);
    #ifdef debugPrint
        std::cout << "Loaded BlockMap map " << *blockMapPointer << std::endl;
        std::cin.get();
    #endif

    return blockMapPointer;
}

std::shared_ptr<PlayPal> PLAYPAL(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<uint8_t[]> levelPalleteData = std::make_shared<uint8_t[]>(lump.size);
    // Read using format
    for (size_t i = 0; i < lump.size; i+=3) {
        levelPalleteData[i] = lumpDataByteReader->readBytesAsUint8();
        levelPalleteData[i + 1] = lumpDataByteReader->readBytesAsUint8();
        levelPalleteData[i + 2] = lumpDataByteReader->readBytesAsUint8();

        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded RGB Value [" << ((i / 3)+1) << "]" << " Out of [" << lump.size / 3 << "]" << levelPalleteData[i] << std::endl;
        #endif
    }

    std::shared_ptr<PlayPal> returnValue = std::make_shared<PlayPal>(levelPalleteData);

    #ifdef debugPrint
        std::cout << "Loaded PlayPal " << *returnValue << std::endl;
        std::cin.get();
    #endif
    return returnValue;
}

std::shared_ptr<DoomSprite> SPRITE(ConsecutiveBytearrayReader& fileByteReader, Lump& lump) {
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    uint16_t width = lumpDataByteReader->readBytesAsUint16();
    uint16_t height = lumpDataByteReader->readBytesAsUint16();
    int16_t leftOffset = lumpDataByteReader->readBytesAsInt16();
    int16_t topOffset = lumpDataByteReader->readBytesAsInt16();

    size_t offsets[width];

    for (size_t i = 0; i < width; i++)
    {
        offsets[i] = lumpDataByteReader->readBytesAsUint32();
    }

    std::shared_ptr<uint8_t[]> pixels = std::make_shared<uint8_t[]>(width * height);
    std::shared_ptr<DoomSprite> pic = std::make_shared<DoomSprite>(width, height, leftOffset, topOffset, pixels);
    
    uint8_t rowstart;
    uint8_t pixel;
    uint8_t pixel_count;

    for (size_t i = 0; i < width; i++)
    {
        // Seek to the start of the column data
    lumpDataByteReader->pointer = offsets[i];
    rowstart = lumpDataByteReader->readBytesAsUint8();
        while(rowstart != 255) {    
            if (rowstart == 255) {
                break;
            }

            pixel_count = lumpDataByteReader->readBytesAsUint8();
            lumpDataByteReader->pointer++;  // Read and ignore the dummy value

            for (size_t j = 0; j < pixel_count; j++) {
                pixel = lumpDataByteReader->readBytesAsUint8();
                // Write Pixel to the image (column i, row rowstart + j)
                pic->pixels[i + (rowstart + j) * width] = pixel;
            }

            // Read and ignore the dummy value
            lumpDataByteReader->pointer++;
            rowstart = lumpDataByteReader->readBytesAsUint8();
        }
    }
    


    #ifdef debugPrint
        std::cout << "Loaded Picture " << *pic << std::endl;
        std::cin.get();
    #endif

    return pic;
}

void writeBMP(std::string &filename, DoomSprite &picture, PlayPal &playpal, uint8_t palleteIndex) {
    // BMP Header
    const int fileHeaderSize = 14;
    const int infoHeaderSize = 40;
    const int width = picture.width;
    const int height = picture.height;
    const int paddingSize = (4 - (width * 3) % 4) % 4;  // BMP rows are aligned to 4-byte boundaries
    const int fileSize = fileHeaderSize + infoHeaderSize + (width * 3 + paddingSize) * height;

    unsigned char fileHeader[fileHeaderSize] = {
        'B', 'M',             // Signature
        0, 0, 0, 0,           // Image file size in bytes
        0, 0, 0, 0,           // Reserved
        fileHeaderSize + infoHeaderSize, 0, 0, 0  // Start of pixel array
    };

    unsigned char infoHeader[infoHeaderSize] = {
        infoHeaderSize, 0, 0, 0,  // Header size
        0, 0, 0, 0,               // Image width
        0, 0, 0, 0,               // Image height
        1, 0,                     // Number of color planes
        24, 0,                    // Bits per pixel
        0, 0, 0, 0,               // Compression (0 = none)
        0, 0, 0, 0,               // Image size (can be 0 for uncompressed)
        0, 0, 0, 0,               // Horizontal resolution (pixels per meter, not important)
        0, 0, 0, 0,               // Vertical resolution (pixels per meter, not important)
        0, 0, 0, 0,                // Number of colors in palette
        0, 0, 0, 0                // Important colors (0 = all)
    };

    // Fill file size
    fileHeader[2] = static_cast<unsigned char>(fileSize);
    fileHeader[3] = static_cast<unsigned char>(fileSize >> 8);
    fileHeader[4] = static_cast<unsigned char>(fileSize >> 16);
    fileHeader[5] = static_cast<unsigned char>(fileSize >> 24);

    // Fill width and height
    infoHeader[4] = static_cast<unsigned char>(width);
    infoHeader[5] = static_cast<unsigned char>(width >> 8);
    infoHeader[6] = static_cast<unsigned char>(width >> 16);
    infoHeader[7] = static_cast<unsigned char>(width >> 24);
    infoHeader[8] = static_cast<unsigned char>(height);
    infoHeader[9] = static_cast<unsigned char>(height >> 8);
    infoHeader[10] = static_cast<unsigned char>(height >> 16);
    infoHeader[11] = static_cast<unsigned char>(height >> 24);

    // Write headers
    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    file.write(reinterpret_cast<char*>(infoHeader), infoHeaderSize);
    uint8_t* color;
    // Write the image buffer to the BMP file
    for (int y = height - 1; y >= 0; --y) {  // BMP files store pixels from bottom to top
        for (int x = 0; x < width; ++x) {
            // Get the pointer to the part of the pallette corrisponsing to the correct color
            // You go to the correct pallette, and then to the right part of it, then * 3 for the size of color
            color = &(playpal.getPallette(palleteIndex)[picture.pixels[y * width + x] * 3]);
            file.put(color[2]).put(color[1]).put(color[0]);
        }
        file.write("\0\0\0", paddingSize);  // Add padding
    }

    file.close();
}

std::shared_ptr<std::string[]> PNAMES(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to) {
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);

    size_t entryNum = lumpDataByteReader->readBytesAsInt32();

    // Create array
    std::shared_ptr<std::string[]> pnames = std::make_shared<std::string[]>(entryNum);
    // Read using format
    for (size_t i = 0; i <entryNum; i++) {
        pnames[i] = lumpDataByteReader->readBytesAsStr(8);
        // Print if debugPrint is on
        #ifdef debugPrint
            std::cout << "Loaded std::string [" << (i+1) << "]" << " Out of [" << entryNum << "]" << pnames[i] << std::endl;
        #endif
    }
    #ifdef debugPrint
        std::cin.get();
    #endif
    return pnames;
}