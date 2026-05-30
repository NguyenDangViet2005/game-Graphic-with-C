#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <graphics.h>
#include "../configs/Config.cpp"
#include "Cloud.cpp"
#include "Firefly.cpp"
#include "GroundCracks.cpp"
#include "Gravestone.cpp"
#include "TallGrass.cpp"
#include "../algorithms/fractal.cpp"
#include "../algorithms/index.cpp"
#include "../algorithms/polygon_fill.cpp"

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

// Vẽ background (trời, đám mây, đất, cỏ)
void drawBackground() {
    //vẽ nền trời Gradient từ đen xanh đậm đến xanh dương nhạt - tối hơn
    for(int i = 0; i < GROUND_Y; i++) {
        float ratio = (float)i / GROUND_Y;
        int r = 2 + (int)(ratio * 8);   
        int g = 3 + (int)(ratio * 10); 
        int b = 10 + (int)(ratio * 18); 
        setcolor(COLOR(r, g, b));
        // Bresenham line
        bresenhamLine(0, i, SCREEN_WIDTH, i);
    }
    
    // Vẽ mặt trăng ở góc trên bên phải
    int moonX = SCREEN_WIDTH - 150;
    int moonY = 80;
    int moonRadius = 50;
    
    // Ánh sáng mặt trăng - giảm độ sáng
    setcolor(COLOR(30, 35, 50));
    setfillstyle(SOLID_FILL, COLOR(30, 35, 50));
    fillellipse(moonX, moonY, moonRadius + 15, moonRadius + 15);
    
    setcolor(COLOR(45, 50, 65));
    setfillstyle(SOLID_FILL, COLOR(45, 50, 65));
    fillellipse(moonX, moonY, moonRadius + 8, moonRadius + 8);
    
    // Mặt trăng chính - màu trắng xám nhạt hơn
    setcolor(COLOR(180, 185, 190));
    setfillstyle(SOLID_FILL, COLOR(180, 185, 190));
    fillellipse(moonX, moonY, moonRadius, moonRadius);
    
    // Chi tiết trên mặt trăng - tối hơn (vẽ trước)
    setcolor(COLOR(150, 155, 160));
    setfillstyle(SOLID_FILL, COLOR(150, 155, 160));
    fillellipse(moonX - 15, moonY - 10, 12, 10);
    fillellipse(moonX + 18, moonY + 5, 10, 8);
    fillellipse(moonX + 5, moonY + 18, 8, 7);
    fillellipse(moonX - 10, moonY + 12, 6, 5);
    
    
    // Đám mây đã được chuyển sang chế độ bay bồng bềnh động (drawFloatingClouds)
    
    
    // vẽ nền đất và cỏ
    
    // Lớp đất chính - xanh đen đậm
    setcolor(COLOR(8, 12, 18));
    setfillstyle(SOLID_FILL, COLOR(8, 12, 18));
    bar(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // Lớp đất gradient sáng hơn chút ở trên
    setcolor(COLOR(12, 16, 22));
    setfillstyle(SOLID_FILL, COLOR(12, 16, 22));
    bar(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y + 40);
    
    // Layer cỏ tối
    for(int i = 0; i < SCREEN_WIDTH; i += 40) {
        int h = 25 + (i % 15);
        int darkness = (i % 3);
        
        if(darkness == 0) {
            setcolor(COLOR(15, 20, 28));
            setfillstyle(SOLID_FILL, COLOR(15, 20, 28));
        } else if(darkness == 1) {
            setcolor(COLOR(18, 24, 32));
            setfillstyle(SOLID_FILL, COLOR(18, 24, 32));
        } else {
            setcolor(COLOR(20, 28, 35));
            setfillstyle(SOLID_FILL, COLOR(20, 28, 35));
        }
        
        bar(i, GROUND_Y, i + 40, GROUND_Y + h);
        
        if(i % 5 == 0) {
            setcolor(COLOR(10, 14, 20));
            bresenhamLine(i + 10, GROUND_Y + 5, i + 10, GROUND_Y + h - 3);
            bresenhamLine(i + 25, GROUND_Y + 8, i + 25, GROUND_Y + h - 2);
        }
    }
    
    // Chi tiết bụi cỏ nhỏ xíu
    for(int i = 0; i < 50; i++) {
        int gx = 20 + i * 24;
        int gy = GROUND_Y + 2 + (i % 6);
        
        if(i % 3 == 0) {
            setcolor(COLOR(22, 32, 36));
            bresenhamLine(gx, gy, gx, gy - 3);
            bresenhamLine(gx + 1, gy, gx + 1, gy - 4);
        }
    }
    
    // Border mặt đất
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);
    // Bresenham line (thick)
    bresenhamThickLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y, 3);

    // Vẽ thêm các ngôi sao lấp lánh trang trí nền trời bằng tô màu đệ quy giới hạn
    auto drawSmallStar = [](int cx, int cy) {
        setcolor(WHITE);
        line(cx, cy - 4, cx + 4, cy);
        line(cx + 4, cy, cx, cy + 4);
        line(cx, cy + 4, cx - 4, cy);
        line(cx - 4, cy, cx, cy - 4);
        recursiveBoundaryFillBounded(cx, cy, YELLOW, WHITE, cx - 5, cy - 5, cx + 5, cy + 5);
    };

    drawSmallStar(100, 50);
    drawSmallStar(150, 80);
    drawSmallStar(320, 60);
    drawSmallStar(450, 40);
    drawSmallStar(700, 90);
    drawSmallStar(800, 50);
    drawSmallStar(950, 70);
}

#endif 
