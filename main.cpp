#include <graphics.h>
#include <stdio.h>

#include "configs/Config.cpp"
#include "configs/Audio.cpp"
#include "screens/menu/Menu.cpp"

int main() {
    printf("Dang tai...\n");
    
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monster Slayer - Dark Forest Theme");
 
    if (graphresult() != grOk) {
        printf("Tai that bai!\n");
        return 1;   
    }
    
    printf("Tai thanh cong!\n");
    printf("Dang chay...\n");

    initAudio();
    gameLoop(); 
    
    printf("Da thoat, hen gap lai!\n");
    shutdownAudio();
    closegraph();
    return 0;
}
