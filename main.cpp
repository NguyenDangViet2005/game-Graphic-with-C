#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

#include "configs/Config.cpp"
#include "Menu.cpp"

int main() {
    printf("Initializing graphics...\n");
    
    initwindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Monster Slayer - Dark Forest Theme");
 
    if (graphresult() != grOk) {
        printf("Graphics initialization failed!\n");
        return 1;
    }
    
    printf("Graphics initialized successfully!\n");
    printf("Starting game loop...\n");

    gameLoop(); 
    
    printf("Game ended, closing graphics...\n");
    closegraph();
    return 0;
}
