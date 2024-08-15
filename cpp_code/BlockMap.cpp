#include <cstdint>
#include <iostream>
#include "./headers/BlockMap.h"

std::ostream& operator<<(std::ostream& os, const BlockMap& obj) {
      os << "BlockMap{ ";
      os << "gridX: " << obj.gridX << " ";
      os << "gridY: " << obj.gridY << " ";
      os << "columnNumber: " << obj.columnNumber << " ";
      os << "rowNumber: " << obj.rowNumber << " ";
      os << "offsets: " << obj.offsets << " ";
      os << "lineDefIndexByBlock: " << obj.lineDefIndexByBlock << " ";
      os << "}";
      return os;
}