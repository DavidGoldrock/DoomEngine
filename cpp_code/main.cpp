#include <iostream>
#include "./headers/Lump.h"

int main() {
    char text[] = "hello";
    char text2[] = "hello";
    std::cout << Lump(3,2,text) << std::endl;
    return 0;
}