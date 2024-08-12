class Node:
    def __init__(self, x, y, deltaX, deltaY, rightBoundingBoxTop, rightBoundingBoxBottom, rightBoundingBoxLeft, rightBoundingBoxRight, leftBoundingBoxTop, leftBoundingBoxBottom, leftBoundingBoxLeft, leftBoundingBoxRight, rightChild, leftChild):
        self.x = x
        self.y = y
        self.deltaX = deltaX
        self.deltaY = deltaY
        self.rightBoundingBoxTop = rightBoundingBoxTop
        self.rightBoundingBoxBottom = rightBoundingBoxBottom
        self.rightBoundingBoxLeft = rightBoundingBoxLeft
        self.rightBoundingBoxRight = rightBoundingBoxRight
        self.leftBoundingBoxTop = leftBoundingBoxTop
        self.leftBoundingBoxBottom = leftBoundingBoxBottom
        self.leftBoundingBoxLeft = leftBoundingBoxLeft
        self.leftBoundingBoxRight = leftBoundingBoxRight
        self.rightChild = rightChild
        self.leftChild = leftChild

    def __str__(self):
        return f"{self.x=}, {self.y=}, {self.deltaX=}, {self.deltaY=}, {self.rightBoundingBoxTop=}, {self.rightBoundingBoxBottom=}, {self.rightBoundingBoxLeft=}, {self.rightBoundingBoxRight=}, {self.leftBoundingBoxTop=}, {self.leftBoundingBoxBottom=}, {self.leftBoundingBoxLeft=}, {self.leftBoundingBoxRight=}, {self.rightChild=}, {self.leftChild=}"

    __repr__ = __str__