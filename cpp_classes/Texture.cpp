#include "../headers/Texture.h"

Texture::Texture(std::string name, bool masked, int16_t width, int16_t height, int16_t patchCount) :  name (name), masked (masked), width (width), height (height), patchCount (patchCount) {}
Texture::Texture() :  name (""), masked (false), width (0), height (0), patchCount (0) {}

std::ostream& operator<<(std::ostream& os, const Texture& obj) {
    os << "Texture{ ";
    os << "name: " << obj.name << " ";
    os << "masked: " << (bool) obj.masked << " ";
    os << "width: " << (int) obj.width << " ";
    os << "height: " << (int) obj.height << " ";
    os << "patchCount: " << (int) obj.patchCount << " ";

    os << "Patches{" << std::endl;
        for (int i = 0; i < obj.patchCount; ++i) {
        os << "    ";
            os << obj.patches[i] << std::endl;
        }
        os << "}" << std::endl;

    os << "}";
    return os;
} 