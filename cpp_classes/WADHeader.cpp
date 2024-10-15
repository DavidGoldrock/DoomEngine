#include "../headers/WADHeader.h"

WADHeader::WADHeader(std::string header, uint32_t numlumps, uint32_t infotableofs) : header(header), numlumps(numlumps), infotableofs(infotableofs) {}

std::ostream &operator<<(std::ostream &os, const WADHeader &obj)
{
    os << "WADHeader{ ";
    os << "header: " << obj.header << " ";
    os << "numlumps: " << (int)obj.numlumps << " ";
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
    uint32_t numlumps = fileByteReader.readBytesAsUint32();
    // Offset to the infotables, the place where the lumps descriptions are found
    uint32_t infotableofs = fileByteReader.readBytesAsUint32();

#ifdef debugPrint
    std::cout << "Numlumps is: " << numlumps << " and infotablesOffset is: " << infotableofs << std::endl;
    std::cin.get();
#endif

    return std::make_shared<WADHeader>(header, numlumps, infotableofs);
}

std::shared_ptr<Lump[]> GenerateLumps(ConsecutiveBytearrayReader &fileByteReader, size_t numlumps)
{
    // array of all Lump descriptions in the file
    std::shared_ptr<Lump[]> lumps = std::make_shared<Lump[]>(numlumps);
    for (int i = 0; i < numlumps; i++)
    {
        lumps[i] = fileByteReader.readLump();
#ifdef debugPrint
        std::cout << "Loaded Lump[" << (i + 1) << "] out of [" << (numlumps) << "] <" << lumps[i] << ">" << std::endl;
#endif
    }

#ifdef debugPrint
    std::cout << "Finished loading Lumps" << std::endl;
    std::cin.get();
#endif

    return lumps;
}