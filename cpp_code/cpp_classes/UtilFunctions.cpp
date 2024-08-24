#include "../headers/UtilFunctions.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include <fstream>
#include "../headers/Lump.h"

bool bitAtLocation(size_t source, size_t n) { 
    return (source & (1 << n)) != 0;
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