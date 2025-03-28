#include <iostream>
#include <fstream>
#include <memory>
#include "./headers/FileDescriptor.h"
#include <windows.h>
int main()
{
    // The name of the wad. might be picked from directory or something in the future
    std::string filename;
    // It's buffer (MAX_PATH is a windows constant for maximum fileSize)
    char filenameBuffer[MAX_PATH] = {0};
    
    OPENFILENAMEA windowsFileSelectionIOObject;
    ZeroMemory(&windowsFileSelectionIOObject, sizeof(windowsFileSelectionIOObject));  // Initialize structure with zeros
    windowsFileSelectionIOObject.lStructSize = sizeof(windowsFileSelectionIOObject);  // Set size of struct
    windowsFileSelectionIOObject.hwndOwner = NULL;  // No parent window
    windowsFileSelectionIOObject.lpstrFile = filenameBuffer;  // Buffer to store selected file
    windowsFileSelectionIOObject.nMaxFile = MAX_PATH;
    windowsFileSelectionIOObject.lpstrTitle = "Select a Doom Wad File";  // Dialog title
    windowsFileSelectionIOObject.lpstrFilter = "DoomFiles (.wad, .pwad, .iwad)\0*.wad;*.iwad;*.pwad\0";  // File filters
    windowsFileSelectionIOObject.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_NOCHANGEDIR; // file and path must exist, and forces the function not to change directory
    // Was file successfully read
    bool flag = true;
    // The file descriptor itself
    std::shared_ptr<FileDescriptor> fileDescriptor = nullptr;
    while (flag) {
        std::cout << "Enter your filename" << std::endl;
        if(!GetOpenFileNameA(&windowsFileSelectionIOObject)) {
            std::cout << "Must choose a file" << std::endl << std::endl;
            continue;
        }
        else {
            filename = std::string(filenameBuffer);
        }

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