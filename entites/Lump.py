class Lump:
    def __init__(self, filepos: int, size: int, name: str):
        self.filepos = filepos
        self.size = size
        self.name = name

    def __str__(self):
        return f"{self.filepos=}, {self.size=}, {self.name=}"

    __repr__ = __str__
