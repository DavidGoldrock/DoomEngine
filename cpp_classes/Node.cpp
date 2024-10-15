#include "../headers/Node.h"

Node::Node(uint16_t x, uint16_t y, uint16_t deltaX, uint16_t deltaY, uint16_t rightBoundingBoxTop, uint16_t rightBoundingBoxBottom, uint16_t rightBoundingBoxLeft, uint16_t rightBoundingBoxRight, uint16_t leftBoundingBoxTop, uint16_t leftBoundingBoxBottom, uint16_t leftBoundingBoxLeft, uint16_t leftBoundingBoxRight, uint16_t rightChildIndex, uint16_t leftChildIndex)
    : x(x), y(y), deltaX(deltaX), deltaY(deltaY), rightBoundingBoxTop(rightBoundingBoxTop), rightBoundingBoxBottom(rightBoundingBoxBottom), rightBoundingBoxLeft(rightBoundingBoxLeft), rightBoundingBoxRight(rightBoundingBoxRight), leftBoundingBoxTop(leftBoundingBoxTop), leftBoundingBoxBottom(leftBoundingBoxBottom), leftBoundingBoxLeft(leftBoundingBoxLeft), leftBoundingBoxRight(leftBoundingBoxRight), rightChildIndex(rightChildIndex), leftChildIndex(leftChildIndex)
{
}

Node::Node()
    : x(0), y(0), deltaX(0), deltaY(0), rightBoundingBoxTop(0), rightBoundingBoxBottom(0), rightBoundingBoxLeft(0), rightBoundingBoxRight(0), leftBoundingBoxTop(0), leftBoundingBoxBottom(0), leftBoundingBoxLeft(0), leftBoundingBoxRight(0), rightChildIndex(0), leftChildIndex(0)
{
}

std::ostream &operator<<(std::ostream &os, const Node &obj)
{
    os << "Node{ ";
    os << "x: " << (int)obj.x << " ";
    os << "y: " << (int)obj.y << " ";
    os << "deltaX: " << (int)obj.deltaX << " ";
    os << "deltaY: " << (int)obj.deltaY << " ";
    os << "rightBoundingBoxTop: " << (int)obj.rightBoundingBoxTop << " ";
    os << "rightBoundingBoxBottom: " << (int)obj.rightBoundingBoxBottom << " ";
    os << "rightBoundingBoxLeft: " << (int)obj.rightBoundingBoxLeft << " ";
    os << "rightBoundingBoxRight: " << (int)obj.rightBoundingBoxRight << " ";
    os << "leftBoundingBoxTop: " << (int)obj.leftBoundingBoxTop << " ";
    os << "leftBoundingBoxBottom: " << (int)obj.leftBoundingBoxBottom << " ";
    os << "leftBoundingBoxLeft: " << (int)obj.leftBoundingBoxLeft << " ";
    os << "leftBoundingBoxRight: " << (int)obj.leftBoundingBoxRight << " ";
    os << "rightChildIndex: " << (int)obj.rightChildIndex << " ";
    os << "leftChildindex: " << (int)obj.leftChildIndex << " ";
    os << "}";
    return os;
}

std::shared_ptr<Node[]> NODES(ConsecutiveBytearrayReader &fileByteReader, Lump &lump, size_t from, size_t to)
{
    // Read data to byteReader
    std::shared_ptr<uint8_t[]> data = std::make_shared<uint8_t[]>(lump.size);
    fileByteReader.readLumpData(data.get(), lump);
    std::unique_ptr<ConsecutiveBytearrayReader> lumpDataByteReader = std::make_unique<ConsecutiveBytearrayReader>(data, lump.size);
    // Create array
    std::shared_ptr<Node[]> levelNode = std::make_shared<Node[]>(lump.size / 28);
    // Read using format
    for (size_t i = 0; i < lump.size / 28; i++)
    {
        levelNode[i].x = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].y = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].deltaX = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].deltaY = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxTop = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxBottom = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxLeft = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightBoundingBoxRight = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxTop = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxBottom = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxLeft = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftBoundingBoxRight = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].rightChildIndex = lumpDataByteReader->readBytesAsUint16();
        levelNode[i].leftChildIndex = lumpDataByteReader->readBytesAsUint16();

// Print if debugPrint is on
#ifdef debugPrint
        std::cout << "Loaded Node [" << (i + 1) << "]" << " Out of [" << lump.size / 28 << "]" << levelNode[i] << std::endl;
#endif
    }

    return levelNode;
}