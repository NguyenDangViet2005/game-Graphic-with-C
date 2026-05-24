#ifndef SETTINGS_SCREEN_CPP
#define SETTINGS_SCREEN_CPP

#include <graphics.h>
#include <stdio.h>
#include "../../configs/Config.cpp"
#include "../../configs/Audio.cpp"

// Forward declarations of functions defined in MenuScreens.cpp
void drawMenuButton(int x, int y, int width, int height, const char* text, int isSelected);
void drawBackButton(int x, int y, int width, int height, int isHover);
void clearMenuInputState();

// Helper to get option text dynamically
static void getSettingsItemText(int idx, char* outBuf) {
    if (idx == 0) {
        sprintf(outBuf, "%s: %s", 
            gCurrentLanguage->settings_sound, 
            gSoundEnabled ? gCurrentLanguage->settings_sound_on : gCurrentLanguage->settings_sound_off
        );
    } else if (idx == 1) {
        sprintf(outBuf, "%s: %s", 
            gCurrentLanguage->settings_language, 
            gLanguage == 0 ? "Tieng Viet" : "English"
        );
    } else {
        sprintf(outBuf, "%s", gCurrentLanguage->back_button);
    }
}

// Redraw Settings screen contents
static void drawSettingsScreen(int currentSelection, int boxX, int boxY, int boxW, int boxH, 
                              int buttonX, int buttonY[], int btnW, int btnH, int totalItems,
                              int backBtnX, int backBtnY, int backBtnW, int backBtnH, int backHover) {
    loadAndDrawBackground();
    
    // Draw Header Title
    const char* title = gCurrentLanguage->settings_title;
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setbkcolor(COLOR(10, 15, 30));
    setcolor(COLOR(255, 230, 100));
    int titleWidth = textwidth((char*)title);
    outtextxy((SCREEN_WIDTH - titleWidth) / 2, 80, (char*)title);

    // Draw Box
    setfillstyle(SOLID_FILL, COLOR(15, 20, 35));
    bar(boxX, boxY, boxX + boxW, boxY + boxH);
    setcolor(COLOR(255, 230, 100));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(boxX, boxY, boxX + boxW, boxY + boxH);
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(100, 120, 150));
    rectangle(boxX + 5, boxY + 5, boxX + boxW - 5, boxY + boxH - 5);

    // Draw Buttons
    char textBuf[128];
    for (int i = 0; i < totalItems; i++) {
        getSettingsItemText(i, textBuf);
        drawMenuButton(buttonX, buttonY[i], btnW, btnH, textBuf, i == currentSelection);
    }

    // Draw Back Button at top left
    drawBackButton(backBtnX, backBtnY, backBtnW, backBtnH, backHover);
}

void showSettings() {
    int boxW = 600;
    int boxH = 320;
    int boxX = (SCREEN_WIDTH - boxW) / 2;
    int boxY = 180;

    int totalItems = 3;
    int currentSelection = 0;

    int btnW = 500;
    int btnH = 55;
    int startY = boxY + 30;
    int spacing = 20;
    int buttonX = boxX + (boxW - btnW) / 2;
    int buttonY[3];
    for (int i = 0; i < totalItems; i++) {
        buttonY[i] = startY + i * (btnH + spacing);
    }

    int backBtnW = 180;
    int backBtnH = 45;
    int backBtnX = 20;
    int backBtnY = 20;
    int backHover = 0;

    clearMenuInputState();
    drawSettingsScreen(currentSelection, boxX, boxY, boxW, boxH, buttonX, buttonY, btnW, btnH, totalItems, backBtnX, backBtnY, backBtnW, backBtnH, backHover);

    char textBuf[128];

    while (1) {
        // Mouse hover / click
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();

            // Click back button at top left
            if (mx >= backBtnX && mx <= backBtnX + backBtnW &&
                my >= backBtnY && my <= backBtnY + backBtnH) {
                break;
            }

            // Click settings items
            for (int i = 0; i < totalItems; i++) {
                if (mx >= buttonX && mx <= buttonX + btnW &&
                    my >= buttonY[i] && my <= buttonY[i] + btnH) {
                    if (i == 0) {
                        toggleSound();
                        drawSettingsScreen(currentSelection, boxX, boxY, boxW, boxH, buttonX, buttonY, btnW, btnH, totalItems, backBtnX, backBtnY, backBtnW, backBtnH, backHover);
                    } else if (i == 1) {
                        setLanguage(1 - gLanguage);
                        drawSettingsScreen(currentSelection, boxX, boxY, boxW, boxH, buttonX, buttonY, btnW, btnH, totalItems, backBtnX, backBtnY, backBtnW, backBtnH, backHover);
                    } else if (i == 2) {
                        goto exit_settings;
                    }
                }
            }
        }

        int mx = mousex();
        int my = mousey();

        // Mouse hover back button
        int isBackHover = (mx >= backBtnX && mx <= backBtnX + backBtnW &&
                           my >= backBtnY && my <= backBtnY + backBtnH);
        if (isBackHover != backHover) {
            backHover = isBackHover;
            drawBackButton(backBtnX, backBtnY, backBtnW, backBtnH, backHover);
        }

        // Mouse hover settings buttons
        for (int i = 0; i < totalItems; i++) {
            if (mx >= buttonX && mx <= buttonX + btnW &&
                my >= buttonY[i] && my <= buttonY[i] + btnH) {
                if (currentSelection != i) {
                    getSettingsItemText(currentSelection, textBuf);
                    drawMenuButton(buttonX, buttonY[currentSelection], btnW, btnH, textBuf, 0);
                    currentSelection = i;
                    getSettingsItemText(currentSelection, textBuf);
                    drawMenuButton(buttonX, buttonY[currentSelection], btnW, btnH, textBuf, 1);
                }
                break;
            }
        }

        // Keyboard inputs
        if (kbhit()) {
            char key = getch();
            if (key == 0 || key == -32) {
                key = getch();
                int newSelection = currentSelection;
                if (key == 72) { // Up arrow
                    newSelection--;
                    if (newSelection < 0) newSelection = totalItems - 1;
                } else if (key == 80) { // Down arrow
                    newSelection++;
                    if (newSelection >= totalItems) newSelection = 0;
                }

                if (newSelection != currentSelection) {
                    getSettingsItemText(currentSelection, textBuf);
                    drawMenuButton(buttonX, buttonY[currentSelection], btnW, btnH, textBuf, 0);
                    currentSelection = newSelection;
                    getSettingsItemText(currentSelection, textBuf);
                    drawMenuButton(buttonX, buttonY[currentSelection], btnW, btnH, textBuf, 1);
                }
            } else if (key == 13) { // Enter key
                playClick();
                if (currentSelection == 0) {
                    toggleSound();
                    drawSettingsScreen(currentSelection, boxX, boxY, boxW, boxH, buttonX, buttonY, btnW, btnH, totalItems, backBtnX, backBtnY, backBtnW, backBtnH, backHover);
                } else if (currentSelection == 1) {
                    setLanguage(1 - gLanguage);
                    drawSettingsScreen(currentSelection, boxX, boxY, boxW, boxH, buttonX, buttonY, btnW, btnH, totalItems, backBtnX, backBtnY, backBtnW, backBtnH, backHover);
                } else if (currentSelection == 2) {
                    break;
                }
            } else if (key == 27) { // ESC key
                playClick();
                break;
            }
        }
        delay(10);
    }

exit_settings:
    // Clean inputs when exiting
    clearMenuInputState();
}

#endif
