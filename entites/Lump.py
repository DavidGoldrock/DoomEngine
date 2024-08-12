class Lump:
    def __init__(self, filepos: int, size: int, name: str):
        self.filepos = filepos
        self.size = size
        self.name = name

    def __str__(self):
        return f"{self.name=}, {self.filepos=}, {self.size=}"

    __repr__ = __str__
