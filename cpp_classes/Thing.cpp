#include "../headers/Thing.h"

Thing::Thing(uint16_t x, uint16_t y, uint16_t angle, uint16_t doomType, uint16_t flags, bool skillLevel12, bool skillLevel3, bool skillLevel45, bool deaf, bool notSinglePlayer)
    : x(x), y(y), angle(angle), doomType(doomType), flags(flags), skillLevel12(skillLevel12), skillLevel3(skillLevel3), skillLevel45(skillLevel45), deaf(deaf), notSinglePlayer(notSinglePlayer)
{
}

Thing::Thing()
{
    this->x = 0;
    this->y = 0;
    this->angle = 0;
    this->doomType = 0;
    this->flags = 0;
    this->skillLevel12 = false;
    this->skillLevel3 = false;
    this->skillLevel45 = false;
    this->deaf = false;
    this->notSinglePlayer = false;
}

std::ostream &operator<<(std::ostream &os, const Thing &obj)
{
    os << "Thing{ ";
    os << "x: " << (int)obj.x << " ";
    os << "y: " << (int)obj.y << " ";
    os << "angle: " << (int)obj.angle << " ";
    os << "doomType: " << (int)obj.doomType << " ";
    os << "flags: " << (int)obj.flags << " ";
    os << "skillLevel12: " << obj.skillLevel12 << " ";
    os << "skillLevel3: " << obj.skillLevel3 << " ";
    os << "skillLevel45: " << obj.skillLevel45 << " ";
    os << "deaf: " << obj.deaf << " ";
    os << "notSinglePlayer: " << obj.notSinglePlayer << " ";
    os << "}";
    return os;
}