#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "configs/Config.cpp"
#include "Menu.cpp"

int main() {
    printf("Dang tai...\n");
    
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monster Slayer - Dark Forest Theme");
 
    if (graphresult() != grOk) {
        printf("Tai that bai!\n");
        return 1;
    }
    
    printf("Tai thanh cong!\n");
    printf("Dang chay...\n");

    gameLoop(); 
    
    printf("Da thoat, hen gap lai!\n");
    closegraph();
    return 0;
}
