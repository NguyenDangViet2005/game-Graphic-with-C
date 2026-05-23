#ifndef FIREFLY_H
#define FIREFLY_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"

// Vẽ đom đóm với tỉ lệ co giãn (affine dãn)
void drawFireflyScaled(int x, int y, int brightness, float scale) {
    if (scale < 0.4f) scale = 0.4f;

    // Thân đom đóm nhỏ
    setcolor(COLOR(80, 80, 60));
    setfillstyle(SOLID_FILL, COLOR(80, 80, 60));
    // Midpoint filled ellipse
    int bodyRx = (int)(2 * scale);
    int bodyRy = (int)(3 * scale);
    if (bodyRx < 1) bodyRx = 1;
    if (bodyRy < 1) bodyRy = 1;
    midpointFilledEllipse(x, y, bodyRx, bodyRy);
    
    // Ánh sáng phát ra
    int glowR = 200 + brightness;
    int glowG = 200 + brightness;
    int glowB = 100;
    if (glowR > 255) glowR = 255;
    if (glowG > 255) glowG = 255;
    
    setcolor(COLOR(glowR, glowG, glowB));
    setfillstyle(SOLID_FILL, COLOR(glowR, glowG, glowB));
    // Midpoint filled circle
    int coreR = (int)(4 * scale);
    if (coreR < 1) coreR = 1;
    midpointFilledCircle(x, y, coreR);
    
    // Hào quang ngoài
    setcolor(COLOR(glowR - 50, glowG - 50, glowB - 20));
    // Bresenham circle
    int haloR1 = (int)(8 * scale);
    if (haloR1 < 2) haloR1 = 2;
    bresenhamCircle(x, y, haloR1);
}

// Vẽ đom đóm (firefly)
void drawFirefly(int x, int y, int brightness) {
    // Giu ham cu de tuong thich
    drawFireflyScaled(x, y, brightness, 1.0f);
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

// Vẽ nhiều đom đóm với hiệu ứng co giãn nhịp nhàng
void drawFirefliesAnimated(float timeSec) {
    const int count = 6;
    const int xs[count] = {180, 680, 1100, 250, 800, 640};
    const int ys[count] = {200, 220, 210, 350, 340, GROUND_Y - 60};
    const int br[count] = {20, 25, 22, 40, 38, 40};

    for (int i = 0; i < count; i++) {
        float phase = (float)i * 0.7f;
        float scale = 1.0f + (float)sin(timeSec * 2.4f + phase) * 0.25f;
        drawFireflyScaled(xs[i], ys[i], br[i], scale);
    }
}

#endif
