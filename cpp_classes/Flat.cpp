#include "../headers/Flat.h"
#include "../headers/CustomException.h"

Flat::Flat(std::shared_ptr<uint8_t[]> rawPixels): rawPixels(rawPixels) {}

uint8_t Flat::getPixel(uint8_t i, uint8_t j) {
    if (i > 64 || j > 64) {
        std::string msg = "Out of bounds. i = " + std::to_string((int)i) +", j = " + std::to_string((int)j);
        throw CustomException(msg);
    }
    return rawPixels.get()[i * size + j];
}

std::ostream &operator<<(std::ostream &os, const Flat &obj) { 
    os << "Flat {" << std::endl;
    for (uint8_t i = 0; i < 14; i ++) {
        os << "{" << std::endl;
        for (int j = 0; j < Flat::size; ++j) {
        os << "    ";
            os << obj.rawPixels[i * Flat::size + j] << std::endl;
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}