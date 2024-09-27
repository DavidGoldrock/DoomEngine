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