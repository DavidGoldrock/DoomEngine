#include "../headers/UtilFunctions.h"
#include "../headers/SpecialClassFunctions.h"
#include <PlayPal.h>
#include <fstream>
#include <vector>
#include <cstring>
#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <cstring>
#include <iostream>
#include <functional>
#include <Sound.h>

/**
 * @fileByteReaderief gets from a DOS screen format using ansi codes and implied \n to colored text running in CMD
 *
 * @param ansicode
 * @param size
 * @return std::string
 */
std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t *ansicode, size_t size)
{
    // Replaces the original code (0-15) with ANSI version of same code
    uint8_t CodeDict[] = {30, 34, 32, 36, 31, 35, 33, 37, 90, 94, 92, 96, 91, 95, 93, 97};
    // string to be returned
    std::string ret;

    // Used to not place the color code for every letter, but rather for every change
    int lastForeground = -1;
    int lastBackground = -1;

    // Every character takes 2 bytes, first is character, second is color code
    for (size_t i = 0; i < size; i += 2)
    {
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
        if (foreground != lastForeground)
        {
            uint8_t foregroundCode = CodeDict[foreground];
            ret += "\033[" + std::to_string(foregroundCode) + "m";
        }

        if (background != lastBackground)
        {
            uint8_t backgroundCode = CodeDict[background] + 10;
            ret += "\033[" + std::to_string(backgroundCode) + "m";
        }

        // Remember last color
        lastForeground = foreground;
        lastBackground = background;

        // Add letter
        ret += letter;

        // Add implicit \n. also reset colors for next line
        if ((i / 2 + 1) % 80 == 0)
        {
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
std::string ENDOOM(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
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


std::shared_ptr<Vec2[]> VERTEXES(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Vec2[]> levelVertex = std::make_shared<Vec2[]>(lump.size / 4);
    // Read using format
    for (size_t i = 0; i < lump.size / 4; i++)
    {
        levelVertex[i].x = lumpDataByteReader->readBytesAsUint16();
        levelVertex[i].y = lumpDataByteReader->readBytesAsUint16();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded Vertex [" << (i + 1) << "]" << " Out of [" << lump.size / 4 << "]" << levelVertex[i] << std::endl;
#endif
    }

    return levelVertex;
}

std::shared_ptr<std::string[]> PNAMES(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);

    size_t entryNum = lumpDataByteReader->readBytesAsInt32();

    // Create array
    std::shared_ptr<std::string[]> pnames = std::make_shared<std::string[]>(entryNum);
    // Read using format
    for (size_t i = 0; i < entryNum; i++)
    {
        pnames[i] = lumpDataByteReader->readBytesAsStr(8);
        // Capitalize
        for (auto & c: pnames[i]) c = toupper(c);
// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded name [" << (i + 1) << "]" << " Out of [" << entryNum << "]" << pnames[i] << std::endl;
#endif
    }

    return pnames;
}

void TEXTURE(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to, std::vector<Texture> &textures)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);

    size_t entryNum = lumpDataByteReader->readBytesAsInt32();

    // Create array
    std::shared_ptr<int32_t[]> offsets = std::make_shared<int32_t[]>(entryNum);
    // Read using format

    for (size_t i = 0; i < entryNum; i++)
    {
        offsets[i] = lumpDataByteReader->readBytesAsInt32();
    }

    Texture texture;

    for (size_t i = 0; i < entryNum; i++)
    {
        texture = Texture();

        lumpDataByteReader->pointer = offsets[i];
        texture.name = lumpDataByteReader->readBytesAsStr(8);

        lumpDataByteReader->pointer += 4;

        texture.width = lumpDataByteReader->readBytesAsInt16();
        texture.height = lumpDataByteReader->readBytesAsInt16();

        // Skip unnecceary
        lumpDataByteReader->pointer += 4;

        texture.patchCount = lumpDataByteReader->readBytesAsInt16();
        texture.patches = std::make_shared<Patch[]>(texture.patchCount);

        for (size_t j = 0; j < texture.patchCount; j++)
        {
            texture.patches[j].originX = lumpDataByteReader->readBytesAsInt16();
            texture.patches[j].originY = lumpDataByteReader->readBytesAsInt16();
            texture.patches[j].patchNum = lumpDataByteReader->readBytesAsInt16();

            // Skip unnecceary
            lumpDataByteReader->pointer += 4;
        }

        textures.push_back(texture);

#ifdef debugPrint
        std::cout << "Loaded texture [" << (i + 1) << "]" << " Out of [" << entryNum << "]" << textureArray[i] << std::endl;
#endif
    }
}

void writeToBMP(std::string &filename, const int32_t width, const int32_t height, std::function<uint8_t(size_t, size_t)> getPixel, PlayPal &playpal, uint8_t palleteIndex, ColorMap &colorMap, uint8_t MapIndex)
{
    // BMP Header
    const int32_t fileHeaderSize = 14;
    const int32_t infoHeaderSize = 40;
    const int32_t paddingSize = (4 - (width * 3) % 4) % 4; // BMP rows are aligned to 4-byte boundaries
    const int32_t fileSize = fileHeaderSize + infoHeaderSize + (width * 3 + paddingSize) * height;

    // Written in a buffer and then written because writing to file many times is very expensive

    auto buffer = std::make_unique<char[]>(fileSize);
    size_t index = 0;

    uint8_t fileHeader[fileHeaderSize] = {
        'B', 'M',                                // Signature
        0, 0, 0, 0,                              // Image file size in bytes
        0, 0, 0, 0,                              // Reserved
        fileHeaderSize + infoHeaderSize, 0, 0, 0 // Start of pixel array
    };

    uint8_t infoHeader[infoHeaderSize] = {
        infoHeaderSize, 0, 0, 0, // Header size
        0, 0, 0, 0,              // Image width
        0, 0, 0, 0,              // Image height
        1, 0,                    // Number of color planes
        24, 0,                   // Bits per pixel
        0, 0, 0, 0,              // Compression (0 = none)
        0, 0, 0, 0,              // Image size (can be 0 for uncompressed)
        0, 0, 0, 0,              // Horizontal resolution (pixels per meter, not important)
        0, 0, 0, 0,              // Vertical resolution (pixels per meter, not important)
        0, 0, 0, 0,              // Number of colors in palette
        0, 0, 0, 0               // Important colors (0 = all)
    };

    // Fill file size
    fileHeader[2] = static_cast<uint8_t>(fileSize);
    fileHeader[3] = static_cast<uint8_t>(fileSize >> 8);
    fileHeader[4] = static_cast<uint8_t>(fileSize >> 16);
    fileHeader[5] = static_cast<uint8_t>(fileSize >> 24);

    // Fill width and height
    infoHeader[4] = static_cast<uint8_t>(width);
    infoHeader[5] = static_cast<uint8_t>(width >> 8);
    infoHeader[6] = static_cast<uint8_t>(width >> 16);
    infoHeader[7] = static_cast<uint8_t>(width >> 24);
    infoHeader[8] = static_cast<uint8_t>(height);
    infoHeader[9] = static_cast<uint8_t>(height >> 8);
    infoHeader[10] = static_cast<uint8_t>(height >> 16);
    infoHeader[11] = static_cast<uint8_t>(height >> 24);

    // Write headers
    std::memcpy(buffer.get() + index, &fileHeader, fileHeaderSize);
    index += fileHeaderSize;
    std::memcpy(buffer.get() + index, &infoHeader, infoHeaderSize);
    index += infoHeaderSize;

    uint8_t *color;

    // Write the image buffer to the BMP file
    for (int y = height - 1; y >= 0; --y)
    { // BMP files store pixels from bottom to top
        for (int x = 0; x < width; ++x)
        {
            // Get the pointer to the part of the pallette corrisponsing to the correct color
            // You go to the correct pallette, and then to the right part of it, then convert using colorMap
            // then * 3 for the size of color
            color = &(playpal.getPallette(palleteIndex)[colorMap.getMap(MapIndex)[getPixel(x, y)] * 3]);
            buffer[index++] = color[2];
            buffer[index++] = color[1];
            buffer[index++] = color[0];
        }
        for (size_t i = 0; i < paddingSize; i++)
        {
            buffer[index++] = 0;
        }
    }

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file.write(buffer.get(), fileSize);
    file.close();
}