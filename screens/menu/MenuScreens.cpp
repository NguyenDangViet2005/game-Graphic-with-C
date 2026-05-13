#ifndef MENU_SCREENS_CPP
#define MENU_SCREENS_CPP
#include <graphics.h>
#include <string.h>

#include "../../configs/Config.cpp"

// Ve tieu de game
void drawTitle() {
    char title[] = "MONSTER SLAYER";
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 8);
    setcolor(COLOR(255, 230, 100));
    setbkcolor(COLOR(10, 15, 30));
    
    int textLen = textwidth(title);
    int textX = (SCREEN_WIDTH - textLen) / 2;
    outtextxy(textX, 80, title);
}

// Ve mot button menu
void drawMenuButton(int x, int y, int width, int height, const char* text, int isSelected) {
    if (isSelected) {
        setfillstyle(SOLID_FILL, COLOR(15, 25, 45));
        setcolor(COLOR(255, 230, 100));
    } else {
        setfillstyle(SOLID_FILL, DARKGRAY);
        setcolor(WHITE);
    }
    
    bar(x, y, x + width, y + height);
    
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x, y, x + width, y + height);
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    if (isSelected) {
        setbkcolor(COLOR(15, 25, 45));
    } else {
        setbkcolor(DARKGRAY);
    }
    
    int textLen = strlen(text);
    int estimatedWidth = textLen * 16;
    int estimatedHeight = 24;
    int textX = x + (width - estimatedWidth) / 2;
    int textY = y + (height - estimatedHeight) / 2;
    outtextxy(textX, textY, (char*)text);
}

// Ve nut back (nho hon nut menu chinh)
void drawBackButton(int x, int y, int width, int height, int isHover) {
    if (isHover) {
        setfillstyle(SOLID_FILL, COLOR(20, 35, 60));
        setcolor(COLOR(255, 230, 100));
    } else {
        setfillstyle(SOLID_FILL, COLOR(45, 45, 45));
        setcolor(COLOR(220, 220, 220));
    }

    bar(x, y, x + width, y + height);
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x, y, x + width, y + height);

    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(isHover ? COLOR(20, 35, 60) : COLOR(45, 45, 45));
    setcolor(isHover ? COLOR(255, 230, 100) : COLOR(230, 230, 230));

    const char* text = "Quay lai";
    int textW = textwidth((char*)text);
    int textH = 16;
    int textX = x + (width - textW) / 2;
    int textY = y + (height - textH) / 2;
    outtextxy(textX, textY, (char*)text);
}

void clearMenuInputState() {
    while (kbhit()) {
        getch();
    }
    while (ismouseclick(WM_LBUTTONDOWN)) {
        clearmouseclick(WM_LBUTTONDOWN);
    }
}

// Ham ve toan bo menu
void drawMenuScreen(int currentSelection, const char* menuItems[], int totalItems) {
    const int BUTTON_WIDTH = 400;
    const int BUTTON_HEIGHT = 60;
    const int BUTTON_SPACING = 20;
    const int START_Y = 250;
    
    loadAndDrawBackground();
    drawTitle();
    
    for(int i = 0; i < totalItems; i++) {
        int buttonX = SCREEN_WIDTH - BUTTON_WIDTH - 150;
        int buttonY = START_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
        drawMenuButton(buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, 
                     menuItems[i], i == currentSelection);
    }
}

// Hien thi menu chinh
int showMainMenu() {
    const int BUTTON_WIDTH = 400;
    const int BUTTON_HEIGHT = 60;
    const int BUTTON_SPACING = 20;
    const int START_Y = 250;
    
    const char* menuItems[] = {
        "Choi game",
        "Huong dan",
        "Bang diem",
        "Thoat"
    };
    
    int currentSelection = 0;
    int totalItems = 4;
    int buttonX = SCREEN_WIDTH - BUTTON_WIDTH - 150;
    int buttonY[4];
    for (int i = 0; i < totalItems; i++) {
        buttonY[i] = START_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
    }

    clearMenuInputState();
    drawMenuScreen(currentSelection, menuItems, totalItems);
    
    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();
            
            for(int i = 0; i < totalItems; i++) {
                if(mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
                   my >= buttonY[i] && my <= buttonY[i] + BUTTON_HEIGHT) {
                    return i;
                }
            }
        }
        
        int mx = mousex();
        int my = mousey();
        
        for(int i = 0; i < totalItems; i++) {
            if(mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
               my >= buttonY[i] && my <= buttonY[i] + BUTTON_HEIGHT) {
                if(currentSelection != i) {
                    drawMenuButton(buttonX, buttonY[currentSelection], BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 0);
                    
                    currentSelection = i;
                    drawMenuButton(buttonX, buttonY[currentSelection], BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 1);
                }
                break;
            }
        }
        
        if(kbhit()) {
            char key = getch();
            if(key == 0 || key == -32) {
                key = getch();
                int newSelection = currentSelection;
                
                if(key == 72) {
                    newSelection--;
                    if(newSelection < 0) newSelection = totalItems - 1;
                }
                else if(key == 80) {
                    newSelection++;
                    if(newSelection >= totalItems) newSelection = 0;
                }
                
                if(newSelection != currentSelection) {
                    drawMenuButton(buttonX, buttonY[currentSelection], BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 0);
                    
                    currentSelection = newSelection;
                    drawMenuButton(buttonX, buttonY[currentSelection], BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 1);
                }
            }
            else if(key == 13) {
                return currentSelection;
            }
            else if(key == 27) {
                return 3;
            }
        }
        
        delay(5);
    }
    
    return 3;
}

#endif
