#ifndef SCOREBOARD_SCREEN_CPP
#define SCOREBOARD_SCREEN_CPP

#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../configs/Config.cpp"
#include "../../screens/menu/MenuCache.cpp"

// Hien thi bang diem
void showScoreboard() {
    loadAndDrawBackground();

    char title[] = "BANG DIEM";
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setbkcolor(COLOR(10, 15, 30));
    setcolor(COLOR(255, 230, 100));

    int titleWidth = textwidth(title);
    outtextxy((SCREEN_WIDTH - titleWidth) / 2, 80, title);

    int boxX = SCREEN_WIDTH / 2 - 20;
    int boxY = 160;
    int boxW = 550;
    int boxH = 400;

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

    int y = boxY + 60;
    int textX = boxX + 60;

    int scores[200];
    int scoreCount = 0;
    FILE* fp = fopen("scores.txt", "r");
    if (fp) {
        while (scoreCount < 200 && fscanf(fp, "%d", &scores[scoreCount]) == 1) {
            scoreCount++;
        }
        fclose(fp);
    }

    for (int i = 0; i < scoreCount - 1; i++) {
        for (int j = i + 1; j < scoreCount; j++) {
            if (scores[j] > scores[i]) {
                int tmp = scores[i];
                scores[i] = scores[j];
                scores[j] = tmp;
            }
        }
    }

    if (scoreCount == 0) {
        outtextxy(textX, y, (char*)"Chua co diem nao");
    } else {
        int maxRows = 6;
        if (scoreCount < maxRows) maxRows = scoreCount;
        for (int i = 0; i < maxRows; i++) {
            char line[64];
            sprintf(line, "%d. %d pt", i + 1, scores[i]);
            outtextxy(textX, y, line);
            y += 50;
        }
    }

    char backMsg2[] = "Nhan ESC de quay lai menu";
    setcolor(COLOR(255, 255, 0));

    setbkcolor(COLOR(10, 15, 30));
    outtextxy(textX, boxY + boxH + 30, backMsg2);

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
