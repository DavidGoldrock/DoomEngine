#include "../headers/UtilFunctions.h"
#include <cstdint>
#include <iostream>
#include <memory>
#include "../headers/Lump.h"

bool bitAtLocation(size_t source, size_t n) { 
    return (source & (1 << n)) != 0;
}

size_t findInLumpArray(std::shared_ptr<Lump[]> arr, size_t arrSize, std::string tagname){
    for(size_t i = 0; i < arrSize; i ++) {
        if (arr[i].name == tagname)
            return i;
    }
    return -1;
}