#ifndef INSTRUCTIONS_SCREEN_CPP
#define INSTRUCTIONS_SCREEN_CPP
#include <graphics.h>

#include "../../configs/Config.cpp"

// Hien thi man hinh huong dan
void showInstructions() {
    loadAndDrawBackground();

    const char* title = gCurrentLanguage->instructions_title;
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);

    setbkcolor(COLOR(10, 15, 30));
    setcolor(COLOR(255, 230, 100));

    int titleWidth = textwidth((char*)title);
    outtextxy((SCREEN_WIDTH - titleWidth) / 2, 80, (char*)title);
    int boxW = 750;
    int boxH = 340;
    int boxX = 410;
    int boxY = 160;

    setfillstyle(SOLID_FILL, COLOR(15, 20, 35));
    bar(boxX, boxY, boxX + boxW, boxY + boxH);

    setcolor(COLOR(255, 230, 100));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(boxX, boxY, boxX + boxW, boxY + boxH);
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(100, 120, 150));
    rectangle(boxX + 5, boxY + 5, boxX + boxW - 5, boxY + boxH - 5);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(240, 240, 250));
    setbkcolor(COLOR(15, 20, 35));

    int y = boxY + 30;
    int textX = boxX + 40;

    outtextxy(textX, y, (char*)gCurrentLanguage->instructions_move);
    y += 45;
    outtextxy(textX, y, (char*)gCurrentLanguage->instructions_attack);
    y += 45;
    outtextxy(textX, y, (char*)gCurrentLanguage->instructions_weapon);
    y += 45;
    outtextxy(textX, y, (char*)gCurrentLanguage->instructions_dash);
    y += 45;
    outtextxy(textX, y, (char*)gCurrentLanguage->instructions_slow);
    y += 45;
    outtextxy(textX, y, (char*)gCurrentLanguage->instructions_power);

    const char* backMsg = gCurrentLanguage->esc_to_back;
    setcolor(COLOR(255, 255, 0));

    setbkcolor(COLOR(10, 15, 30));
    outtextxy(textX, boxY + boxH + 30, (char*)backMsg);

    int backBtnW = 180;
    int backBtnH = 45;
    int backBtnX = 20;
    int backBtnY = 20;
    int backHover = 0;
    drawBackButton(backBtnX, backBtnY, backBtnW, backBtnH, backHover);

    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();
            if(mx >= backBtnX && mx <= backBtnX + backBtnW &&
               my >= backBtnY && my <= backBtnY + backBtnH) {
                break;
            }
        }

        int mx = mousex();
        int my = mousey();
        int isHover = (mx >= backBtnX && mx <= backBtnX + backBtnW &&
                       my >= backBtnY && my <= backBtnY + backBtnH);
        if(isHover != backHover) {
            backHover = isHover;
            drawBackButton(backBtnX, backBtnY, backBtnW, backBtnH, backHover);
        }

        if(kbhit()) {
            char key = getch();
            if(key == 27) break;
        }
        delay(10);
    }
}

#endif
