#ifndef GROUND_CRACKS_H
#define GROUND_CRACKS_H

#include <graphics.h>

// Vẽ vết nứt đất (thay thế rễ cây)
void drawGroundCracks(int x, int y, int width) {
    setcolor(COLOR(5, 8, 12));
    setlinestyle(SOLID_LINE, 0, 2);
    
    // Vết nứt chính giữa
    int mainCrackPoints[][2] = {
        {x, y + 2},
        {x - 3, y + 8},
        {x + 2, y + 15},
        {x - 5, y + 22},
        {x + 1, y + 28}
    };
    
    for (int i = 0; i < 4; i++) {
        line(mainCrackPoints[i][0], mainCrackPoints[i][1],
             mainCrackPoints[i+1][0], mainCrackPoints[i+1][1]);
    }
    
    // Vết nứt trái
    int leftCrackPoints[][2] = {
        {x - 8, y + 5},
        {x - 15, y + 12},
        {x - 22, y + 18},
        {x - width, y + 25}
    };
    
    for (int i = 0; i < 3; i++) {
        line(leftCrackPoints[i][0], leftCrackPoints[i][1],
             leftCrackPoints[i+1][0], leftCrackPoints[i+1][1]);
    }
    
    // Vết nứt phải
    int rightCrackPoints[][2] = {
        {x + 8, y + 5},
        {x + 15, y + 11},
        {x + 20, y + 17},
        {x + width, y + 24}
    };
    
    for (int i = 0; i < 3; i++) {
        line(rightCrackPoints[i][0], rightCrackPoints[i][1],
             rightCrackPoints[i+1][0], rightCrackPoints[i+1][1]);
    }
    
    // Vết nứt nhỏ phụ
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(8, 10, 14));
    
    line(x - 12, y + 10, x - 18, y + 14);
    line(x + 12, y + 9, x + 16, y + 13);
    line(x - 5, y + 18, x - 10, y + 22);
    line(x + 4, y + 20, x + 8, y + 24);
    
    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
