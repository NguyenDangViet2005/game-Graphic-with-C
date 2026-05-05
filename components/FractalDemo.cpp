#ifndef FRACTAL_DEMO_H
#define FRACTAL_DEMO_H

#include <graphics.h>
#include "../algorithms/fractal.cpp"

// Demo tất cả các loại Fractal
void showFractalDemo() {
    cleardevice();
    setbkcolor(BLACK);
    
    // Tiêu đề
    settextstyle(BOLD_FONT, HORIZ_DIR, 4);
    setcolor(COLOR(255, 230, 100));
    setbkcolor(BLACK);
    char title[] = "FRACTAL ALGORITHMS DEMO";
    int titleWidth = textwidth(title);
    outtextxy((SCREEN_WIDTH - titleWidth) / 2, 30, title);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    
    // 1. Fractal Tree
    setcolor(WHITE);
    outtextxy(80, 100, "Fractal Tree");
    setcolor(COLOR(100, 80, 40));
    drawFractalTree(150, 280, 90, 8, 60);
    
    // 2. Koch Snowflake
    setcolor(WHITE);
    outtextxy(320, 100, "Koch Snowflake");
    setcolor(COLOR(150, 200, 255));
    drawKochSnowflake(400, 200, 70, 4);
    
    // 3. Dragon Curve
    setcolor(WHITE);
    outtextxy(580, 100, "Dragon Curve");
    setcolor(COLOR(255, 150, 50));
    drawDragonCurve(600, 150, 700, 150, 10, 1);
    
    // 4. Sierpinski Triangle
    setcolor(WHITE);
    outtextxy(850, 100, "Sierpinski Triangle");
    setcolor(COLOR(100, 255, 100));
    drawSierpinskiTriangle(950, 280, 850, 150, 1050, 150, 5);
    
    // 5. Fractal Circles
    setcolor(WHITE);
    outtextxy(100, 350, "Fractal Circles");
    setcolor(COLOR(255, 200, 100));
    drawFractalCircles(180, 480, 60, 3);
    
    // 6. Multiple Trees
    setcolor(WHITE);
    outtextxy(400, 350, "Fractal Forest");
    for (int i = 0; i < 4; i++) {
        int brightness = 80 + i * 20;
        setcolor(COLOR(brightness / 2, brightness, brightness / 3));
        drawFractalTree(400 + i * 60, 550, 90, 6 + i % 2, 40);
    }
    
    // 7. Complex Pattern
    setcolor(WHITE);
    outtextxy(750, 350, "Complex Pattern");
    setcolor(COLOR(200, 100, 255));
    drawKochSnowflake(850, 450, 50, 3);
    setcolor(COLOR(100, 200, 255));
    drawFractalCircles(850, 450, 80, 2);
    
    // Hướng dẫn
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(COLOR(200, 200, 200));
    outtextxy(SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT - 40, "Press any key to continue...");
    
    getch();
}

#endif
