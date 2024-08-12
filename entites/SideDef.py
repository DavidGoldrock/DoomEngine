class SideDef:
    def __init__(self, x, y, upperTextureName, lowerTextureName, middleTextureName, sectorNumber):
        self.x = x
        self.y = y
        self.upperTextureName = upperTextureName
        self.lowerTextureName = lowerTextureName
        self.middleTextureName = middleTextureName
        self.sectorNumber = sectorNumber

    def __str__(self):
        return f"{self.x = }, {self.y = }, {self.upperTextureName = }, {self.lowerTextureName = }, {self.middleTextureName = }, {self.sectorNumber = }"

    __repr__ = __str__
