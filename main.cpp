#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include "./headers/Vec2.h"
#include "./headers/SpecialClassFunctions.h"
#include "./headers/UtilFunctions.h"
#include "./headers/LevelData.h"
#include "./headers/WADHeader.h"
#include "./headers/FileDescriptor.h"

int main()
{
    // The name of the wad. might be picked from directory or something in the future
    const std::string filename = "./resources/DOOM.wad";
    std::shared_ptr<FileDescriptor> fileDescriptor = FileDescriptor::fromFile(filename);
    return 0;
}