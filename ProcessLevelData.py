from ConsecutiveBytearrayReader import ConsecutiveBytearrayReader
from entites.LineDef import LineDef
from entites.Seg import Seg
from entites.SideDef import SideDef
from entites.Thing import Thing
from entites.Lump import Lump
import numpy as np


def findInLumpArray(arr, tagname):
    for index, element in enumerate(arr):
        if element.name == tagname:
            return index, element


"""
ENDDOOM
"""
CodeDict = {
    0: 30,
    1: 34,
    2: 32,
    3: 36,
    4: 31,
    5: 35,
    6: 33,
    7: 37,
    8: 90,
    9: 94,
    10: 92,
    11: 96,
    12: 91,
    13: 95,
    14: 93,
    15: 97
}


def VGA_16BIT_COLOR_MEMORY_TO_STRING(ansicode: bytes | bytearray) -> str:
    ret = ""
    lastForeground = -1
    lastBackground = -1
    for i in range(0, len(ansicode), 2):
        letter = (ansicode[i]).to_bytes(1, 'little').decode('cp437')
        code = ansicode[i + 1]
        foreground = code & 15
        background = (code & 112) >> 4
        isBlinking = ((code & 128) >> 7) == 1
        # print(f"letter: {letter} code : {code} foreground : {foreground} background : {background} isBlinking : {isBlinking}")
        if foreground != lastForeground:
            foregroundCode = CodeDict[foreground]
            foregroundColor = f"\033[{foregroundCode}m"
            ret += foregroundColor

        if background != lastBackground:
            backgroundCode = CodeDict[background] + 10
            backgroundColor = f"\033[{backgroundCode}m"
            ret += backgroundColor

        lastForeground = foreground
        lastBackground = background

        ret += letter
        if (i / 2 + 1) % 80 == 0:
            ret += f"\033[{0}m"
            ret += "\n"
            lastForeground = -1
            lastBackground = -1
    return ret


def ENDOOM(br, lumps):
    index, ENDOOM_lump = findInLumpArray(lumps, "ENDOOM")
    ENDOOM_text = br.readLumpData(ENDOOM_lump)
    ENDOOM_text_decoded = VGA_16BIT_COLOR_MEMORY_TO_STRING(ENDOOM_text)
    print(ENDOOM_text_decoded)


"""
THINGS
"""


def THINGS(br, levelLumps: list[Lump]):
    _, levelThingLump = findInLumpArray(levelLumps, "THINGS")
    data = br.readLumpData(levelThingLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelThings = []
    for i in range(levelThingLump.size // 10):
        x = br2.readBytes(2, int)
        y = br2.readBytes(2, int)
        angle = br2.readBytes(2, int)
        doomType = br2.readBytes(2, int)
        flags = br2.readBytes(2, int)
        sl12 = (flags & 1) == 1
        sl3 = ((flags & 2) >> 1) == 1
        sl45 = ((flags & 4) >> 2) == 1
        deaf = ((flags & 8) >> 3) == 1
        nsp = ((flags & 16) >> 4) == 1
        levelThings.append(Thing(x, y, angle, doomType, flags, sl12, sl3, sl45, deaf, nsp))
    return levelThings


"""
LINEDEFS
"""


def LINEDEFS(br, levelLumps: list[Lump]):
    _, levelLineDefLump = findInLumpArray(levelLumps, "LINEDEFS")
    data = br.readLumpData(levelLineDefLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelLineDefs = []
    for i in range(levelLineDefLump.size // 14):
        startVertex = br2.readBytes(2, int)
        endVertex = br2.readBytes(2, int)
        flags = br2.readBytes(2, int)
        sType = br2.readBytes(2, int)
        sTag = br2.readBytes(2, int)
        fSideDef = br2.readBytes(2, int)
        bSideDef = br2.readBytes(2, int)
        blocksPM = (flags & 1) == 1
        blocksM = ((flags & 2) >> 1) == 1
        ts = ((flags & 4) >> 2) == 1
        upperTextureUnpegged = ((flags & 8) >> 3) == 1
        lowerTextureUnpegged = ((flags & 16) >> 4) == 1
        secret = ((flags & 32) >> 5) == 1
        blocksSound = ((flags & 64) >> 6) == 1
        neverAutoMap = ((flags & 128) >> 7) == 1
        alwaysAutoMap = ((flags & 256) >> 8) == 1
        levelLineDefs.append(
            LineDef(startVertex, endVertex, flags, sType, sTag, fSideDef, bSideDef, blocksPM, blocksM, ts,
                    upperTextureUnpegged, lowerTextureUnpegged, secret, blocksSound, neverAutoMap, alwaysAutoMap))
        print(levelLineDefs[i])
        print()
    return levelLineDefs


"""
SIDEDEFS
"""


def SIDEDEFS(br, levelLumps: list[Lump]):
    _, levelSideDefLump = findInLumpArray(levelLumps, "SIDEDEFS")
    data = br.readLumpData(levelSideDefLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelSideDefs = []
    for i in range(levelSideDefLump.size // 30):
        x = br2.readBytes(2, int)
        y = br2.readBytes(2, int)
        upperTextureName = br2.readBytes(8, str).strip("\x00")
        lowerTextureName = br2.readBytes(8, str).strip("\x00")
        middleTextureName = br2.readBytes(8, str).strip("\x00")
        sectorNumber = br2.readBytes(2, int)
        levelSideDefs.append(
            SideDef(x, y, upperTextureName, lowerTextureName, middleTextureName, sectorNumber))
        print(levelSideDefs[i])
    return levelSideDefs


"""
VERTEXES
"""


def VERTEXES(br, levelLumps: list[Lump]):
    _, levelVertexsLump = findInLumpArray(levelLumps, "VERTEXES")
    data = br.readLumpData(levelVertexsLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelVertexes = []
    for i in range(levelVertexsLump.size // 4):
        x = br2.readBytes(2, int)
        y = br2.readBytes(2, int)
        levelVertexes.append(np.array([x, y]))
    return levelVertexes

"""
SEGS
"""


def SEGS(br, levelLumps: list[Lump]):
    _, levelSegsLump = findInLumpArray(levelLumps, "SEGS")
    data = br.readLumpData(levelSegsLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelSegs = []
    for i in range(levelSegsLump.size // 12):
        startingVertexNumber = br2.readBytes(2, int)
        endingVertexNumber = br2.readBytes(2, int)
        angle = br2.readBytes(2, int)
        lineDefNumber = br2.readBytes(2, int)
        directionSameAsLineDef = br2.readBytes(2, int) == 1
        offset = br2.readBytes(2, int)

        levelSegs.append(Seg(startingVertexNumber, endingVertexNumber, angle, lineDefNumber, directionSameAsLineDef, offset))
    return levelSegs
