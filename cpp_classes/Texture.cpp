#include "../headers/Texture.h"

Texture::Texture(std::string name, int16_t width, int16_t height, int16_t patchCount) : name(name), width(width), height(height), patchCount(patchCount) {}
Texture::Texture() : name(""), width(0), height(0), patchCount(0) {}

std::ostream &operator<<(std::ostream &os, const Texture &obj)
{
    os << "Texture{ ";
    os << "name: " << obj.name << " ";
    os << "width: " << (int)obj.width << " ";
    os << "height: " << (int)obj.height << " ";
    os << "patchCount: " << (int)obj.patchCount << " ";

    os << "Patches{" << std::endl;
    for (int i = 0; i < obj.patchCount; ++i)
    {
        os << "    ";
        os << obj.patches[i] << std::endl;
    }
    os << "}" << std::endl;

    os << "}";
    return os;
}