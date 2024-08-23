#include <iostream>
#include "./headers/Lump.h"
#include <fstream>
#include <memory>
#include "./headers/ConsecutiveBytearrayReader.h"
#include "./headers/Lump.h"
#include "./headers/Vec2.h"
#include "./headers/ProcessLevelData.h"

std::shared_ptr<uint8_t[]> readFileToUint8Array(const std::string& filename, size_t& size) {
    // Open the file in binary mode at the end to get the file size
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }

    // Get the size of the file
    size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Allocate memory for the data
    std::shared_ptr<uint8_t[]> data(new uint8_t[size], std::default_delete<uint8_t[]>());

    // Read the file contents into the array
    if (!file.read(reinterpret_cast<char*>(data.get()), size)) {
        std::cerr << "Failed to read the file: " << filename << std::endl;
        size = 0;
        return nullptr;
    }

    return data;
}


int main() {
    const std::string filename = "./resources/DOOM.wad";
    size_t size = 0;
    std::shared_ptr<uint8_t[]> data = readFileToUint8Array(filename, size);
    if (size == 0 or data == nullptr) {
        return -1;
    }

    std::cout << "File read successfully. Size: " << size << " bytes." << std::endl;

     
    std::unique_ptr<ConsecutiveBytearrayReader> br = std::make_unique<ConsecutiveBytearrayReader>(data, size);
    char header[5];

    br->readBytesAsChar(header,4);
    std::cout << "Header is: " << header << std::endl;

    if(!(strcmp(header, "IWAD") == 0 || strcmp(header, "PWAD") == 0)) {
        std::cout << "Header must be IWAD or PWAD. header is: " << header << std::endl;
        return -1;
    }

    uint32_t numlumps = br->readBytesAsUint32();
    uint32_t infotableofs = br->readBytesAsUint32();   

    std::cout << "Numlumps is: " << numlumps << " and infotablesOffset is: " << infotableofs << std::endl; 

    br->pointer = infotableofs;
    std::shared_ptr<Lump[]> lumps = std::make_shared<Lump[]>(numlumps);
    for(int i = 0; i < numlumps; i++) {
        lumps[i] = br->readLump();
        std::cout << "Loaded Lump[" << (i+1) << "] out of ["<< (numlumps) << "] <" << lumps[i] << ">" << std::endl;
    }
    std::cout << "Finished loading Lumps" << std::endl;
    std::cout << ENDOOM(*br, lumps, numlumps) << std::endl;
    std::shared_ptr<Thing[]> things = THINGS(*br, lumps, numlumps);
    std::shared_ptr<LineDef[]> lineDefs = LINEDEFS(*br, lumps, numlumps);
    std::shared_ptr<SideDef[]> sideDefs = SIDEDEFS(*br, lumps, numlumps);
    std::shared_ptr<Seg[]> segs = SEGS(*br, lumps, numlumps);
    std::shared_ptr<SubSector[]> subSectors = SSECTORS(*br, lumps, numlumps);
    std::shared_ptr<Node[]> nodes = NODES(*br, lumps, numlumps);
    std::shared_ptr<Sector[]> sectors = SECTORS(*br, lumps, numlumps);
    std::shared_ptr<Vec2[]> vertexes = VERTEXES(*br, lumps, numlumps);
    return 0;
}