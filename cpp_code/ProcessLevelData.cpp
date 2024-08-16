#include "./headers/ProcessLevelData.h"

int findInLumpArray(Lump* arr, size_t arrSize, char* tagname){
    for(size_t i = 0; i < arrSize; i ++) {
        if (strcmp(arr[i].name, tagname) == 0)
            return i;
    }
    return -1;
}

bool bitAtLocation(size_t byte, size_t n){ 
    return (byte & (2 << n) >> n) == 1;
}

Thing* THINGS(ConsecutiveBytearrayReader* br, size_t arrSize, Lump* levelLumps){
    char tagname[] = "THINGS";
    size_t levelThingLumpIndex = findInLumpArray(levelLumps, arrSize, tagname);
    uint8_t* data = new uint8_t[levelLumps[levelThingLumpIndex].size];
    br->readLumpData(data, levelLumps[levelThingLumpIndex]);
    ConsecutiveBytearrayReader* br2 = new ConsecutiveBytearrayReader(data, levelLumps[levelThingLumpIndex].size);
    Thing* levelThings = (Thing*) malloc(sizeof(Thing) * (levelLumps[levelThingLumpIndex].size / 10));
    for (size_t i = 0; i < levelLumps[levelThingLumpIndex].size / 10; i++) {
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
    }
    delete br2;
    return levelThings;
}