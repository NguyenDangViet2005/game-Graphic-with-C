#ifndef MENU_LOOP_CPP
#define MENU_LOOP_CPP
#include "Menu.cpp"
// Ham vong lap game chinh - quan ly menu va lua chon
void gameLoop() {
    int running = 1;
    while(running) {
        int choice = showMainMenu();
        
        switch(choice) {
            case 0: 
                playGame();
                break;
            case 1: 
                showInstructions();
                break;
            case 2: 
                showScoreboard();
                break;
            case 3: 
                running = 0;
                break;
        }
    }
}

#endif
