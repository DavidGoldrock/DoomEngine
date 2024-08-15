class Thing:
    def __init__(self, x, y, angle, doomType, flags, skillLevel12, skillLevel3, skillLevel45, deaf, notSinglePlayer):
        self.x = x
        self.y = y
        self.angle = angle
        self.doomType = doomType
        self.flags = flags
        self.skillLevel12 = skillLevel12
        self.skillLevel3 = skillLevel3
        self.skillLevel45 = skillLevel45
        self.deaf = deaf
        self.notSinglePlayer = notSinglePlayer

    def __str__(self):
        return f"{self.x=}, {self.y=}, {self.angle=}, {self.doomType=}, {self.flags=}, {self.skillLevel12=}, {self.skillLevel3=}, {self.skillLevel45=}, {self.deaf=}, {self.notSinglePlayer=}"

    __repr__ = __str__
