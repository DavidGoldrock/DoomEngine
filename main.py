# from CUDA_Manager import CUDA_Manager
from ConsecutiveBytearrayReader import ConsecutiveBytearrayReader
import os
# from PIL import Image
from ProcessLevelData import THINGS, LINEDEFS, ENDOOM, SIDEDEFS, VERTEXES, SEGS, SSECTORS, NODES, SECTORS, REJECT, \
    BLOCKMAP, convert_playpal_to_palettes, convert_doom_picture_to_png
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

    print(f"{numlumps=} {infotableofs=}")

    # get all lump tags
    br.pointer = infotableofs
    lumps = []
    for i in range(numlumps):
        lumps.append(br.readLump())
        print(f"loaded Lump[{i + 1}] out of [{numlumps}] <{lumps[i]}>")
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
    # print(level1Lumps)
    print(f"{len(THINGS(br, level1Lumps))=}")
    #print(f"{(LINEDEFS(br, level1Lumps))=}")
    # print(f"{SIDEDEFS(br,level1Lumps)=}")
    #print(f"{(VERTEXES(br,level1Lumps))=}")
    #print(f"{(SEGS(br,level1Lumps))=}")
    #print(f"{(SSECTORS(br,level1Lumps))=}")
    #print(f"{(NODES(br,level1Lumps))=}")
    # text = '\n'.join([str(s) for s in SECTORS(br,level1Lumps)])
    # print(text)
    #print(f"{(SECTORS(br,level1Lumps))=}")
    #print(f"{(REJECT(br,level1Lumps))=}")
    #print(f"{(BLOCKMAP(br,level1Lumps))=}")
    #palettes = convert_playpal_to_palettes(br.readLumpData(findInLumpArray(lumps,"PLAYPAL")[1]))
    #index1 ,spriteStart = findInLumpArray(lumps, "S_START")
    #index2 ,spriteEND = findInLumpArray(lumps, "S_END")
    # for i in range(index1 + 1, index2):
    #     convert_doom_picture_to_png(br.readLumpData(lumps[i]), palettes[0], f"./results/output{i}.png")
    # convert_doom_picture_to_png(br.readLumpData(findInLumpArray(lumps,"TITLEPIC")[1]),palettes[0], "output.png")

    # lumpSet = set()
    # for lump in lumps:
    #     if lump.name not in ["THINGS", "LINEDEFS", "SIDEDEFS", "VERTEXES", "SEGS", "SSECTORS", "NODES", "SECTORS", "REJECT"]:
    #         lumpSet.add(lump.name)
    # l = list(lumpSet)
    # l.sort()
    # for lump in l:
    #     print(lump, end=", ")

