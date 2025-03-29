#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/FileDescriptor.h"

int main()
{
    std::shared_ptr<FileDescriptor> fileDescriptor = nullptr;
    

    while (fileDescriptor == nullptr) {
        fileDescriptor = FileDescriptor::getFileDescriptorFromUser();
    }

    return 0;
}