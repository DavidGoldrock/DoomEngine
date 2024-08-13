class BlockMap:
    def __init__(self, gridX, gridY, columnNumber, rowNumber, offsets, lineDefIndexByBlock):
        self.gridX = gridX
        self.gridY = gridY
        self.columnNumber = columnNumber
        self.rowNumber = rowNumber
        self.offsets = offsets
        self.lineDefIndexByBlock = lineDefIndexByBlock

    def __str__(self):
        return f"{self.gridX=}, {self.gridY=}, {self.columnNumber=}, {self.rowNumber=}, {self.offsets=}, {self.lineDefIndexByBlock=}"

    __repr__ = __str__
