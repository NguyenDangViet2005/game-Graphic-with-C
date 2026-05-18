#ifndef LOADING_SCREEN_H
#define LOADING_SCREEN_H

#include <graphics.h>
#include "../configs/Config.cpp"
#include "../algorithms/index.cpp"

// Vẽ màn hình loading đơn giản với progress bar mượt mà
void drawLoadingScreen(int progress, const char* statusText = "Loading...") {
    static int lastProgress = -1;

    if (progress < 0) progress = 0;
    if (progress > 100) progress = 100;

    int barWidth = 600;
    int barHeight = 35;
    int barX = (SCREEN_WIDTH - barWidth) / 2;
    int barY = SCREEN_HEIGHT / 2 + 40;
    int innerWidth = barWidth - 6;

    if (lastProgress < 0 || progress < lastProgress || progress == 0) {
        // Nền đen mượt
        setcolor(BLACK);
        setfillstyle(SOLID_FILL, BLACK);
        bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Tiêu đề game
        settextstyle(BOLD_FONT, HORIZ_DIR, 7);
        setcolor(COLOR(255, 230, 100));
        setbkcolor(BLACK);
        char title[] = "MONSTER SLAYER";
        int titleWidth = textwidth(title);
        outtextxy((SCREEN_WIDTH - titleWidth) / 2, SCREEN_HEIGHT / 2 - 100, title);

        // Subtitle
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        setcolor(COLOR(180, 180, 180));
        char subtitle[] = "Prepare for Adventure";
        int subtitleWidth = textwidth(subtitle);
        outtextxy((SCREEN_WIDTH - subtitleWidth) / 2, SCREEN_HEIGHT / 2 - 40, subtitle);

        // Shadow cho depth
        setcolor(COLOR(20, 20, 20));
        setfillstyle(SOLID_FILL, COLOR(20, 20, 20));
        bar(barX + 3, barY + 3, barX + barWidth + 3, barY + barHeight + 3);

        // Background bar
        setcolor(COLOR(40, 40, 50));
        setfillstyle(SOLID_FILL, COLOR(40, 40, 50));
        bar(barX, barY, barX + barWidth, barY + barHeight);

        // Viền bar
        setcolor(COLOR(100, 100, 120));
        setlinestyle(SOLID_LINE, 0, 2);
        rectangle(barX, barY, barX + barWidth, barY + barHeight);

        lastProgress = 0;
    }

    int lastFill = (innerWidth * lastProgress) / 100;
    int fillWidth = (innerWidth * progress) / 100;
    if (fillWidth > innerWidth) fillWidth = innerWidth;
    if (fillWidth < lastFill) fillWidth = lastFill;

    if (fillWidth > lastFill) {
        for (int i = lastFill; i < fillWidth; i++) {
            float ratio = (float)i / (float)innerWidth;
            int r = 200 + (int)(ratio * 55);
            int g = 180 + (int)(ratio * 50);
            int b = 30 + (int)(ratio * 20);
            setcolor(COLOR(r, g, b));
            bresenhamLine(barX + 3 + i, barY + 3, barX + 3 + i, barY + barHeight - 3);
        }
    }

    if (fillWidth > 0) {
        setcolor(COLOR(255, 240, 150));
        bresenhamLine(barX + 3, barY + 3, barX + 3 + fillWidth, barY + 3);
        bresenhamLine(barX + 3, barY + 4, barX + 3 + fillWidth, barY + 4);
    }

    setfillstyle(SOLID_FILL, BLACK);
    bar(barX, barY + barHeight + 18, barX + barWidth, barY + barHeight + 75);

    // Hiển thị phần trăm và status
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(255, 255, 255));
    char percentText[20];
    sprintf(percentText, "%d%%", progress);
    int percentWidth = textwidth(percentText);
    outtextxy((SCREEN_WIDTH - percentWidth) / 2, barY + barHeight + 25, percentText);

    // Status text
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(COLOR(150, 150, 150));
    int statusWidth = textwidth((char*)statusText);
    outtextxy((SCREEN_WIDTH - statusWidth) / 2, barY + barHeight + 55, (char*)statusText);

    lastProgress = progress;
}

#endif


