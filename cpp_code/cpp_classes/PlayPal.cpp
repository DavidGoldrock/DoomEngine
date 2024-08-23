#include "../headers/PlayPal.h"

static uint16_t palleteDepth = 256;

PlayPal::PlayPal(std::shared_ptr<RGB[]> rawRGBs): rawRGBs(rawRGBs) {}

RGB* PlayPal::getPallette(uint8_t index) {
    return rawRGBs.get() + (palleteDepth * index);
}

std::ostream &operator<<(std::ostream &os, const PlayPal &obj) { 
    os << "PlayPal {" << std::endl;
    for (uint8_t i = 0; i < 14; i ++) {
        os << "{" << std::endl;
        for (int j = 0; j < palleteDepth; ++j) {
        os << "    ";
            os << obj.rawRGBs[i * palleteDepth + j] << std::endl;
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}