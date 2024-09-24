#ifndef UTILS_H
#define UTILS_H

#include <cstdint>
#include <iostream>
#include <memory>
#include "../headers/Lump.h"

#ifndef debugPrint
    // #define debugPrint 
#endif

bool bitAtLocation(size_t source, size_t n);

bool isCollision(float x1, float y1, float width1, float height1, 
                 float x2, float y2, float width2, float height2);

size_t findInLumpArray(std::shared_ptr<Lump[]> arr, size_t from, size_t to, std::string tagname);

std::shared_ptr<uint8_t[]> readFileToUint8Array(const std::string& filename, size_t& size);
#endif