#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "configs/Config.cpp"
#include "Menu.cpp"

int main() {
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monster Slayer - Dark Forest Theme");
 
    if (graphresult() != grOk) {
        return 1;
    }

    gameLoop(); 
    closegraph();
    return 0;
}
