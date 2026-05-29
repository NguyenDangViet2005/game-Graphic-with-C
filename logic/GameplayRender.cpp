#ifndef GAMEPLAY_RENDER_CPP
#define GAMEPLAY_RENDER_CPP

#include <graphics.h>
#include <math.h>
#include <stdio.h>

#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "GameplayTypes.cpp"

void drawArrowAffine(float x, float y, float angle, float scale) {
    float cosA = (float)cos(angle);
    float sinA = (float)sin(angle);

    Vec2 shaftStart = {-22.0f, 0.0f};
    Vec2 shaftEnd = {18.0f, 0.0f};
    Vec2 headA = {18.0f, 0.0f};
    Vec2 headB = {10.0f, -5.0f};
    Vec2 headC = {10.0f, 5.0f};
    Vec2 tailA = {-22.0f, 0.0f};
    Vec2 tailB = {-30.0f, -4.0f};
    Vec2 tailC = {-30.0f, 4.0f};

    Vec2 s0 = applyAffine(shaftStart, cosA, sinA, scale, scale, x, y);
    Vec2 s1 = applyAffine(shaftEnd, cosA, sinA, scale, scale, x, y);
    Vec2 h0 = applyAffine(headA, cosA, sinA, scale, scale, x, y);
    Vec2 h1 = applyAffine(headB, cosA, sinA, scale, scale, x, y);
    Vec2 h2 = applyAffine(headC, cosA, sinA, scale, scale, x, y);
    Vec2 t0 = applyAffine(tailA, cosA, sinA, scale, scale, x, y);
    Vec2 t1 = applyAffine(tailB, cosA, sinA, scale, scale, x, y);
    Vec2 t2 = applyAffine(tailC, cosA, sinA, scale, scale, x, y);

    setcolor(COLOR(255, 230, 120));
    setlinestyle(SOLID_LINE, 0, 2);
    line((int)s0.x, (int)s0.y, (int)s1.x, (int)s1.y);

    int headPts[] = {(int)h0.x, (int)h0.y, (int)h1.x, (int)h1.y, (int)h2.x, (int)h2.y};
    setfillstyle(SOLID_FILL, COLOR(255, 245, 160));
    fillpoly(3, headPts);

    int tailPts[] = {(int)t0.x, (int)t0.y, (int)t1.x, (int)t1.y, (int)t2.x, (int)t2.y};
    setfillstyle(SOLID_FILL, COLOR(220, 80, 80));
    fillpoly(3, tailPts);
}

void drawSlowShield(float x, float y, float timeSec) {
    int centerX = (int)x;
    int centerY = (int)(y - 40.0f);
    int pulse = (int)(sin(timeSec * 6.0f) * 3.0f);
    int baseR = 62 + pulse;

    setcolor(COLOR(120, 200, 255));
    setlinestyle(SOLID_LINE, 0, 2);
    circle(centerX, centerY, baseR);

    setcolor(COLOR(60, 140, 220));
    setlinestyle(DOTTED_LINE, 0, 1);
    circle(centerX, centerY, baseR + 6);

    setlinestyle(SOLID_LINE, 0, 1);
}

void drawGameOverButton(int x, int y, int width, int height, int isHover) {
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

    const char* text = gCurrentLanguage->game_over_to_menu;
    int textW = textwidth((char*)text);
    int textH = 16;
    int textX = x + (width - textW) / 2;
    int textY = y + (height - textH) / 2;
    outtextxy(textX, textY, (char*)text);
}

static void drawTextButton(int x, int y, int width, int height, int isHover, const char* text) {
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

    int textW = textwidth((char*)text);
    int textH = 16;
    int textX = x + (width - textW) / 2;
    int textY = y + (height - textH) / 2;
    outtextxy(textX, textY, (char*)text);
}

void showGameOverScreen(int score) {
    playGameOver();
    setfillstyle(SOLID_FILL, BLACK);
    bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    settextstyle(BOLD_FONT, HORIZ_DIR, 6);
    setcolor(COLOR(255, 80, 80));
    setbkcolor(BLACK);
    const char* title = gCurrentLanguage->game_over_title;
    outtextxy((SCREEN_WIDTH - textwidth((char*)title)) / 2, 220, (char*)title);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(COLOR(255, 230, 120));
    char scoreText[64];
    sprintf(scoreText, "%s: %d", gCurrentLanguage->game_over_score, score);
    outtextxy((SCREEN_WIDTH - textwidth(scoreText)) / 2, 320, scoreText);

    int btnW = 220;
    int btnH = 50;
    int btnX = (SCREEN_WIDTH - btnW) / 2;
    int btnY = 410;
    int btnHover = 0;
    drawGameOverButton(btnX, btnY, btnW, btnH, btnHover);

    while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();
            if (mx >= btnX && mx <= btnX + btnW &&
                my >= btnY && my <= btnY + btnH) {
                break;
            }
        }

        int mx = mousex();
        int my = mousey();
        int isHover = (mx >= btnX && mx <= btnX + btnW &&
                       my >= btnY && my <= btnY + btnH);
        if (isHover != btnHover) {
            btnHover = isHover;
            drawGameOverButton(btnX, btnY, btnW, btnH, btnHover);
        }

        delay(10);
    }
}

void showSpamWarningScreen() {
    int visPage = getvisualpage();
    setactivepage(visPage); // Draw directly onto the visible screen

    int popupW = 580;
    int popupH = 260;
    int popupX = (SCREEN_WIDTH - popupW) / 2;
    int popupY = (SCREEN_HEIGHT - popupH) / 2;

    // Draw the pop-up container
    setfillstyle(SOLID_FILL, COLOR(20, 24, 35));
    bar(popupX, popupY, popupX + popupW, popupY + popupH);

    // Border
    setcolor(COLOR(255, 120, 80));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(popupX, popupY, popupX + popupW, popupY + popupH);

    // Inner border
    setcolor(COLOR(100, 110, 130));
    setlinestyle(SOLID_LINE, 0, 1);
    rectangle(popupX + 5, popupY + 5, popupX + popupW - 5, popupY + popupH - 5);

    // Title
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    setcolor(COLOR(255, 100, 100));
    setbkcolor(COLOR(20, 24, 35));
    const char* title = gCurrentLanguage->spam_title;
    outtextxy(popupX + (popupW - textwidth((char*)title)) / 2, popupY + 30, (char*)title);

    // Message
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(220, 220, 220));
    const char* msg = gCurrentLanguage->spam_message;
    outtextxy(popupX + (popupW - textwidth((char*)msg)) / 2, popupY + 100, (char*)msg);

    // Button
    int btnW = 160;
    int btnH = 44;
    int btnX = popupX + (popupW - btnW) / 2;
    int btnY = popupY + 170;
    int btnHover = 0;
    const char* btnText = gCurrentLanguage->spam_button;
    drawTextButton(btnX, btnY, btnW, btnH, btnHover, btnText);

    while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
    while (1) {
        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();
            if (mx >= btnX && mx <= btnX + btnW &&
                my >= btnY && my <= btnY + btnH) {
                break;
            }
        }

        int mx = mousex();
        int my = mousey();
        int isHover = (mx >= btnX && mx <= btnX + btnW &&
                       my >= btnY && my <= btnY + btnH);
        if (isHover != btnHover) {
            btnHover = isHover;
            drawTextButton(btnX, btnY, btnW, btnH, btnHover, btnText);
        }

        delay(10);
    }
}

#endif
