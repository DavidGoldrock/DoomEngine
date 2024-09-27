#include "../headers/ColorMap.h"

ColorMap::ColorMap(std::shared_ptr<uint8_t[]> rawRGBs) : rawIndexes(rawRGBs) {}

uint8_t *ColorMap::getMap(uint8_t index)
{
    return rawIndexes.get() + (ColorMap::MAP_DEPTH * index);
}

std::ostream &operator<<(std::ostream &os, const ColorMap &obj)
{
    os << "ColorMap {" << std::endl;
    for (uint8_t i = 0; i < ColorMap::COLORMAP_AMMOUNT; i++)
    {
        os << "{" << std::endl;
        for (int j = 0; j < ColorMap::MAP_DEPTH; ++j)
        {
            os << (int) obj.rawIndexes[i * ColorMap::MAP_DEPTH + j] << ", ";
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}