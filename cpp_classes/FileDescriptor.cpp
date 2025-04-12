#include "../headers/FileDescriptor.h"
#include <UtilFunctions.h>
#include "FileDescriptor.h"
#include <windows.h>


FileDescriptor::FileDescriptor(std::shared_ptr<WADHeader> wadHeader, std::string endoom, std::shared_ptr<PlayPal> playpal, std::shared_ptr<ColorMap> colorMap, std::shared_ptr<std::string[]> pnames, size_t pnameAmmount, std::vector<Texture> textures, std::vector<Sound> sounds, std::vector<LevelData> levels):wadHeader(wadHeader), endoom(endoom), playpal(playpal), colorMap(colorMap), pnames(pnames), pnameAmmount(pnameAmmount), textures(textures), sounds(sounds), levels(levels) {

}


std::ostream &operator<<(std::ostream &os, const FileDescriptor &obj) {
    os << "wadHeader: " << obj.wadHeader << std::endl;
    os << "endoom: " << obj.endoom << std::endl;
    os << "playpal: " << obj.playpal << std::endl;
    os << "colorMap: " << obj.colorMap << std::endl;
    os << "pnames {" << std::endl;
    os << "    pnameAmmount: " << (int) obj.pnameAmmount << std::endl << "    names:{";
    for (size_t i = 0; i < obj.pnameAmmount; i++)
    {
        os << "        " << obj.pnames[i] << std::endl;
    }

    os << "    }" << std::endl << "}" << std::endl;
    
    os << "textures {" << std::endl;
    for (Texture texture : obj.textures)
    {
        os << "    " << texture << std::endl;
    }

    os << "}" << std::endl;

    os << "textures {" << std::endl;
    for (Sound sound : obj.sounds)
    {
        os << "    " << sound << std::endl;
    }

    os << "}" << std::endl;

    os << "levels {" << std::endl;
    for (LevelData level : obj.levels)
    {
        os << "    " << level << std::endl;
    }

    os << "}" << std::endl;
    return os;
}


std::shared_ptr<FileDescriptor> FileDescriptor::fromFile(const std::string filename) {
    
    // the size of the file data. set by readFileToUint8Array
    size_t fileSize = 0;
    std::shared_ptr<uint8_t[]> fileData = readFileToUint8Array(filename, fileSize);

    // If the file couldn't be read for some reason, quit.
    if (fileSize == 0 or fileData == nullptr)
    {
        return nullptr;
    }

    std::cout << "File read successfully. Size: " << fileSize << " bytes." << std::endl;

    // a consecutive byte reader for the file, used by various functions
    std::unique_ptr<ConsecutiveBytearrayReader> fileByteReader = std::make_unique<ConsecutiveBytearrayReader>(fileData, fileSize);

    // Go to the infotables

    auto wadHeader = GenerateWADHeader(*fileByteReader);

    if (wadHeader == nullptr) {
        return nullptr;
    }

    // The end message of the file. written in ANSI compatible syntax

    std::string tagname = "ENDOOM";
    size_t endoomLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
if(endoomLumpIndex == -1) {
    std::cout << "Error: endoomLumpIndex is not found" << std::endl;
    return nullptr;
}

    std::string endoom = ENDOOM(*fileByteReader, wadHeader->lumps[endoomLumpIndex], 0, wadHeader->numLumps);

    tagname = "PLAYPAL";
    size_t palleteLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    if(palleteLumpIndex == -1) {
        std::cout << "Error: palleteLumpIndex is not found" << std::endl;
        return nullptr;
    }
    std::shared_ptr<PlayPal> playpal = PLAYPAL(*fileByteReader, wadHeader->lumps[palleteLumpIndex], 0, wadHeader->numLumps);

    tagname = "COLORMAP";
    size_t colorMapLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    if(colorMapLumpIndex == -1) {
        std::cout << "Error: colorMapLumpIndex is not found" << std::endl;
        return nullptr;
    }
    std::shared_ptr<ColorMap> colorMap = COLORMAP_FROM_READER(*fileByteReader, wadHeader->lumps[colorMapLumpIndex], 0, wadHeader->numLumps);

    tagname = "PNAMES";
    size_t pnamesLumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    if(pnamesLumpIndex == -1) {
        std::cout << "Error: pnamesLumpIndex is not found" << std::endl;
        return nullptr;
    }
    std::shared_ptr<std::string[]> pnames = PNAMES(*fileByteReader, wadHeader->lumps[pnamesLumpIndex], 0, wadHeader->numLumps);
    size_t pnameAmmount = (wadHeader->lumps[pnamesLumpIndex].size - 4) / 8;

    auto textures = std::vector<Texture>();

    tagname = "TEXTURE1";
    size_t texture1LumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    if(texture1LumpIndex == -1) {
        std::cout << "Error: texture1LumpIndex is not found" << std::endl;
        return nullptr;
    }
    TEXTURE(*fileByteReader, wadHeader->lumps[texture1LumpIndex], 0, wadHeader->numLumps, textures);

    tagname = "TEXTURE2";
    size_t texture2LumpIndex = findInLumpArray(wadHeader->lumps, 0, wadHeader->numLumps, tagname);
    if(texture2LumpIndex == -1) {
        std::cout << "Error: texture2LumpIndex is not found" << std::endl;
        return nullptr;
    }
    TEXTURE(*fileByteReader, wadHeader->lumps[texture2LumpIndex], 0, wadHeader->numLumps, textures);
    // std::cout << endoom << std::endl;
#ifdef debugPrint
    std::cin.get();
#endif

    std::vector<Sound> sounds = std::vector<Sound>();
    SOUNDS(*fileByteReader, *wadHeader, sounds);
    // SaveAllPictures(*fileByteReader, *wadHeader, *playpal, *colorMap, pnames, pnameAmmount, textures);
    SaveAllSounds("./results/Sound Effects/", sounds);
    auto levels = GenerateLevels(*fileByteReader, *wadHeader);

    for (auto level : levels)
    {
        // TODO: Code lol
    }

    std::shared_ptr<FileDescriptor> fileDescriptor = std::make_shared<FileDescriptor>(wadHeader, endoom, playpal, colorMap, pnames, pnameAmmount, textures, sounds, levels);
    return fileDescriptor;
}

std::shared_ptr<FileDescriptor> FileDescriptor::getFileDescriptorFromUser() {

    std::shared_ptr<FileDescriptor> fileDescriptor = nullptr;

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

    std::cout << "Enter your filename" << std::endl;
    if(!GetOpenFileNameA(&windowsFileSelectionIOObject)) {
        std::cout << "Must choose a file" << std::endl << std::endl;
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
    }
    return fileDescriptor;
}