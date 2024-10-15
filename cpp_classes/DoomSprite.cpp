#include "../headers/DoomSprite.h"
#include "../headers/CustomException.h"
// #define PRINT_PICTURES
DoomSprite::DoomSprite(uint16_t width, uint16_t height, int16_t leftOffset, int16_t topOffset, std::shared_ptr<uint8_t[]> pixels) : width(width), height(height), leftOffset(leftOffset), topOffset(topOffset), pixels(pixels) {}

uint8_t DoomSprite::getPixel(uint8_t x, uint8_t y)
{
    if (y > height || x > width)
    {
        std::string msg = "Out of bounds. y = " + std::to_string((int)y) + ", x = " + std::to_string((int)x);
        throw CustomException(msg);
    }
    return pixels[y * width + x];
}

std::ostream &operator<<(std::ostream &os, const DoomSprite &obj)
{
    os << "DoomSprite {" << std::endl;
    os << "Width " << obj.width << std::endl;
    os << "Height " << obj.height << std::endl;
    os << "Left offset " << obj.leftOffset << std::endl;
    os << "Top offset " << obj.topOffset << std::endl;
#ifdef PRINT_PICTURES
    os << "Columns {" << std::endl;
    for (size_t i = 0; i < obj.width; i++)
    {
        for (size_t j = 0; j < obj.height; j++)
        {
            os << " " << (int)obj.pixels[i + j * obj.width];
        }
        os << std::endl;
    }
#endif
    os << "    }" << std::endl
       << "}" << std::endl;
    return os;
}

std::shared_ptr<DoomSprite> SPRITE(ConsecutiveBytearrayReader &fileByteReader, Lump &lump)
{
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    uint16_t width = lumpDataByteReader->readBytesAsUint16();
    uint16_t height = lumpDataByteReader->readBytesAsUint16();
    int16_t leftOffset = lumpDataByteReader->readBytesAsInt16();
    int16_t topOffset = lumpDataByteReader->readBytesAsInt16();

    size_t offsets[width];

    for (size_t i = 0; i < width; i++)
    {
        offsets[i] = lumpDataByteReader->readBytesAsUint32();
    }

    std::shared_ptr<uint8_t[]> pixels = std::make_shared<uint8_t[]>(width * height);

    for (size_t i = 0; i < width * height; i++)
    {
        pixels[i] = PlayPal::TRANSPARENT_COLOR;
    }

    std::shared_ptr<DoomSprite> pic = std::make_shared<DoomSprite>(width, height, leftOffset, topOffset, pixels);

    uint8_t rowstart;
    uint8_t pixel;
    uint8_t pixel_count;

    for (size_t i = 0; i < width; i++)
    {
        // Seek to the start of the column data
        lumpDataByteReader->pointer = offsets[i];
        rowstart = lumpDataByteReader->readBytesAsUint8();
        while (rowstart != 255)
        {
            if (rowstart == 255)
            {
                break;
            }

            pixel_count = lumpDataByteReader->readBytesAsUint8();
            lumpDataByteReader->pointer++; // Read and ignore the dummy value

            for (size_t j = 0; j < pixel_count; j++)
            {
                pixel = lumpDataByteReader->readBytesAsUint8();
                // Write Pixel to the image (column i, row rowstart + j)
                pic->pixels[i + (rowstart + j) * width] = pixel;
            }

            // Read and ignore the dummy value
            lumpDataByteReader->pointer++;
            rowstart = lumpDataByteReader->readBytesAsUint8();
        }
    }

#ifdef debugPrint
    std::cout << "Loaded Picture " << *pic << std::endl;
#endif

    return pic;
}