import struct

from PIL import Image

from ConsecutiveBytearrayReader import ConsecutiveBytearrayReader
from entites.BlockMap import BlockMap
from entites.LineDef import LineDef
from entites.Node import Node
from entites.Sector import Sector
from entites.Seg import Seg
from entites.SideDef import SideDef
from entites.SubSector import SubSector
from entites.Thing import Thing
from entites.Lump import Lump
import numpy as np


def findInLumpArray(arr, tagname):
    for index, element in enumerate(arr):
        if element.name == tagname:
            return index, element


def bitAtLocation(byte: int, n: int): return (byte & (2 ** n) >> n) == 1


def matricise(arr, row_size): return [arr[i:i + row_size] for i in range(0, len(arr), row_size)]


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
        isBlinking = bitAtLocation(code, 7)
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


def THINGS(br, levelLump: list[Lump]):
    _, levelThingLump = findInLumpArray(levelLump, "THINGS")
    data = br.readLumpData(levelThingLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelThings = []
    for i in range(levelThingLump.size // 10):
        x = br2.readBytesAsUint16()
        y = br2.readBytesAsUint16()
        angle = br2.readBytesAsUint16()
        doomType = br2.readBytesAsUint16()
        flags = br2.readBytesAsUint16()
        skillLevel12 = bitAtLocation(flags, 0)
        skillLevel3 = bitAtLocation(flags, 1)
        skillLevel45 = bitAtLocation(flags, 2)
        deaf = bitAtLocation(flags, 3)
        notSinglePlayer = bitAtLocation(flags, 4)
        levelThings.append(Thing(x, y, angle, doomType, flags, skillLevel12, skillLevel3, skillLevel45, deaf, notSinglePlayer))
    return levelThings


"""
LINEDEFS
"""


def LINEDEFS(br, levelLump: list[Lump]):
    _, levelLineDefLump = findInLumpArray(levelLump, "LINEDEFS")
    data = br.readLumpData(levelLineDefLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelLineDefs = []
    for i in range(levelLineDefLump.size // 14):
        startVertex = br2.readBytesAsUint16()
        endVertex = br2.readBytesAsUint16()
        flags = br2.readBytesAsUint16()
        sType = br2.readBytesAsUint16()
        sTag = br2.readBytesAsUint16()
        fSideDef = br2.readBytesAsUint16()
        bSideDef = br2.readBytesAsUint16()
        blocksPM = bitAtLocation(flags, 0)
        blocksM = bitAtLocation(flags, 1)
        ts = bitAtLocation(flags, 2)
        upperTextureUnpegged = bitAtLocation(flags, 3)
        lowerTextureUnpegged = bitAtLocation(flags, 4)
        secret = bitAtLocation(flags, 5)
        blocksSound = bitAtLocation(flags, 6)
        neverAutoMap = bitAtLocation(flags, 7)
        alwaysAutoMap = bitAtLocation(flags, 8)
        levelLineDefs.append(
            LineDef(startVertex, endVertex, flags, sType, sTag, fSideDef, bSideDef, blocksPM, blocksM, ts,
                    upperTextureUnpegged, lowerTextureUnpegged, secret, blocksSound, neverAutoMap, alwaysAutoMap))
    return levelLineDefs


"""
SIDEDEFS
"""


def SIDEDEFS(br, levelLump: list[Lump]):
    _, levelSideDefLump = findInLumpArray(levelLump, "SIDEDEFS")
    data = br.readLumpData(levelSideDefLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelSideDefs = []
    for i in range(levelSideDefLump.size // 30):
        x = br2.readBytesAsUint16()
        y = br2.readBytesAsUint16()
        upperTextureName = br2.readBytes(8, str).strip("\x00")
        lowerTextureName = br2.readBytes(8, str).strip("\x00")
        middleTextureName = br2.readBytes(8, str).strip("\x00")
        sectorNumber = br2.readBytesAsUint16()
        levelSideDefs.append(
            SideDef(x, y, upperTextureName, lowerTextureName, middleTextureName, sectorNumber))
    return levelSideDefs


"""
VERTEXES
"""


def VERTEXES(br, levelLump: list[Lump]):
    _, levelVertexsLump = findInLumpArray(levelLump, "VERTEXES")
    data = br.readLumpData(levelVertexsLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelVertexes = []
    for i in range(levelVertexsLump.size // 4):
        x = br2.readBytesAsUint16()
        y = br2.readBytesAsUint16()
        levelVertexes.append(np.array([x, y]))
    return levelVertexes


"""
SEGS
"""


def SEGS(br, levelLump: list[Lump]):
    _, levelSegsLump = findInLumpArray(levelLump, "SEGS")
    data = br.readLumpData(levelSegsLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelSegs = []
    for i in range(levelSegsLump.size // 12):
        startingVertexNumber = br2.readBytesAsUint16()
        endingVertexNumber = br2.readBytesAsUint16()
        angle = br2.readBytesAsUint16()
        lineDefNumber = br2.readBytesAsUint16()
        directionSameAsLineDef = br2.readBytesAsUint16() == 1
        offset = br2.readBytesAsUint16()

        levelSegs.append(
            Seg(startingVertexNumber, endingVertexNumber, angle, lineDefNumber, directionSameAsLineDef, offset))
    return levelSegs


"""
SSECTORS
"""


def SSECTORS(br, levelLump: list[Lump]):
    _, levelSsectorsLump = findInLumpArray(levelLump, "SSECTORS")
    data = br.readLumpData(levelSsectorsLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelSsectors = []
    for i in range(levelSsectorsLump.size // 4):
        segCount = br2.readBytesAsUint16()
        firstSegNumber = br2.readBytesAsUint16()

        levelSsectors.append(SubSector(segCount, firstSegNumber))
    return levelSsectors


"""
NODES
"""


def NODES(br, levelLump: list[Lump]):
    _, levelNodesLump = findInLumpArray(levelLump, "NODES")
    data = br.readLumpData(levelNodesLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelNodes = []
    for i in range(levelNodesLump.size // 28):
        x = br2.readBytesAsUint16()
        y = br2.readBytesAsUint16()

        deltaX = br2.readBytesAsUint16()
        deltaY = br2.readBytesAsUint16()

        rightBoundingBoxTop = br2.readBytesAsUint16()
        rightBoundingBoxBottom = br2.readBytesAsUint16()
        rightBoundingBoxLeft = br2.readBytesAsUint16()
        rightBoundingBoxRight = br2.readBytesAsUint16()

        leftBoundingBoxTop = br2.readBytesAsUint16()
        leftBoundingBoxBottom = br2.readBytesAsUint16()
        leftBoundingBoxLeft = br2.readBytesAsUint16()
        leftBoundingBoxRight = br2.readBytesAsUint16()

        rightChild = br2.readBytesAsUint16()
        leftChild = br2.readBytesAsUint16()

        levelNodes.append(Node(x, y, deltaX, deltaY, rightBoundingBoxTop, rightBoundingBoxBottom, rightBoundingBoxLeft,
                               rightBoundingBoxRight, leftBoundingBoxTop, leftBoundingBoxBottom, leftBoundingBoxLeft,
                               leftBoundingBoxRight, rightChild, leftChild))
    return levelNodes


"""
SECTORS
"""


def SECTORS(br, levelLump: list[Lump]):
    _, levelSectorsLump = findInLumpArray(levelLump, "SECTORS")
    data = br.readLumpData(levelSectorsLump)
    br2 = ConsecutiveBytearrayReader(data)
    levelSectors = []
    for i in range(levelSectorsLump.size // 26):
        floorHeight = br2.readBytesAsUint16()
        ceilingHeight = br2.readBytesAsUint16()
        floorTextureName = br2.readBytes(8, str).strip("\x00")
        ceilingTextureName = br2.readBytes(8, str).strip("\x00")
        lightLevel = br2.readBytesAsUint16()
        specialTag = br2.readBytesAsUint16()
        tagNumber = br2.readBytesAsUint16()

        levelSectors.append(
            Sector(floorHeight, ceilingHeight, floorTextureName, ceilingTextureName, lightLevel, specialTag, tagNumber))
    return levelSectors


"""
REJECT
"""


def REJECT(br, levelLump: list[Lump]):
    _, levelRejectLump = findInLumpArray(levelLump, "REJECT")
    data = br.readLumpData(levelRejectLump)
    rowSize = int(np.sqrt(len(data) * 8))
    bitCount = 0
    arr = []
    while bitCount < levelRejectLump.size * 8:
        byteIndex = bitCount // 8
        bitIndex = bitCount % 8
        arr.append(bitAtLocation(data[byteIndex], bitIndex))

        bitCount += 1
    matrix = np.array(matricise(arr, rowSize))
    return matrix


"""
BLOCKMAP
"""


def BLOCKMAP(br, levelLump: list[Lump]):
    _, levelBlockMapLump = findInLumpArray(levelLump, "BLOCKMAP")
    data = br.readLumpData(levelBlockMapLump)
    br2 = ConsecutiveBytearrayReader(data)

    gridX = br2.readBytesAsUint16()
    gridY = br2.readBytesAsUint16()
    columnNumber = br2.readBytesAsUint16()
    rowNumber = br2.readBytesAsUint16()

    offsets = []

    for i in range(columnNumber * rowNumber):
        offsets.append(br2.readBytesAsUint16() * 2)

    lineDefIndexByBlock = []

    for i in range(columnNumber * rowNumber):
        offset = offsets[i]
        br2.pointer = offset
        lineDefIndexByBlock.append([])

        lineDefIndex = br2.readBytes(2)
        assert lineDefIndex == b"\x00\x00"
        lineDefIndex = br2.readBytes(2)
        while lineDefIndex != b"\xff\xff":
            lineDefIndexByBlock[i].append(int.from_bytes(lineDefIndex, 'little'))
            lineDefIndex = br2.readBytes(2)
    return BlockMap(gridX, gridY, columnNumber, rowNumber, offsets, lineDefIndexByBlock)


def convert_playpal_to_palettes(playpal_data):
    # Length of each palette in bytes
    palette_size = 768
    # Number of palettes in the lump
    num_palettes = len(playpal_data) // palette_size

    # Initialize list to hold palettes
    palettes = []

    for i in range(num_palettes):
        palette_start_index = i * palette_size
        palette = playpal_data[palette_start_index:palette_start_index + palette_size]
        palettes.append(palette)

    return palettes


def convert_doom_picture_to_png(doom_image_data, palette_data, output_filename):
    # Initialize the reader
    br = ConsecutiveBytearrayReader(doom_image_data)

    # Read image metadata
    width = br.readBytesAsUint16()
    height = br.readBytesAsUint16()
    left = br.readBytesAsUint16()
    top = br.readBytesAsUint16()

    # Create an image with 8-bit color depth
    image = Image.new('P', (width, height))

    # Set the palette with DOOM's palette data
    palette = [tuple(palette_data[i:i + 3]) for i in range(0, len(palette_data), 3)]
    image.putpalette([c for color in palette for c in color] + [0] * (256 - len(palette)))

    # Set the background color to cyan (index 1 in palette)
    cyan_index = 1
    image.paste(cyan_index, [0, 0, width, height])

    # Create column array
    column_array = [br.readBytes(4, int) for _ in range(width)]

    # Read pixel data from each column
    for i in range(width):
        # Seek to the start of the column data
        br.pointer = column_array[i]

        while True:
            rowstart = br.readBytes(1, int)
            if rowstart == 255:
                break

            pixel_count = br.readBytes(1, int)
            br.readBytes(1)  # Read and ignore the dummy value

            for j in range(pixel_count):
                pixel = br.readBytes(1, int)
                # Write Pixel to the image (column i, row rowstart + j)
                image.putpixel((i, rowstart + j), pixel)

            # Read and ignore the dummy value
            br.readBytes(1)

    # Save the image as PNG
    image.save(output_filename)
