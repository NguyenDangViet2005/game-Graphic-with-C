#ifndef TALL_GRASS_H
#define TALL_GRASS_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"

// Vẽ bụi cỏ dại cao
void drawTallGrass(int x, int y, int height) {
    for (int i = 0; i < 5; i++) {
        int offsetX = x + (i - 2) * 4;
        int grassHeight = height + (i % 3) * 5;
        
        setcolor(COLOR(25 + i * 5, 50 + i * 8, 30 + i * 3));
        
        // Cọng cỏ cong
        int midX = offsetX + (i % 2 == 0 ? 3 : -3);
        int midY = y - grassHeight / 2;
        
        // Bresenham line
        midpointLine(offsetX, y, midX, midY);
        midpointLine(midX, midY, offsetX + (i % 2 == 0 ? 2 : -2), y - grassHeight);
    }
}

// Vẽ bụi cỏ dại cao với hiệu ứng nghiêng (affine quay quanh gốc)
void drawTallGrassAffine(int x, int y, int height, float angle) {
    float cosA = (float)cos(angle);
    float sinA = (float)sin(angle);

    for (int i = 0; i < 5; i++) {
        int offsetX = x + (i - 2) * 4;
        int grassHeight = height + (i % 3) * 5;

        setcolor(COLOR(25 + i * 5, 50 + i * 8, 30 + i * 3));

        int midX = offsetX + (i % 2 == 0 ? 3 : -3);
        int midY = y - grassHeight / 2;
        int tipX = offsetX + (i % 2 == 0 ? 2 : -2);
        int tipY = y - grassHeight;

        float midDx = (float)(midX - offsetX);
        float midDy = (float)(midY - y);
        float tipDx = (float)(tipX - offsetX);
        float tipDy = (float)(tipY - y);

        int midXr = offsetX + (int)(midDx * cosA - midDy * sinA);
        int midYr = y + (int)(midDx * sinA + midDy * cosA);
        int tipXr = offsetX + (int)(tipDx * cosA - tipDy * sinA);
        int tipYr = y + (int)(tipDx * sinA + tipDy * cosA);

        midpointLine(offsetX, y, midXr, midYr);
        midpointLine(midXr, midYr, tipXr, tipYr);
    }
}

#endif
