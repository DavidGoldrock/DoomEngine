#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
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
#include "ColorMap.h"
#include "Sound.h"
#include "WADHeader.h"

// ENDDOOM

std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t *ansicode, size_t size);

std::string ENDOOM(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

std::shared_ptr<Vec2[]> VERTEXES(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

std::shared_ptr<std::string[]> PNAMES(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to);

void TEXTURE(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to, std::vector<Texture> &textures);

void writeToBMP(std::string &filename, const int32_t width, const int32_t height, std::function<uint8_t(size_t, size_t)> getPixel, PlayPal &playpal, uint8_t palleteIndex, ColorMap &colorMap, uint8_t MapIndex);

void SaveAllPictures(ConsecutiveBytearrayReader &fileByteReader, WADHeader &wadHeader, PlayPal &playpal, ColorMap &colorMap, std::shared_ptr<std::string[]> pnames, size_t pnameAmmount, std::vector<Texture> textures);

void SaveAllSounds(ConsecutiveBytearrayReader &fileByteReader, WADHeader &wadHeader);