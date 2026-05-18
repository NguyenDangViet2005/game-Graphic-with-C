#ifndef FIREFLY_H
#define FIREFLY_H

#include <graphics.h>
#include "../algorithms/index.cpp"

// Vẽ đom đóm (firefly)
void drawFirefly(int x, int y, int brightness) {
    // Thân đom đóm nhỏ
    setcolor(COLOR(80, 80, 60));
    setfillstyle(SOLID_FILL, COLOR(80, 80, 60));
    // Midpoint filled ellipse
    midpointFilledEllipse(x, y, 2, 3);
    
    // Ánh sáng phát ra
    int glowR = 200 + brightness;
    int glowG = 200 + brightness;
    int glowB = 100;
    if (glowR > 255) glowR = 255;
    if (glowG > 255) glowG = 255;
    
    setcolor(COLOR(glowR, glowG, glowB));
    setfillstyle(SOLID_FILL, COLOR(glowR, glowG, glowB));
    // Midpoint filled circle
    midpointFilledCircle(x, y, 4);
    
    // Hào quang ngoài
    setcolor(COLOR(glowR - 50, glowG - 50, glowB - 20));
    // Bresenham circle
    bresenhamCircle(x, y, 8);
    setcolor(COLOR(glowR - 80, glowG - 80, glowB - 40));
    // Midpoint circle
    midpointCircle(x, y, 12);
}

// Vẽ nhiều đom đóm với vị trí và độ sáng khác nhau
void drawFireflies() {
    // Đom đóm tầng xa (mờ hơn)
    drawFirefly(180, 200, 20);
    drawFirefly(420, 180, 15);
    drawFirefly(680, 220, 25);
    drawFirefly(920, 190, 18);
    drawFirefly(1100, 210, 22);
    
    // Đom đóm tầng gần (sáng hơn)
    drawFirefly(250, 350, 40);
    drawFirefly(550, 320, 45);
    drawFirefly(800, 340, 38);
    drawFirefly(1050, 360, 42);
    
    // Đom đóm bay thấp
    drawFirefly(320, GROUND_Y - 80, 35);
    drawFirefly(640, GROUND_Y - 60, 40);
    drawFirefly(950, GROUND_Y - 70, 37);
}

#endif
