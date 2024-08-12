class Thing:
    def __init__(self, x, y, angle, doomType, flags, sl12, sl3, sl45, deaf, nsp):
        self.x = x
        self.y = y
        self.angle = angle
        self.doomType = doomType
        self.flags = flags
        self.sl12 = sl12
        self.sl3 = sl3
        self.sl45 = sl45
        self.deaf = deaf
        self.nsp = nsp

    def __str__(self):
        return f"{self.x=}, {self.y=}, {self.angle=}, {self.doomType=}, {self.flags=}, {self.sl12=}, {self.sl3=}, {self.sl45=}, {self.deaf=}, {self.nsp=}"

    __repr__ = __str__
