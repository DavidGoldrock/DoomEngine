#include "../headers/Sound.h"

Sound::Sound(uint16_t formatNumber, uint16_t sampleRate, uint32_t adjustedSampleNumber, std::shared_ptr<uint8_t[]> samples)
    : formatNumber(formatNumber), sampleRate(sampleRate), sampleNumber(adjustedSampleNumber), samples(samples)
{
}

Sound::Sound()
{
    this->formatNumber = 0;
    this->sampleRate = 0;
    this->sampleNumber = 0;
    this->samples = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Sound &obj)
{
    os << "Sound{ ";
    os << "formatNumber: " << (int)obj.formatNumber << " ";
    os << "sampleRate: " << (int)obj.sampleRate << " ";
    os << "adjustedSampleNumber: " << (int)obj.sampleNumber << " ";
    os << "samples: {" << std::endl;
    for (size_t i = 0; i < obj.sampleNumber; i++)
    {
        os << "    " << (int) obj.samples[i] << ",";
    }
    os << "}";
    return os;
}