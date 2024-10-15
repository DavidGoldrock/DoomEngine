#ifndef WAD_HEADER_H
#define WAD_HEADER_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>

struct WADHeader
{
    std::string header;
    uint32_t numlumps;
    uint32_t infotableofs;

    WADHeader(std::string header, uint32_t numlumps, uint32_t infotableofs);

    friend std::ostream &operator<<(std::ostream &os, const WADHeader &obj);
};

std::shared_ptr<WADHeader> GenerateWADHeader(ConsecutiveBytearrayReader &fileByteReader);

std::shared_ptr<Lump[]> GenerateLumps(ConsecutiveBytearrayReader &fileByteReader, size_t numlumps);

#endif