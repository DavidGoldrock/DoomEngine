class SubSector:
    def __init__(self, segCount, firstSegNumber):
        self.segCount = segCount
        self.firstSegNumber = firstSegNumber

    def __str__(self):
        return f"{self.segCount=}, {self.firstSegNumber=}"

    __repr__ = __str__
