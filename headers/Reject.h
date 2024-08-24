#ifndef REJECT_H
#define REJECT_H

#include <cstdint>
#include <iostream>
#include <memory>

class Reject {
private:
    std::unique_ptr<bool[]> rejectData;
    size_t sectorsNumber;

public:
    // Constructor
    Reject(std::shared_ptr<uint8_t[]> rejectData, size_t sectorsNumber);

    friend std::ostream& operator<<(std::ostream& os, const Reject& obj);
    bool getRejectData(size_t row, size_t column);
};

#endif
