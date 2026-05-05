#ifndef TALL_GRASS_H
#define TALL_GRASS_H

#include <graphics.h>

// Vẽ bụi cỏ dại cao
void drawTallGrass(int x, int y, int height) {
    for (int i = 0; i < 5; i++) {
        int offsetX = x + (i - 2) * 4;
        int grassHeight = height + (i % 3) * 5;
        
        setcolor(COLOR(25 + i * 5, 50 + i * 8, 30 + i * 3));
        
        // Cọng cỏ cong
        int midX = offsetX + (i % 2 == 0 ? 3 : -3);
        int midY = y - grassHeight / 2;
        
        line(offsetX, y, midX, midY);
        line(midX, midY, offsetX + (i % 2 == 0 ? 2 : -2), y - grassHeight);
    }
}

#endif
