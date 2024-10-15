#include "../headers/WADHeader.h"

WADHeader::WADHeader(std::string header, uint32_t numLumps, uint32_t infotableofs, std::shared_ptr<Lump[]> lumps) : header(header), numLumps(numLumps), infotableofs(infotableofs), lumps(lumps) {}

std::ostream &operator<<(std::ostream &os, const WADHeader &obj)
{
    os << "WADHeader{ ";
    os << "header: " << obj.header << " ";
    os << "numLumps: " << (int)obj.numLumps << " ";
    os << "infotableofs: " << (int)obj.infotableofs << " ";
    os << "}";
    return os;
}

std::shared_ptr<WADHeader> GenerateWADHeader(ConsecutiveBytearrayReader &fileByteReader)
{
    // File header found in the begginning of the file, should be IWAD or PWAD
    std::string header = fileByteReader.readBytesAsStr(4);
    std::cout << "Header is: " << header << std::endl;

    if (!(header == "IWAD" || header == "PWAD"))
    {
        std::cout << "Header must be IWAD or PWAD. header is: " << header << std::endl;
        return nullptr;
    }

    // Number of LUMP objects in the file
    uint32_t numLumps = fileByteReader.readBytesAsUint32();
    // Offset to the infotables, the place where the lumps descriptions are found
    uint32_t infotableofs = fileByteReader.readBytesAsUint32();
    
    fileByteReader.pointer = infotableofs;
    auto lumps = GenerateLumps(fileByteReader, numLumps);

#ifdef debugPrint
    std::cout << "numLumps is: " << numLumps << " and infotablesOffset is: " << infotableofs << std::endl;
    std::cin.get();
#endif

    return std::make_shared<WADHeader>(header, numLumps, infotableofs, lumps);
}

std::shared_ptr<Lump[]> GenerateLumps(ConsecutiveBytearrayReader &fileByteReader, size_t numLumps)
{
    // array of all Lump descriptions in the file
    std::shared_ptr<Lump[]> lumps = std::make_shared<Lump[]>(numLumps);
    for (int i = 0; i < numLumps; i++)
    {
        lumps[i] = fileByteReader.readLump();
#ifdef debugPrint
        std::cout << "Loaded Lump[" << (i + 1) << "] out of [" << (numLumps) << "] <" << lumps[i] << ">" << std::endl;
#endif
    }

#ifdef debugPrint
    std::cout << "Finished loading Lumps" << std::endl;
    std::cin.get();
#endif

    return lumps;
}