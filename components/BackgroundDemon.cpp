#ifndef BACKGROUND_DEMON_H
#define BACKGROUND_DEMON_H

#include <graphics.h>
#include "../configs/Config.cpp"
#include "Cloud.cpp"
#include "Firefly.cpp"
#include "../algorithms/fractal.cpp"
#include "../algorithms/index.cpp"
#include "../algorithms/polygon_fill.cpp"
#include "Gravestone.cpp"
#include "TallGrass.cpp"

// Vết nứt đất quỷ giới màu dung nham đỏ cam
static void drawGroundCracksDemon(int x, int y, int width) {
    setcolor(COLOR(255, 69, 0));
    setlinestyle(SOLID_LINE, 0, 2);
    
    int mainCrackPoints[][2] = {
        {x, y + 2},
        {x - 3, y + 8},
        {x + 2, y + 15},
        {x - 5, y + 22},
        {x + 1, y + 28}
    };
    for (int i = 0; i < 4; i++) {
        bresenhamLine(mainCrackPoints[i][0], mainCrackPoints[i][1],
                      mainCrackPoints[i+1][0], mainCrackPoints[i+1][1]);
    }
    
    int leftCrackPoints[][2] = {
        {x - 8, y + 5},
        {x - 15, y + 12},
        {x - 22, y + 18},
        {x - width, y + 25}
    };
    for (int i = 0; i < 3; i++) {
        bresenhamLine(leftCrackPoints[i][0], leftCrackPoints[i][1],
                      leftCrackPoints[i+1][0], leftCrackPoints[i+1][1]);
    }
    
    int rightCrackPoints[][2] = {
        {x + 8, y + 5},
        {x + 15, y + 11},
        {x + 20, y + 17},
        {x + width, y + 24}
    };
    for (int i = 0; i < 3; i++) {
        bresenhamLine(rightCrackPoints[i][0], rightCrackPoints[i][1],
                      rightCrackPoints[i+1][0], rightCrackPoints[i+1][1]);
    }
    
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(255, 140, 0));
    bresenhamLine(x - 12, y + 10, x - 18, y + 14);
    bresenhamLine(x + 12, y + 9, x + 16, y + 13);
    bresenhamLine(x - 5, y + 18, x - 10, y + 22);
    bresenhamLine(x + 4, y + 20, x + 8, y + 24);
    setlinestyle(SOLID_LINE, 0, 1);
}

// Vẽ background Quỷ giới
void drawBackgroundDemon() {
    // Vẽ nền trời Gradient từ đen đến đỏ thẫm/cam lửa (hellish gradient)
    for(int i = 0; i < GROUND_Y; i++) {
        float ratio = (float)i / GROUND_Y;
        int r = 12 + (int)(ratio * 108);   
        int g = 2 + (int)(ratio * 18); 
        int b = 2 + (int)(ratio * 8); 
        setcolor(COLOR(r, g, b));
        bresenhamLine(0, i, SCREEN_WIDTH, i);
    }
    
    // Vẽ Trăng Máu (Blood Moon) ở góc trên bên phải
    int moonX = SCREEN_WIDTH - 150;
    int moonY = 80;
    int moonRadius = 50;
    
    // Ánh sáng trăng máu
    setcolor(COLOR(65, 15, 15));
    setfillstyle(SOLID_FILL, COLOR(65, 15, 15));
    fillellipse(moonX, moonY, moonRadius + 15, moonRadius + 15);
    
    setcolor(COLOR(90, 20, 20));
    setfillstyle(SOLID_FILL, COLOR(90, 20, 20));
    fillellipse(moonX, moonY, moonRadius + 8, moonRadius + 8);
    
    // Mặt trăng chính - màu đỏ máu rực
    setcolor(COLOR(190, 30, 30));
    setfillstyle(SOLID_FILL, COLOR(190, 30, 30));
    fillellipse(moonX, moonY, moonRadius, moonRadius);
    
    // Chi tiết trên trăng máu - màu đỏ đen thẫm
    setcolor(COLOR(100, 15, 15));
    setfillstyle(SOLID_FILL, COLOR(100, 15, 15));
    fillellipse(moonX - 15, moonY - 10, 12, 10);
    fillellipse(moonX + 18, moonY + 5, 10, 8);
    fillellipse(moonX + 5, moonY + 18, 8, 7);
    fillellipse(moonX - 10, moonY + 12, 6, 5);
    
    // Vẽ nền đất dung nham/quỷ giới
    // Lớp đất chính - đỏ đen cực đậm
    setcolor(COLOR(16, 6, 6));
    setfillstyle(SOLID_FILL, COLOR(16, 6, 6));
    bar(0, GROUND_Y, SCREEN_WIDTH, SCREEN_HEIGHT);
    
    // Lớp đất phía trên - đỏ cam tối màu
    setcolor(COLOR(28, 10, 10));
    setfillstyle(SOLID_FILL, COLOR(28, 10, 10));
    bar(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y + 40);
    
    // Lớp cỏ/gai quỷ giới tối màu có đốm lửa
    for(int i = 0; i < SCREEN_WIDTH; i += 40) {
        int h = 25 + (i % 15);
        int darkness = (i % 3);
        
        if(darkness == 0) {
            setcolor(COLOR(32, 10, 10));
            setfillstyle(SOLID_FILL, COLOR(32, 10, 10));
        } else if(darkness == 1) {
            setcolor(COLOR(40, 12, 12));
            setfillstyle(SOLID_FILL, COLOR(40, 12, 12));
        } else {
            setcolor(COLOR(48, 16, 16));
            setfillstyle(SOLID_FILL, COLOR(48, 16, 16));
        }
        
        bar(i, GROUND_Y, i + 40, GROUND_Y + h);
        
        if(i % 5 == 0) {
            // Các đường nứt lửa li ti trong cỏ
            setcolor(COLOR(220, 80, 20));
            bresenhamLine(i + 10, GROUND_Y + 5, i + 10, GROUND_Y + h - 3);
            bresenhamLine(i + 25, GROUND_Y + 8, i + 25, GROUND_Y + h - 2);
        }
    }
    
    // Chi tiết bụi gai quỷ đỏ thẫm
    for(int i = 0; i < 50; i++) {
        int gx = 20 + i * 24;
        int gy = GROUND_Y + 2 + (i % 6);
        
        if(i % 3 == 0) {
            setcolor(COLOR(120, 30, 20));
            bresenhamLine(gx, gy, gx, gy - 3);
            bresenhamLine(gx + 1, gy, gx + 1, gy - 4);
        }
    }
    
    // Border mặt đất màu cam lửa/dung nham nóng chảy
    setcolor(COLOR(180, 50, 10));
    setlinestyle(SOLID_LINE, 0, 3);
    bresenhamThickLine(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y, 3);
    
    // Vẽ đốm lửa bốc lên
    auto drawFireSpark = [](int cx, int cy) {
        int points[] = {
            cx, cy - 3,
            cx + 3, cy,
            cx, cy + 3,
            cx - 3, cy,
            cx, cy - 3
        };
        setcolor(COLOR(255, 120, 20));
        setfillstyle(SOLID_FILL, COLOR(255, 200, 30));
        fillpoly(5, points);
    };
    
    drawFireSpark(100, 50);
    drawFireSpark(150, 80);
    drawFireSpark(320, 60);
    drawFireSpark(450, 40);
    drawFireSpark(700, 90);
    drawFireSpark(800, 50);
    drawFireSpark(950, 70);
}

void drawMountainsDemon() {
    // Núi 1
    int pts1[] = {
        -50, GROUND_Y,
        150, GROUND_Y - 260,
        350, GROUND_Y
    };
    setcolor(COLOR(20, 5, 5));
    setfillstyle(SOLID_FILL, COLOR(20, 5, 5));
    fillpoly(3, pts1);
    
    // Núi 2 (sau núi 1, lệch phải)
    int pts2[] = {
        200, GROUND_Y,
        450, GROUND_Y - 320,
        700, GROUND_Y
    };
    setcolor(COLOR(16, 4, 4));
    setfillstyle(SOLID_FILL, COLOR(16, 4, 4));
    fillpoly(3, pts2);
    
    // Núi 3
    int pts3[] = {
        550, GROUND_Y,
        800, GROUND_Y - 240,
        1050, GROUND_Y
    };
    setcolor(COLOR(22, 6, 6));
    setfillstyle(SOLID_FILL, COLOR(22, 6, 6));
    fillpoly(3, pts3);
    
    // Núi 4
    int pts4[] = {
        850, GROUND_Y,
        1100, GROUND_Y - 290,
        1300, GROUND_Y
    };
    setcolor(COLOR(18, 5, 5));
    setfillstyle(SOLID_FILL, COLOR(18, 5, 5));
    fillpoly(3, pts4);
    
    // Vẽ dòng dung nham chảy trên sườn núi (lava flows)
    setlinestyle(SOLID_LINE, 0, 3);
    setcolor(COLOR(255, 69, 0)); // Màu dung nham nóng chảy
    
    line(450, GROUND_Y - 320, 410, GROUND_Y - 180);
    line(410, GROUND_Y - 180, 430, GROUND_Y - 100);
    line(430, GROUND_Y - 100, 390, GROUND_Y);
    
    setcolor(COLOR(230, 60, 10));
    line(1100, GROUND_Y - 290, 1140, GROUND_Y - 150);
    line(1140, GROUND_Y - 150, 1110, GROUND_Y);
    
    setlinestyle(SOLID_LINE, 0, 1);
}

// Vẽ Rừng Quỷ
void drawDarkForestDemon() {
    // Vẽ dãy núi ở phía xa thay thế tầng cây
    drawMountainsDemon();
    
    // Không vẽ cây lớn nguyên bản, chỉ vẽ nứt đất dung nham tại các vị trí cố định
    for (int i = 0; i < 6; i++) {
        int cx = 120 + i * 200;
        drawGroundCracksDemon(cx, GROUND_Y, 35);
    }
    
    for(int i=0; i<8; ++i) {
        int bx = 100 + i * 140;
        int by = GROUND_Y;
        int br = 35 + (i%3)*8;
        drawDarkBush(bx, by, br);
    }
    
    drawGravestone(250, GROUND_Y, 30, 50);
    drawGravestone(720, GROUND_Y, 25, 45);
    
    setcolor(COLOR(130, 30, 30));
    drawSpiderWeb(250 + 15, GROUND_Y - 35, 28);
    drawSpiderWeb(250 - 10, GROUND_Y - 25, 22);
    
    setcolor(COLOR(110, 25, 25));
    drawSpiderWeb(720 + 12, GROUND_Y - 30, 25);
    drawSpiderWeb(720 - 8, GROUND_Y - 22, 20);
    
    setcolor(COLOR(105, 20, 20));
    drawSpiderWeb(120 - 25, GROUND_Y - 150, 32);
    drawSpiderWeb(350 + 30, GROUND_Y - 180, 28);
    drawSpiderWeb(580 - 20, GROUND_Y - 160, 30);
    drawSpiderWeb(820 + 25, GROUND_Y - 170, 26);
    drawSpiderWeb(1050 - 28, GROUND_Y - 155, 29);
    
    setcolor(COLOR(95, 15, 15));
    drawSpiderWeb(180, GROUND_Y - 80, 18);
    drawSpiderWeb(450, GROUND_Y - 95, 20);
    drawSpiderWeb(680, GROUND_Y - 70, 16);
    drawSpiderWeb(920, GROUND_Y - 88, 19);
    drawSpiderWeb(1120, GROUND_Y - 75, 17);
    
    setcolor(COLOR(45, 12, 10)); // Chỉ để lại cây khô ma quỷ đỏ thẫm (Fractal Tree)
    drawDarkFractalTree(120, GROUND_Y, 90, 9, 85);
    drawDarkFractalTree(350, GROUND_Y, 90, 10, 95);
    drawDarkFractalTree(580, GROUND_Y, 90, 9, 90);
    drawDarkFractalTree(820, GROUND_Y, 90, 10, 100);
    drawDarkFractalTree(1050, GROUND_Y, 90, 9, 88);
}

#endif
