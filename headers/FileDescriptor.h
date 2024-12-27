#ifndef FILE_DESCRIPTOR_H
#define FILE_DESCRIPTOR_H

#include <memory>
#include "WADHeader.h"
#include "PlayPal.h"
#include "ColorMap.h"
#include "Texture.h"
#include "LevelData.h"


struct FileDescriptor
{

    std::shared_ptr<WADHeader> wadHeader;
    std::string endoom;
    std::shared_ptr<PlayPal> playpal;
    std::shared_ptr<ColorMap> colorMap;
    std::shared_ptr<std::string[]> pnames;
    size_t pnameAmmount;
    std::vector<Texture> textures;
    std::vector<Sound> sounds;
    std::vector<LevelData> levels;
    // Constructor
    FileDescriptor(std::shared_ptr<WADHeader> wadHeader, std::string endoom, std::shared_ptr<PlayPal> playpal, std::shared_ptr<ColorMap> colorMap, std::shared_ptr<std::string[]> pnames, size_t pnameAmmount, std::vector<Texture> textures, std::vector<Sound> sounds, std::vector<LevelData> levels);

    static std::shared_ptr<FileDescriptor> fromFile(const std::string filename);
    friend std::ostream &operator<<(std::ostream &os, const FileDescriptor &obj);
};


#endif
