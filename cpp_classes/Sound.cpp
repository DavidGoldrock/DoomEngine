#include "../headers/Sound.h"
#include "fstream"
Sound::Sound(std::string name, uint16_t formatNumber, uint16_t sampleRate, uint32_t adjustedSampleNumber, std::shared_ptr<uint8_t[]> samples)
    : name(name), formatNumber(formatNumber), sampleRate(sampleRate), sampleNumber(adjustedSampleNumber), samples(samples)
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

std::shared_ptr<Sound> SOUND(ConsecutiveBytearrayReader &fileByteReader, Lump &lump) {
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);

    std::shared_ptr<Sound> sound = std::make_shared<Sound>();
    sound->name = lump.name;
    sound->formatNumber = lumpDataByteReader->readBytesAsUint16();

    if (sound->formatNumber == 0) {
        sound->sampleRate = 140;
        sound->sampleNumber = lumpDataByteReader->readBytesAsUint16();
        sound->samples = std::make_shared<uint8_t[]>(sound->sampleNumber);

        for (size_t i = 0; i < sound->sampleNumber; i++)
        {
            sound->samples[i] = lumpDataByteReader->readBytesAsUint8();
        }
    }

    else if (sound->formatNumber == 3) {
        sound->sampleRate = lumpDataByteReader->readBytesAsUint16();
        sound->sampleNumber = lumpDataByteReader->readBytesAsUint16() - 32;
        
        lumpDataByteReader->pointer += 16;
        
        sound->samples = std::make_shared<uint8_t[]>(sound->sampleNumber);

        for (size_t i = 0; i < sound->sampleNumber; i++)
        {
            sound->samples[i] = lumpDataByteReader->readBytesAsUint8();
        }
    }

    else {
        std::cerr << "Lump " << lump << "Has corrupted format number" << sound->formatNumber << std::endl;
    }

    #ifdef debugPrint
        std::cout << "Loaded Sound " << *sound << std::endl;
    #endif

    return sound;
}

constexpr char RIFF_HEADER[4] = {'R', 'I', 'F', 'F'};
constexpr char WAVE_HEADER[4] = {'W', 'A', 'V', 'E'};
constexpr char FMT_HEADER[4] = {'f', 'm', 't', ' '};
constexpr uint32_t FMT_CHUNK_SIZE = 16;  // Size of the fmt chunk (16 for PCM)
constexpr uint16_t AUDIO_FORMAT = 1;     // PCM format
constexpr uint16_t NUM_CHANNELS = 1;     // Mono
constexpr uint16_t BITS_PER_SAMPLE = 8;  // 8 bits per sample
constexpr char DATA_HEADER[4] = {'d', 'a', 't', 'a'};


std::shared_ptr<uint8_t[]> soundToWav(Sound& sound) {
    // Calculate required sizes
    uint32_t byte_rate = sound.sampleRate * NUM_CHANNELS * BITS_PER_SAMPLE / 8;
    uint16_t block_align = NUM_CHANNELS * BITS_PER_SAMPLE / 8;
    uint32_t data_bytes = sound.sampleNumber * NUM_CHANNELS * BITS_PER_SAMPLE / 8;
    uint32_t wav_size = 36 + data_bytes;  // 36 bytes for header + data section size

    // Create a buffer for the header
    uint8_t header[44]; // Total header size for WAV is 44 bytes

    // Write RIFF header
    std::memcpy(header, RIFF_HEADER, 4); // "RIFF"
    std::memcpy(header + 4, &wav_size, 4); // File size minus 8 bytes
    std::memcpy(header + 8, WAVE_HEADER, 4); // "WAVE"

    // Write fmt chunk
    std::memcpy(header + 12, FMT_HEADER, 4); // "fmt "
    std::memcpy(header + 16, &FMT_CHUNK_SIZE, 4); // Size of fmt chunk (16)
    std::memcpy(header + 20, &AUDIO_FORMAT, 2); // PCM format
    std::memcpy(header + 22, &NUM_CHANNELS, 2); // Number of channels
    uint32_t copy = sound.sampleRate;
    std::memcpy(header + 24, &copy, 4); // Sample rate
    std::memcpy(header + 28, &byte_rate, 4); // Byte rate
    std::memcpy(header + 32, &block_align, 2); // Block align
    std::memcpy(header + 34, &BITS_PER_SAMPLE, 2); // Bits per sample

    // Write data chunk
    std::memcpy(header + 36, DATA_HEADER, 4); // "data"
    std::memcpy(header + 40, &data_bytes, 4); // Data size

    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(data_bytes + 44);
    std::memcpy(data.get(), header, 44);
    std::memcpy(data.get() + 44, sound.samples.get(), data_bytes);

    return data;
}

// Function to write WAV file
void writeToWav(std::string filename, std::shared_ptr<Sound> sound) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file\n";
        return;
    }

    std::shared_ptr<uint8_t[]> data = soundToWav(*sound);
    size_t length = (sound->sampleNumber * NUM_CHANNELS * BITS_PER_SAMPLE / 8) + 44;

    // Write the sample data
    file.write(reinterpret_cast<const char*>(data.get()), length);

    file.close();
    std::cout << "FILE CLOSED" << std::endl;
}
