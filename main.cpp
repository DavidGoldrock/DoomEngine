#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/FileDescriptor.h"

int main()
{
    // The name of the wad. might be picked from directory or something in the future
    const std::string filename = "./resources/DOOM.wad";
    std::shared_ptr<FileDescriptor> fileDescriptor;
    try {
        fileDescriptor = FileDescriptor::fromFile(filename);
    }
    catch (const std::exception& e) {
        std::cout << "Exception " << e.what() << std::endl;
        return -1;
    }

    if (fileDescriptor == nullptr) {
        return -1;
    }

    return 0;
}