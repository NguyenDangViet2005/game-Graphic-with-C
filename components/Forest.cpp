#ifndef FOREST_H
#define FOREST_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"
#include "Gravestone.cpp"
#include "TallGrass.cpp"
#include "GroundCracks.cpp"

// Vẽ rừng tối với chi tiết Fractal
void drawDarkForest() {
    // Tầng cây xa
    drawFarLayer(0);
    
    // Vẽ cây lớn (GIỮ NGUYÊN)
    int treeSpacing = 180; 
    for (int i = 0; i < SCREEN_WIDTH / treeSpacing + 2; i++) {
        int tx = i * treeSpacing;
        int th = 300 + (tx % 50); 
        drawDarkTree(tx, GROUND_Y, th);
        
        // === VẾT NỨT ĐẤT THAY CHO RỄ CÂY ===
        if (i % 3 == 0) {
            drawGroundCracks(tx, GROUND_Y, 40);
        }
        
        // === MẠNG NHỆN BÁM TRÊN THÂN CÂY ===
        if (i % 2 == 0) {
            setcolor(COLOR(55, 55, 65));
            drawSpiderWeb(tx - 15, GROUND_Y - 120, 30);
        }
        if (i % 3 == 1) {
            setcolor(COLOR(50, 50, 60));
            drawSpiderWeb(tx + 20, GROUND_Y - 180, 25);
        }
    }
    
    // Bụi cỏ dưới gốc (GIỮ NGUYÊN)
    for(int i=0; i<8; ++i) {
        int bx = 100 + i * 140;
        int by = GROUND_Y;
        int br = 35 + (i%3)*8;
        drawDarkBush(bx, by, br);
    }
    
    // Ngôi mộ cổ (GIỮ NGUYÊN)
    drawGravestone(250, GROUND_Y, 30, 50);
    drawGravestone(720, GROUND_Y, 25, 45);
    
    // === MẠNG NHỆN BÁM TRÊN BIA MỘ ===
    setcolor(COLOR(60, 60, 70));
    drawSpiderWeb(250 + 15, GROUND_Y - 35, 28);  // Bia mộ 1 - góc phải
    drawSpiderWeb(250 - 10, GROUND_Y - 25, 22);  // Bia mộ 1 - góc trái
    
    setcolor(COLOR(58, 58, 68));
    drawSpiderWeb(720 + 12, GROUND_Y - 30, 25);  // Bia mộ 2 - góc phải
    drawSpiderWeb(720 - 8, GROUND_Y - 22, 20);   // Bia mộ 2 - góc trái
    
    // === MẠNG NHỆN TRÊN CÂY FRACTAL ===
    setcolor(COLOR(52, 52, 62));
    drawSpiderWeb(120 - 25, GROUND_Y - 150, 32);
    drawSpiderWeb(350 + 30, GROUND_Y - 180, 28);
    drawSpiderWeb(580 - 20, GROUND_Y - 160, 30);
    drawSpiderWeb(820 + 25, GROUND_Y - 170, 26);
    drawSpiderWeb(1050 - 28, GROUND_Y - 155, 29);
    
    // === MẠNG NHỆN RẢI RÁC TRONG RỪNG ===
    setcolor(COLOR(48, 48, 58));
    drawSpiderWeb(180, GROUND_Y - 80, 18);
    drawSpiderWeb(450, GROUND_Y - 95, 20);
    drawSpiderWeb(680, GROUND_Y - 70, 16);
    drawSpiderWeb(920, GROUND_Y - 88, 19);
    drawSpiderWeb(1120, GROUND_Y - 75, 17);
    
    // Cỏ dại và cỏ gai sẽ được vẽ động ở layer foreground
    
    // === CÂY FRACTAL KHÔ CẰN TO (vẽ sau cùng để hiển thị trên cây thường) ===
    setcolor(COLOR(25, 20, 15));  // Màu tối hơn nhiều
    // Cây to hơn nhiều: depth 9-10, length 80-100
    drawDarkFractalTree(120, GROUND_Y, 90, 9, 85);
    drawDarkFractalTree(350, GROUND_Y, 90, 10, 95);
    drawDarkFractalTree(580, GROUND_Y, 90, 9, 90);
    drawDarkFractalTree(820, GROUND_Y, 90, 10, 100);
    drawDarkFractalTree(1050, GROUND_Y, 90, 9, 88);
}

// Vẽ lớp cỏ tiền cảnh với hiệu ứng đong đưa
void drawForestSway(float timeSec) {
    float swayBase = (float)sin(timeSec * 1.6f) * 0.12f;

    drawTallGrassAffine(220, GROUND_Y, 36, swayBase + 0.03f);
    drawTallGrassAffine(520, GROUND_Y, 40, swayBase - 0.02f);
    drawTallGrassAffine(820, GROUND_Y, 38, swayBase + 0.04f);
    drawTallGrassAffine(1040, GROUND_Y, 39, swayBase - 0.03f);

    drawThornyGrassAffine(420, GROUND_Y, 30, swayBase + 0.05f);
    drawThornyGrassAffine(920, GROUND_Y, 32, swayBase - 0.04f);
}

#endif

