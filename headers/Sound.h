#ifndef SOUND_H
#define SOUND_H

#include <cstdint>
#include <iostream>
#include <memory>

struct Sound
{
    uint16_t formatNumber;
    uint16_t sampleRate;
    uint32_t sampleNumber;
    std::shared_ptr<uint8_t[]> samples;

    // Constructor
    Sound(uint16_t formatNumber, uint16_t sampleRate, uint32_t adjustedSampleNumber, std::shared_ptr<uint8_t[]> samples);
    Sound();

    friend std::ostream &operator<<(std::ostream &os, const Sound &obj);
};

#endif
