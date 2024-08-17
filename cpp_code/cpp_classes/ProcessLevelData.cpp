#include "../headers/ProcessLevelData.h"

int findInLumpArray(Lump* arr, size_t arrSize, std::string tagname){
    for(size_t i = 0; i < arrSize; i ++) {
        if (arr[i].name == tagname)
            return i;
    }
    return -1;
}

bool bitAtLocation(size_t byte, size_t n){ 
    return (byte & (2 << n) >> n) == 1;
}

Thing* THINGS(ConsecutiveBytearrayReader* br, Lump* lumps, size_t numlumps){
    char tagname[] = "THINGS";
    size_t levelThingLumpIndex = findInLumpArray(lumps, numlumps, tagname);
    uint8_t* data = new uint8_t[lumps[levelThingLumpIndex].size];
    br->readLumpData(data, lumps[levelThingLumpIndex]);
    ConsecutiveBytearrayReader* br2 = new ConsecutiveBytearrayReader(data, lumps[levelThingLumpIndex].size);
    Thing* levelThings = new Thing[lumps[levelThingLumpIndex].size / 10];
    for (size_t i = 0; i < lumps[levelThingLumpIndex].size / 10; i++) {
        levelThings[i].x = br2->readBytesAsUint16();
        levelThings[i].y = br2->readBytesAsUint16();
        levelThings[i].angle = br2->readBytesAsUint16();
        levelThings[i].doomType = br2->readBytesAsUint16();
        levelThings[i].flags = br2->readBytesAsUint16();
        levelThings[i].skillLevel12 = bitAtLocation(levelThings[i].flags, 0);
        levelThings[i].skillLevel3 = bitAtLocation(levelThings[i].flags, 1);
        levelThings[i].skillLevel45 = bitAtLocation(levelThings[i].flags, 2);
        levelThings[i].deaf = bitAtLocation(levelThings[i].flags, 3);
        levelThings[i].notSinglePlayer = bitAtLocation(levelThings[i].flags, 4);

        std::cout << "Loaded Thing [" << (i+1) << "]" << " Out of [" << lumps[levelThingLumpIndex].size / 10 << "]" << levelThings[i] << std::endl;
    }
    delete br2;
    return levelThings;
}

std::string VGA_16BIT_COLOR_MEMORY_TO_STRING(uint8_t* ansicode, size_t size)
{   
    uint8_t CodeDict[] =  {30,34,32,36,31,35,33,37,90,94, 92, 96, 91, 95, 93, 97};
    std::string ret;
    int lastForeground = -1;
    int lastBackground = -1;

    for (size_t i = 0; i < size; i += 2) {
        char letter = static_cast<char>(ansicode[i]);
        uint8_t code = ansicode[i + 1];
        int foreground = code & 15;
        int background = (code & 112) >> 4;
        bool isBlinking = bitAtLocation(code, 7);

        if (foreground != lastForeground) {
            int foregroundCode = CodeDict[foreground];
            ret += "\033[" + std::to_string(foregroundCode) + "m";
        }

        if (background != lastBackground) {
            int backgroundCode = CodeDict[background] + 10;
            ret += "\033[" + std::to_string(backgroundCode) + "m";
        }

        lastForeground = foreground;
        lastBackground = background;

        ret += letter;
        if ((i / 2 + 1) % 80 == 0) {
            ret += "\033[0m";
            ret += "\n";
            lastForeground = -1;
            lastBackground = -1;
        }
    }

    return ret;

}
    


void ENDOOM(ConsecutiveBytearrayReader* br, Lump* lumps, size_t numlumps) {
    int index = findInLumpArray(lumps, numlumps,"ENDOOM");
    uint8_t data[lumps[index].size];
    br->readLumpData(data, lumps[index]);
    std::string ENDOOM_text_decoded = VGA_16BIT_COLOR_MEMORY_TO_STRING(data, lumps[index].size);
    std::cout << ENDOOM_text_decoded << std::endl;
}

// LineDef* LINEDEFS(ConsecutiveBytearrayReader* br, size_t arrSize, Lump* lumps) {
    
// }