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
#include "PlayPal.h"
#include "DoomSprite.h"
#include "Texture.h"
#include "Flat.h"
#include <functional>


//ENDDOOM

std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t* ansicode, size_t size);

std::string ENDOOM(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// THINGS


std::shared_ptr<Thing[]> THINGS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// LINEDEFS

std::shared_ptr<LineDef[]> LINEDEFS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);

// SIDEDEFS

std::shared_ptr<SideDef[]> SIDEDEFS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);

// SEGS

std::shared_ptr<Seg[]> SEGS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// VERTEXES

std::shared_ptr<Vec2[]> VERTEXES(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// SSECTORS

std::shared_ptr<SubSector[]> SSECTORS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// NODES

std::shared_ptr<Node[]> NODES(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// SECTORS

std::shared_ptr<Sector[]> SECTORS(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);


// """
// REJECT
// """

std::shared_ptr<Reject> REJECT(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t sectorAmmount, size_t from, size_t to);


// """
// BLOCKMAP
// """

std::shared_ptr<BlockMap> BLOCKMAP(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);

// """
// PLAYPAL
// """

std::shared_ptr<PlayPal> PLAYPAL(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);

// """
// Pictures
// """

std::shared_ptr<DoomSprite> SPRITE(ConsecutiveBytearrayReader& fileByteReader, Lump& lump);

void writeToBMP(std::string &filename, const int32_t width, const int32_t height, std::function<uint8_t(size_t,size_t)> getPixel,  PlayPal &playpal, uint8_t palleteIndex);

std::shared_ptr<Flat> FLAT(ConsecutiveBytearrayReader& fileByteReader, Lump& lump);

// """
// PNAMES
//

std::shared_ptr<std::string[]> PNAMES(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);

std::shared_ptr<Texture[]> TEXTURE(ConsecutiveBytearrayReader& fileByteReader, Lump& lump, size_t from, size_t to);
