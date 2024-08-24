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
#include "Vec2.h"
#include "Reject.h"
#include "BlockMap.h"
#include "RGB.h"
#include "PlayPal.h"
#include "DoomPicture.h"


//ENDDOOM

std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t* ansicode, size_t size);

std::string ENDOOM(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// THINGS


std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// LINEDEFS

std::shared_ptr<LineDef[]> LINEDEFS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);

// SIDEDEFS

std::shared_ptr<SideDef[]> SIDEDEFS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);

// SEGS

std::shared_ptr<Seg[]> SEGS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// VERTEXES

std::shared_ptr<Vec2[]> VERTEXES(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// SSECTORS

std::shared_ptr<SubSector[]> SSECTORS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// NODES

std::shared_ptr<Node[]> NODES(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// SECTORS

std::shared_ptr<Sector[]> SECTORS(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// """
// REJECT
// """

std::shared_ptr<Reject> REJECT(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);


// """
// BLOCKMAP
// """

std::shared_ptr<BlockMap> BLOCKMAP(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);

std::shared_ptr<PlayPal> PLAYPAL(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);

std::shared_ptr<DoomPicture> PICTURE(ConsecutiveBytearrayReader& fileByteReader, Lump& lump);

void writeBMP(std::string &filename, DoomPicture &picture, PlayPal &playpal, uint8_t paletteIndex);

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
//     fileByteReader = ConsecutiveBytearrayReader(doom_image_data)

//     # Read image metadata
//     width = fileByteReader.readBytesAsUint16()
//     height = fileByteReader.readBytesAsUint16()
//     left = fileByteReader.readBytesAsUint16()
//     top = fileByteReader.readBytesAsUint16()

//     # Create an image with 8-bit color depth
//     image = Image.new('P', (width, height))

//     # Set the palette with DOOM's palette data
//     palette = [tuple(palette_data[i:i + 3]) for i in range(0, len(palette_data), 3)]
//     image.putpalette([c for color in palette for c in color] + [0] * (256 - len(palette)))

//     # Set the background color to cyan (index 1 in palette)
//     cyan_index = 1
//     image.paste(cyan_index, [0, 0, width, height])

//     # Create column array
//     column_array = [fileByteReader.readBytes(4, int) for _ in range(width)]

//     # Read pixel data from each column
//     for i in range(width):
//         # Seek to the start of the column data
//         fileByteReader.pointer = column_array[i]

//         while True:
//             rowstart = fileByteReader.readBytes(1, int)
//             if rowstart == 255:
//                 fileByteReadereak

//             pixel_count = fileByteReader.readBytes(1, int)
//             fileByteReader.readBytes(1)  # Read and ignore the dummy value

//             for j in range(pixel_count):
//                 pixel = fileByteReader.readBytes(1, int)
//                 # Write Pixel to the image (column i, row rowstart + j)
//                 image.putpixel((i, rowstart + j), pixel)

//             # Read and ignore the dummy value
//             fileByteReader.readBytes(1)

//     # Save the image as PNG
//     image.save(output_filename)
