#include "../headers/UtilFunctions.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <fstream>
#include "../headers/Lump.h"

bool bitAtLocation(size_t source, size_t n) { 
    return (source & (1 << n)) != 0;
}

bool isCollision(float x1, float y1, float width1, float height1, 
                 float x2, float y2, float width2, float height2) {
    // Check for overlap in the x direction
    bool x_overlap = x1 < x2 + width2 && x1 + width1 > x2;
    
    // Check for overlap in the y direction
    bool y_overlap = y1 < y2 + height2 && y1 + height1 > y2;

    // Boxes collide if they overlap in both x and y directions
    return x_overlap && y_overlap;
}

size_t findInLumpArray(std::shared_ptr<Lump[]> arr, size_t from , size_t to, std::string tagname){
    for(size_t i = from; i < to; i ++) {
        if (arr[i].name == tagname)
            return i;
    }
    return -1;
}

/**
 * @brief gets the contents of the file into a smart pointer of uint8
 * 
 * @param filename the name of the opened file, passed by reference because copying a string is expensive
 * @param size the size of the file, passed by reference, changed by the function to match the size
 * @return std::shared_ptr<uint8_t[]> representing the contents of the file in bytes
 */
std::shared_ptr<uint8_t[]> readFileToUint8Array(const std::string& filename, size_t& size) {
    // Open the file in binary mode at the end to get the file size
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }

    // Get the size of the file
    size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory for the data
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(size);

    // Read the file contents into the array
    if (!file.read(reinterpret_cast<char*>(data.get()), size)) {
        std::cerr << "Failed to read the file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }

    return data;
}