#ifndef SOUND_H
#define SOUND_H

#include <cstdint>
#include "ConsecutiveBytearrayReader.h"
#include "Lump.h"
#include <iostream>
#include <memory>

struct Sound
{
    std::string name;
    uint16_t formatNumber;
    uint16_t sampleRate;
    uint32_t sampleNumber;
    std::shared_ptr<uint8_t[]> samples;

    // Constructor
    Sound(std::string name, uint16_t formatNumber, uint16_t sampleRate, uint32_t adjustedSampleNumber, std::shared_ptr<uint8_t[]> samples);
    Sound();

    friend std::ostream &operator<<(std::ostream &os, const Sound &obj);
};

std::shared_ptr<Sound> SOUND(ConsecutiveBytearrayReader &fileByteReader, Lump &lump);

void writeToWav(std::string filename, Sound& sound);

#endif
