# from CUDA_Manager import CUDA_Manager
from ConsecutiveBytearrayReader import ConsecutiveBytearrayReader
import os

from ProcessLevelData import THINGS, LINEDEFS, ENDOOM, SIDEDEFS, VERTEXES
from entites.LineDef import LineDef
from entites.Thing import Thing
from entites.Lump import Lump

os.system("")


def getLumpsData(br):
    # make sure this is a valid file
    identification = br.readBytes(4, str)
    assert identification == "IWAD" or "PWAD"

    # get lump directory data
    numlumps = br.readBytes(4, int)
    infotableofs = br.readBytes(4, int)

    # get all lump tags
    br.pointer = infotableofs
    lumps = []
    for i in range(numlumps):
        lumps.append(br.readLump())
        print(f"loaded <{lumps[i].name}>")
    return lumps


def findInLumpArray(arr, tagname):
    for index, element in enumerate(arr):
        if element.name == tagname:
            return index, element


if __name__ == "__main__":
    # cuda_manager = CUDA_Manager()
    # cuda_manager.execute_command("TestFunction")
    # open wad
    with open("./resources/DOOM.WAD", "rb") as file:
        ba = file.read()
    br = ConsecutiveBytearrayReader(ba)

    lumps = getLumpsData(br)

    print(ENDOOM(br,lumps))

    index1, level1Lump = findInLumpArray(lumps, "E1M1")
    index2, level2Lump = findInLumpArray(lumps, "E1M2")
    level1Lumps = lumps[index1 + 1:index2]
    print(level1Lumps)
    # print(THINGS(br, level1Lumps))
    # print(LINEDEFS(br, level1Lumps))
    # print(SIDEDEFS(br,level1Lumps))
    print(VERTEXES(br,level1Lumps))
