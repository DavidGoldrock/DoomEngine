#include <cstdint>
#include <cstring>
#include <iostream>
#include "Lump.h"
#include "Thing.h"
#include "LineDef.h"
#include "ConsecutiveBytearrayReader.h"
#include "SideDef.h"
#include "Seg.h"
#include "SubSector.h"
#include "Node.h"
#include "Sector.h"

int findInLumpArray(Lump* arr, size_t arrSize, std::string tagname);
    
bool bitAtLocation(size_t byte, size_t n);




//ENDDOOM

std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t* ansicode, size_t size);

void ENDOOM(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);


// THINGS


Thing* THINGS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);



// LINEDEFS

LineDef* LINEDEFS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);

// SIDEDEFS

SideDef* SIDEDEFS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);

// SEGS

Seg* SEGS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);


// """
// VERTEXES
// """


// def VERTEXES(br, levelLump: list[Lump]):
//     _, levelVertexsLump = findInLumpArray(levelLump, "VERTEXES")
//     data = br.readLumpData(levelVertexsLump)
//     br2 = ConsecutiveBytearrayReader(data)
//     levelVertexes = []
//     for i in range(levelVertexsLump.size // 4):
//         x = br2->readBytesAsUint16()
//         y = br2->readBytesAsUint16()
//         levelVertexes.append(np.array([x, y]))
//     return levelVertexes


// SSECTORS

SubSector* SSECTORS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);


// NODES

Node* NODES(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);


// SECTORS

// Sector* SECTORS(ConsecutiveBytearrayReader& br, Lump* lumps, size_t numlumps);


// def SECTORS(br, levelLump: list[Lump]):
//     _, levelSectorsLump = findInLumpArray(levelLump, "SECTORS")
//     data = br.readLumpData(levelSectorsLump)
//     br2 = ConsecutiveBytearrayReader(data)
//     levelSectors = []
//     for i in range(levelSectorsLump.size // 26):
//         floorHeight = br2->readBytesAsUint16()
//         ceilingHeight = br2->readBytesAsUint16()
//         floorTextureName = br2->readBytes(8, str).strip("\x00")
//         ceilingTextureName = br2->readBytes(8, str).strip("\x00")
//         lightLevel = br2->readBytesAsUint16()
//         specialTag = br2->readBytesAsUint16()
//         tagNumber = br2->readBytesAsUint16()

//         levelSectors.append(
//             Sector(floorHeight, ceilingHeight, floorTextureName, ceilingTextureName, lightLevel, specialTag, tagNumber))
//     return levelSectors


// """
// REJECT
// """


// def REJECT(br, levelLump: list[Lump]):
//     _, levelRejectLump = findInLumpArray(levelLump, "REJECT")
//     data = br.readLumpData(levelRejectLump)
//     rowSize = int(np.sqrt(len(data) * 8))
//     bitCount = 0
//     arr = []
//     while bitCount < levelRejectLump.size * 8:
//         byteIndex = bitCount // 8
//         bitIndex = bitCount % 8
//         arr.append(bitAtLocation(data[byteIndex], bitIndex))

//         bitCount += 1
//     matrix = np.array(matricise(arr, rowSize))
//     return matrix


// """
// BLOCKMAP
// """


// def BLOCKMAP(br, levelLump: list[Lump]):
//     _, levelBlockMapLump = findInLumpArray(levelLump, "BLOCKMAP")
//     data = br.readLumpData(levelBlockMapLump)
//     br2 = ConsecutiveBytearrayReader(data)

//     gridX = br2->readBytesAsUint16()
//     gridY = br2->readBytesAsUint16()
//     columnNumber = br2->readBytesAsUint16()
//     rowNumber = br2->readBytesAsUint16()

//     offsets = []

//     for i in range(columnNumber * rowNumber):
//         offsets.append(br2->readBytesAsUint16() * 2)

//     lineDefIndexByBlock = []

//     for i in range(columnNumber * rowNumber):
//         offset = offsets[i]
//         br2->pointer = offset
//         lineDefIndexByBlock.append([])

//         lineDefIndex = br2->readBytes(2)
//         assert lineDefIndex == b"\x00\x00"
//         lineDefIndex = br2->readBytes(2)
//         while lineDefIndex != b"\xff\xff":
//             lineDefIndexByBlock[i].append(int.from_bytes(lineDefIndex, 'little'))
//             lineDefIndex = br2->readBytes(2)
//     return BlockMap(gridX, gridY, columnNumber, rowNumber, offsets, lineDefIndexByBlock)


// def convert_playpal_to_palettes(playpal_data):
//     # Length of each palette in bytes
//     palette_size = 768
//     # Number of palettes in the lump
//     num_palettes = len(playpal_data) // palette_size

//     # Initialize list to hold palettes
//     palettes = []

//     for i in range(num_palettes):
//         palette_start_index = i * palette_size
//         palette = playpal_data[palette_start_index:palette_start_index + palette_size]
//         palettes.append(palette)

//     return palettes


// def convert_doom_picture_to_png(doom_image_data, palette_data, output_filename):
//     # Initialize the reader
//     br = ConsecutiveBytearrayReader(doom_image_data)

//     # Read image metadata
//     width = br.readBytesAsUint16()
//     height = br.readBytesAsUint16()
//     left = br.readBytesAsUint16()
//     top = br.readBytesAsUint16()

//     # Create an image with 8-bit color depth
//     image = Image.new('P', (width, height))

//     # Set the palette with DOOM's palette data
//     palette = [tuple(palette_data[i:i + 3]) for i in range(0, len(palette_data), 3)]
//     image.putpalette([c for color in palette for c in color] + [0] * (256 - len(palette)))

//     # Set the background color to cyan (index 1 in palette)
//     cyan_index = 1
//     image.paste(cyan_index, [0, 0, width, height])

//     # Create column array
//     column_array = [br.readBytes(4, int) for _ in range(width)]

//     # Read pixel data from each column
//     for i in range(width):
//         # Seek to the start of the column data
//         br.pointer = column_array[i]

//         while True:
//             rowstart = br.readBytes(1, int)
//             if rowstart == 255:
//                 break

//             pixel_count = br.readBytes(1, int)
//             br.readBytes(1)  # Read and ignore the dummy value

//             for j in range(pixel_count):
//                 pixel = br.readBytes(1, int)
//                 # Write Pixel to the image (column i, row rowstart + j)
//                 image.putpixel((i, rowstart + j), pixel)

//             # Read and ignore the dummy value
//             br.readBytes(1)

//     # Save the image as PNG
//     image.save(output_filename)
