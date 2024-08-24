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

// """
// PLAYPAL
// """

std::shared_ptr<PlayPal> PLAYPAL(ConsecutiveBytearrayReader& fileByteReader, std::shared_ptr<Lump[]> lumps, size_t from, size_t to);

// """
// Pictures
// """

std::shared_ptr<DoomPicture> PICTURE(ConsecutiveBytearrayReader& fileByteReader, Lump& lump);

void writeBMP(std::string &filename, DoomPicture &picture, PlayPal &playpal, uint8_t paletteIndex);
