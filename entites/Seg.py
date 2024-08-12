class Seg:
    def __init__(self, startingVertexNumber, endingVertexNumber, angle, lineDefNumber, directionSameAsLineDef, offset):
        self.startingVertexNumber = startingVertexNumber
        self.endingVertexNumber = endingVertexNumber
        self.angle = angle
        self.lineDefNumber = lineDefNumber
        self.directionSameAsLineDef = directionSameAsLineDef
        self.offset = offset

    def __str__(self):
        return f"{self.startingVertexNumber=}, {self.endingVertexNumber=}, {self.angle=}, {self.lineDefNumber=}, {self.directionSameAsLineDef=}, {self.offset=}"

    __repr__ = __str__
