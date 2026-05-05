#ifndef FOREST_H
#define FOREST_H

#include <graphics.h>
#include "../algorithms/index.cpp"

// Vẽ rừng tối (kết hợp tầng xa, cây, và bụi cỏ)
void drawDarkForest() {
    // Tầng cây xa
    drawFarLayer(0);
    
    // Vẽ cây lớn
    int treeSpacing = 180; 
    for (int i = 0; i < SCREEN_WIDTH / treeSpacing + 2; i++) {
        int tx = i * treeSpacing;
        int th = 300 + (tx % 50); 
        drawDarkTree(tx, GROUND_Y, th);
    }
    
    // Bụi cỏ dưới gốc
    for(int i=0; i<8; ++i) {
        int bx = 100 + i * 140;
        int by = GROUND_Y;
        int br = 35 + (i%3)*8;
        drawDarkBush(bx, by, br);
    }
}

#endif
