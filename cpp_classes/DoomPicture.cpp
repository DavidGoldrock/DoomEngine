#include "../headers/DoomPicture.h"

DoomSprite::DoomSprite(uint16_t width, uint16_t height, int16_t leftOffset, int16_t topOffset, std::shared_ptr<uint8_t[]> pixels): width(width), height(height), leftOffset(leftOffset), topOffset(topOffset), pixels(pixels) {}

std::ostream &operator<<(std::ostream &os, const DoomSprite &obj) { 
    os << "DoomPicture {" << std::endl;
    os << "Width " << obj.width << std::endl; 
    os << "Height " << obj.height << std::endl; 
    os << "Left offset " << obj.leftOffset << std::endl;
    os << "Top offset " << obj.topOffset << std::endl;
    os << "Columns {" << std::endl;
    for (size_t i = 0; i < obj.width; i++) {
        for (size_t j = 0; j < obj.height; j++)
        {
            os << " " << (int) obj.pixels[i + j * obj.width];
        }
        os  << std::endl;
    }
    os << "    }" << std::endl << "}" << std::endl;
    return os;
}