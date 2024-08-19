#include <iostream>
#include "./headers/Lump.h"
#include <fstream>
#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include "./headers/Vec2.h"
#include "./headers/ProcessLevelData.h"

bool readFileToUint8Array(const std::string& filename, uint8_t*& data, size_t& size) {
    // Open the file in binary mode at the end to get the file size
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        return false;
    }

    // Get the size of the file
    size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory for the data
    data = new uint8_t[size];

    // Read the file contents into the array
    if (!file.read(reinterpret_cast<char*>(data), size)) {
        std::cerr << "Failed to read the file: " << filename << std::endl;
        delete[] data;
        data = nullptr;
        file.close();
        return false;
    }
    file.close();
    return true;
}

int main() {
    const std::string filename = "./resources/DOOM.wad";
    uint8_t* data = nullptr;
    size_t size = 0;
    if (!readFileToUint8Array(filename, data, size)) {
        return -1;
    }

    std::cout << "File read successfully. Size: " << size << " bytes." << std::endl;

     
    ConsecutiveBytearrayReader* br = new ConsecutiveBytearrayReader(data, size);
    char* header = new char[5];

    br->readBytesAsChar(header,4);
    std::cout << "Header is: " << header << std::endl;

    if(!(strcmp(header, "IWAD") == 0 || strcmp(header, "PWAD") == 0)) {
        std::cout << "Header must be IWAD or PWAD. header is: " << header << std::endl;

        delete[] header;
        delete[] data;
        header = nullptr;
        data = nullptr;
        return -1;
    }

    uint32_t numlumps = br->readBytesAsUint32();
    uint32_t infotableofs = br->readBytesAsUint32();   

    std::cout << "Numlumps is: " << numlumps << " and infotablesOffset is: " << infotableofs << std::endl; 

    br->pointer = infotableofs;
    Lump* lumps = new Lump[numlumps];
    for(int i = 0; i < numlumps; i++) {
        lumps[i] = br->readLump();
        std::cout << "Loaded Lump[" << (i+1) << "] out of ["<< (numlumps) << "] <" << lumps[i] << ">" << std::endl;
    }
    std::cout << "Finished loading Lumps" << std::endl;

    ENDOOM(*br, lumps, numlumps);
    Thing* things = THINGS(*br, lumps, numlumps);
    LineDef* lineDefs = LINEDEFS(*br, lumps, numlumps);
    SideDef* sideDefs = SIDEDEFS(*br, lumps, numlumps);
    Seg* segs = SEGS(*br, lumps, numlumps);
    SubSector* subSectors = SSECTORS(*br, lumps, numlumps);
    Node* nodes = NODES(*br, lumps, numlumps);
    Sector* sectors = SECTORS(*br, lumps, numlumps);
    Vec2* vertexes = VERTEXES(*br, lumps, numlumps);
    delete[] vertexes;
    delete[] sectors;
    delete[] nodes;
    delete[] subSectors;
    delete[] segs;
    delete[] sideDefs;
    delete[] lineDefs;
    delete[] things;
    delete[] lumps;
    delete[] header;
    delete[] data;
    return 0;
}