#ifndef WAD_HEADER_H
#define WAD_HEADER_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>

struct WADHeader
{
    std::string header;
    uint32_t numLumps;
    uint32_t infotableofs;
    std::shared_ptr<Lump[]> lumps;

    WADHeader(std::string header, uint32_t numLumps, uint32_t infotableofs, std::shared_ptr<Lump[]> lumps);

    friend std::ostream &operator<<(std::ostream &os, const WADHeader &obj);
};

std::shared_ptr<WADHeader> GenerateWADHeader(ConsecutiveBytearrayReader &fileByteReader);

std::shared_ptr<Lump[]> GenerateLumps(ConsecutiveBytearrayReader &fileByteReader, size_t numLumps);

#endif