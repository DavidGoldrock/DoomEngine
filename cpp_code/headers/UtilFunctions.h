#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include "../headers/Lump.h"

/**
 * @fileByteReaderief returns as bool a flag in position (of any size source)
 * 
 * @param source 
 * @param n bit position
 */
bool bitAtLocation(size_t source, size_t n);

size_t findInLumpArray(std::shared_ptr<Lump[]> arr, size_t arrSize, std::string tagname);

#endif