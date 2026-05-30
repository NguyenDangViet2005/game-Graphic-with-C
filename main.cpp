#include <graphics.h>
#include <stdio.h>
#include <windows.h>

#include "languages/Language.h"

int gSoundEnabled = 1;
int gLanguage = 0;
const Language* gCurrentLanguage = NULL;

#include "configs/Config.cpp"
#include "configs/Audio.cpp"
#include "screens/menu/Menu.cpp"

main() {
    gCurrentLanguage = &langVi;
    int screenW = GetSystemMetrics(SM_CXSCREEN);
    int screenH = GetSystemMetrics(SM_CYSCREEN);
    int winX = (screenW - SCREEN_WIDTH) / 2;
    int winY = (screenH - SCREEN_HEIGHT) / 2 - 30;
    if (winX < 0) winX = 0;
    if (winY < 0) winY = 0;
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monster Slayer - Dark Forest Theme", winX, winY);
    if (graphresult() != grOk) {
        printf("Tai that bai!\n");
        return 1;   
    }
    printf("Tai thanh cong!\n");
    initAudio();
    gameLoop(); 
    shutdownAudio();
    exit(0);
}
