#ifndef WAD_HEADER_H
#define WAD_HEADER_H

#include <cstdint>
#include <iostream>

struct WADHeader
{
    std::string header;
    uint32_t numlumps;
    uint32_t infotableofs;

    WADHeader(std::string header, uint32_t numlumps, uint32_t infotableofs);

    friend std::ostream &operator<<(std::ostream &os, const WADHeader &obj);
};

#endif