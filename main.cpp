#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/FileDescriptor.h"

int main()
{
    // The name of the wad. might be picked from directory or something in the future
    std::string filename;
    std::shared_ptr<FileDescriptor> fileDescriptor;
    bool flag = true;
    while (flag) {
        std::cout << "Enter your filename" << std::endl;
        std::cin >> filename;
        std::cout << std::endl;
        try {
            fileDescriptor = FileDescriptor::fromFile(filename);
        }
        catch (const std::exception& e) {
            std::cout << "Exception " << e.what() << std::endl;
            std::cout << "Try again with another file " << std::endl << std::endl;
        }

        if (fileDescriptor == nullptr) {
            std::cout << "File wasn't read successfully, try again with another file" << std::endl << std::endl;
        }
        else {
            std::cout << "File read successfully" << std::endl;
            flag = false;
        }
    }
    

    return 0;
}