#ifndef THING_H
#define STRUCT THING_H

#include <cstdint>
#include <iostream>

struct Thing {
    uint16_t x;
    uint16_t y;
    uint16_t angle;
    uint16_t doomType;
    uint16_t flags;
    bool skillLevel12;
    bool skillLevel3;
    bool skillLevel45;
    bool deaf;
    bool notSinglePlayer;

    // Constructor
    Thing(uint16_t x, uint16_t y, uint16_t angle, uint16_t doomType, uint16_t flags, bool skillLevel12, bool skillLevel3, bool skillLevel45, bool deaf, bool notSinglePlayer)
        : x(x), y(y), angle(angle), doomType(doomType), flags(flags), skillLevel12(skillLevel12), skillLevel3(skillLevel3), skillLevel45(skillLevel45), deaf(deaf), notSinglePlayer(notSinglePlayer)
    {}

    Thing();

    friend std::ostream& operator<<(std::ostream& os, const Thing& obj);
};

#endif
