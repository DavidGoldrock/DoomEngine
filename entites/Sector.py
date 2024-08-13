class Sector:
    def __init__(self, floorHeight, ceilingHeight, floorTextureName, ceilingTextureName, lightLevel, specialTag, tagNumber):
        self.floorHeight = floorHeight
        self.ceilingHeight = ceilingHeight
        self.floorTextureName = floorTextureName
        self.ceilingTextureName = ceilingTextureName
        self.lightLevel = lightLevel
        self.specialTag = specialTag
        self.tagNumber = tagNumber

    def __str__(self):
        return f"{self.floorHeight=} {self.ceilingHeight=} {self.floorTextureName=} {self.ceilingTextureName=} {self.lightLevel=} {self.specialTag=} {self.tagNumber=}"

    __repr__ = __str__
