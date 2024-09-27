#include "../headers/BlockMap.h"
BlockMap::BlockMap(uint16_t gridX, uint16_t gridY, uint16_t columnNumber, uint16_t rowNumber, std::shared_ptr<std::vector<uint16_t>[]> blocklists)
    : gridX(gridX), gridY(gridY), columnNumber(columnNumber), rowNumber(rowNumber), blocklists(blocklists)
{
}

std::ostream &operator<<(std::ostream &os, const BlockMap &obj)
{
    os << "BlockMap{ " << std::endl;
    os << "gridX: " << obj.gridX << " " << std::endl;
    os << "gridY: " << obj.gridY << " " << std::endl;
    os << "columnNumber: " << obj.columnNumber << " " << std::endl;
    os << "rowNumber: " << obj.rowNumber << " " << std::endl;

    os << "blocklists: [" << std::endl;
    for (int i = 0; i < obj.columnNumber * obj.rowNumber; ++i)
    {
        os << "    [ ";
        for (const auto &val : obj.blocklists[i])
        {
            os << val << " ";
        }
        os << "]" << std::endl;
    }
    os << "] " << std::endl;

    os << "}";
    return os;
}
