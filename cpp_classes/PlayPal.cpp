#include "../headers/PlayPal.h"

PlayPal::PlayPal(std::shared_ptr<uint8_t[]> rawRGBs) : rawRGBs(rawRGBs) {}

uint8_t *PlayPal::getPallette(uint8_t index)
{
    return rawRGBs.get() + (PALLETE_DEPTH * index) * 3;
}

std::ostream &operator<<(std::ostream &os, const PlayPal &obj)
{
    os << "PlayPal {" << std::endl;
    for (uint8_t i = 0; i < PlayPal::PLAYPAL_AMMOUNT; i++)
    {
        os << "{" << std::endl;
        for (int j = 0; j < PlayPal::PALLETE_DEPTH; ++j)
        {
            os << (int) obj.rawRGBs[i * PlayPal::PALLETE_DEPTH + j] << ", ";
        }
        os << "}" << std::endl;
    }
    os << "}" << std::endl;
    return os;
}