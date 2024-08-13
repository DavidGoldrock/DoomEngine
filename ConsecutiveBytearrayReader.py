from entites.Lump import Lump


class ConsecutiveBytearrayReader:
    def __init__(self, arr):
        self.pointer = 0
        self.arr = arr

    def readBytes(self, num: int = 0, t=None):
        if num == -1:
            ret = self.arr[self.pointer:]
            self.pointer = len(self.arr) - 1
            return ret
        ret = self.arr[self.pointer:self.pointer + num]
        self.pointer += num

        if t is None:
            return ret
        if t is int:
            return int.from_bytes(ret, 'little')
        if t is str:
            return ret.decode()

    def readLump(self):
        filepos = self.readBytes(4, int)
        size = self.readBytes(4, int)
        name = self.readBytes(8, str).strip(b"\x00".decode())
        return Lump(filepos, size, name)

    def readLumpData(self, l: Lump):
        pb = self.pointer
        self.pointer = l.filepos
        ret = self.readBytes(l.size)
        self.pointer = pb
        return ret

