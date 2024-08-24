#include "../headers/Reject.h"
#include "../headers/UtilFunctions.h"

Reject::Reject(std::shared_ptr<uint8_t[]> rejectDataSource, size_t sectorsNumber): sectorsNumber(sectorsNumber), rejectData(std::make_unique<bool[]>(sectorsNumber * sectorsNumber)) {
        size_t byteIndex;
        size_t bitIndex;
        for (size_t i = 0; i < sectorsNumber * sectorsNumber; ++i) {
            byteIndex = i / 8;
            bitIndex = i % 8;
            rejectData[i] = bitAtLocation(rejectDataSource[byteIndex], bitIndex);
        }
}

bool Reject::getRejectData(size_t row, size_t column) {
    return rejectData[row * sectorsNumber + column];
}

std::ostream& operator<<(std::ostream& os, const Reject& obj) {
    os << "Reject{ " << std::endl;
    for (size_t i = 0; i < obj.sectorsNumber; ++i) {
        for (size_t j = 0; j < obj.sectorsNumber; ++j) {
            os << obj.rejectData[i * obj.sectorsNumber + j];
        }
        os << std::endl;
    }
    os << "}";
    return os;
}