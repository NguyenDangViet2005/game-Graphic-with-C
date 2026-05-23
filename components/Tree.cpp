#ifndef TREE_H
#define TREE_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"
#include "../algorithms/polygon_fill.cpp"
#include "../configs/Config.cpp"

// Vẽ tầng cây xa
// yOffset: 0 cho game (cao), 100 cho menu (thấp)
void drawFarLayer(int yOffset = 0) {
    int farY = GROUND_Y + yOffset;
    
    // Mảng cây
    int trees[] = {
        // {x, width, height}
        30, 15, 245,       // Cây to
        75, 22, 315,       // Cây rất to
        120, 18, 270,      // Cây to
        165, 25, 340,      // Cây cực to
        210, 12, 235,      // Cây trung bình
        255, 20, 295,      // Cây to
        305, 16, 260,      // Cây to
        350, 28, 350,      // Cây cực to
        400, 14, 245,      // Cây trung bình
        445, 19, 285,      // Cây to
        495, 23, 320,      // Cây rất to
        545, 11, 230,      // Cây trung bình
        590, 17, 275,      // Cây to
        640, 26, 335,      // Cây cực to
        685, 15, 255,      // Cây to
        730, 21, 305,      // Cây rất to
        780, 13, 240,      // Cây trung bình
        825, 24, 325,      // Cây rất to
        875, 18, 280,      // Cây to
        920, 16, 265,      // Cây to
        970, 27, 345,      // Cây cực to
        1020, 20, 295,     // Cây to
        1070, 14, 250      // Cây trung bình
    };
    
    // Vẽ từng thân cây
    int numTrees = sizeof(trees) / sizeof(trees[0]) / 3;
    for(int i = 0; i < numTrees; i++) {
        int tx = trees[i * 3];
        int tw = trees[i * 3 + 1];
        int th = trees[i * 3 + 2];
        
        // Thân cây phía xa
        setcolor(COLOR(3, 3, 3));
        setfillstyle(SOLID_FILL, COLOR(3, 3, 3));
        
        // Vẽ thân hình thang (dưới rộng hơn trên)
        int topW = (int)(tw * 0.75);
        int bottomW = tw;
        
        int points[] = {
            tx - bottomW/2, farY,
            tx + bottomW/2, farY,
            tx + topW/2, farY - th,
            tx - topW/2, farY - th,
            tx - bottomW/2, farY
        };
        
        // To mau bang fillpoly de tranh tran stack
        setfillstyle(SOLID_FILL, COLOR(3, 3, 3));
        fillpoly(4, points);
        
        // Viền đen sâu
        setcolor(COLOR(1, 1, 1));
        midpointLine(tx - bottomW/2, farY, tx - topW/2, farY - th);
        midpointLine(tx + bottomW/2, farY, tx + topW/2, farY - th);
        
        // Kết cây nhỏ (chỉ cây to mới có)
        if(tw >= 18 && i % 2 == 0) {
            setcolor(COLOR(2, 2, 2));
            setfillstyle(SOLID_FILL, COLOR(2, 2, 2));
            fillellipse(tx - tw/4, farY - th * 0.18, 4, 5);
        }
    }
}

// Vẽ cây lớn
void drawDarkTree(int x, int y, int height) {
    int trunkW = height / 6;
    
    // gốc cây
    setcolor(COLOR(12, 12, 12));
    setfillstyle(SOLID_FILL, COLOR(12, 12, 12));
    fillellipse(x, y + 5, trunkW * 2, 8);
    
    // thân cây và nhánh
    
    // Thân chính - hình thang
    int trunk[] = {
        x - trunkW/2, y,
        x - trunkW/3, (int)(y - height * 0.6),
        x + trunkW/3, (int)(y - height * 0.6),
        x + trunkW/2, y
    };
    
    // Thân cây tối màu - đen nâu đậm trong đêm
    setcolor(COLOR(8, 5, 3));
    setfillstyle(SOLID_FILL, COLOR(8, 5, 3));
    
    // To mau than bang fillpoly de tranh tran stack
    setfillstyle(SOLID_FILL, COLOR(8, 5, 3));
    fillpoly(4, trunk);
    
    // Phần thân trên - đậm hơn
    int trunk2[] = {
        x - trunkW/3, (int)(y - height * 0.6),
        x - trunkW/5, (int)(y - height * 0.85),
        x + trunkW/5, (int)(y - height * 0.85),
        x + trunkW/3, (int)(y - height * 0.6)
    };
    setcolor(COLOR(15, 10, 7));
    setfillstyle(SOLID_FILL, COLOR(15, 10, 7));
    
    // To mau than tren bang fillpoly de tranh tran stack
    setfillstyle(SOLID_FILL, COLOR(15, 10, 7));
    fillpoly(4, trunk2);
    
    // Vẽ vân gỗ dọc - đen đậm
    setcolor(COLOR(8, 5, 3));
    setlinestyle(SOLID_LINE, 0, 1);
    for(int i = 0; i < 8; i++) {
        int yPos = y - (i * height * 0.08);
        midpointLine(x - trunkW/4, yPos, x - trunkW/4, yPos + 15);
        midpointLine(x + trunkW/6, yPos + 7, x + trunkW/6, yPos + 20);
    }
    
    // Vân ngang và mắt gỗ
    for(int i = 0; i < 5; i++) {
        int yPos = y - height * 0.15 * i - 10;
        midpointEllipse(x, yPos, trunkW/3, 3);
    }
    
    // Mắt gỗ và vết nứt - gần đen
    setcolor(COLOR(5, 3, 2));
    fillellipse(x - trunkW/5, y - height * 0.3, 4, 6);
    fillellipse(x + trunkW/7, y - height * 0.5, 3, 5);
    midpointLine(x - trunkW/8, y - height * 0.4, x - trunkW/8 + 2, y - height * 0.4 + 18);
    
    // Viền thân cây - đen sâu
    setcolor(COLOR(6, 4, 3));
    setlinestyle(SOLID_LINE, 0, 2);
    drawpoly(4, trunk);
    drawpoly(4, trunk2);
    
    // vẽ nhánh - đen sâu
    setcolor(COLOR(10, 7, 5));
    setlinestyle(SOLID_LINE, 0, 3);
    
    // Nhánh trái
    int branchY1 = y - height * 0.7;
    midpointLine(x - trunkW/4, branchY1, x - trunkW * 2, branchY1 - 30);
    midpointLine(x - trunkW * 2, branchY1 - 30, x - trunkW * 2.3, branchY1 - 35);
    
    // Nhánh phải
    int branchY2 = y - height * 0.65;
    midpointLine(x + trunkW/4, branchY2, x + trunkW * 1.8, branchY2 - 25);
    midpointLine(x + trunkW * 1.8, branchY2 - 25, x + trunkW * 2.2, branchY2 - 20);
    
    // Nhánh trái dưới
    int branchY3 = y - height * 0.5;
    midpointLine(x - trunkW/5, branchY3, x - trunkW * 1.5, branchY3 - 15);
    
    // Nhánh phải dưới
    int branchY4 = y - height * 0.55;
    midpointLine(x + trunkW/6, branchY4, x + trunkW * 1.6, branchY4 - 20);
    
    // Nhánh nhỏ trên đỉnh
    setlinestyle(SOLID_LINE, 0, 2);
    midpointLine(x, y - height * 0.85, x - trunkW * 0.8, y - height * 0.95);
    midpointLine(x, y - height * 0.85, x + trunkW * 0.7, y - height * 0.97);
    
    // Lá cây - nhiều lớp, nhiều chi tiết, gradient từ dưới lên trên
    
    int leafW = height * 0.5;
    int leafH = height * 0.35;
    int centerY = y - height * 0.75;
    
    // Lớp 1: Đen xanh sâu thẳm
    setcolor(COLOR(5, 10, 15));
    setfillstyle(SOLID_FILL, COLOR(5, 10, 15));
    fillellipse(x, centerY, leafW * 0.85, leafH * 0.8);
    
    // Lớp 2: Xanh dương đen (base color)
    setcolor(COLOR(8, 15, 25));
    setfillstyle(SOLID_FILL, COLOR(8, 15, 25));
    fillellipse(x, centerY, leafW * 0.8, leafH * 0.75);
    
    // Lớp 3: Xanh dương đậm - lớp chính
    setcolor(COLOR(12, 20, 35));
    setfillstyle(SOLID_FILL, COLOR(12, 20, 35));
    fillellipse(x, centerY, leafW * 0.72, leafH * 0.68);
    
    // Lớp 4: Xanh dương đậm hơn một chút
    setcolor(COLOR(15, 25, 40));
    setfillstyle(SOLID_FILL, COLOR(15, 25, 40));
    fillellipse(x - leafW * 0.15, centerY - leafH * 0.25, leafW * 0.4, leafH * 0.42);
    fillellipse(x + leafW * 0.12, centerY - leafH * 0.22, leafW * 0.38, leafH * 0.4);
    
    // Lớp 5: Xanh lá đậm - chi tiết thêm
    
    // Vẽ nhiều lá nhỏ xung quanh với gradient từ dưới lên trên
    
    for(int i = 0; i < 48; i++) {
        int angle = i * 7.5;
        float radiusVar = (i % 7) * 0.04;
        float radius = leafW * (0.68 + radiusVar);
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius * 0.62);
        
        // Gradient theo chiều cao: dưới tối, trên sáng dần
        if(yPos >= centerY) {
            // phía dưới - tối nhất
            setcolor(COLOR(12, 18, 28));
            setfillstyle(SOLID_FILL, COLOR(12, 18, 28));
        } else if(yPos >= centerY - leafH * 0.3) {
            // giữa dưới - đậm
            setcolor(COLOR(15, 22, 35));
            setfillstyle(SOLID_FILL, COLOR(15, 22, 35));
        } else if(yPos >= centerY - leafH * 0.6) {
            // trên giữa - đậm hơn
            setcolor(COLOR(20, 30, 38));
            setfillstyle(SOLID_FILL, COLOR(20, 30, 38));
        } else {
            // ngọn - xanh lá nhạt
            setcolor(COLOR(25, 45, 35));
            setfillstyle(SOLID_FILL, COLOR(25, 45, 35));
        }
        
        int sizeW = 18 + (i % 8) * 3;
        int sizeH = 20 + (i % 6) * 3;
        fillellipse(xPos, yPos, sizeW, sizeH);
    }
    
    // Lớp 6: Lá chi tiết nhỏ - đen xanh đậm - tạo cảm giác rậm rạp
    
    for(int i = 0; i < 56; i++) {
        int angle = i * 6.43;
        float radiusVar = (i % 9) * 0.035;
        float baseRadius = 0.72 + radiusVar;
        if(i % 4 == 0) baseRadius += 0.06;
        if(i % 7 == 0) baseRadius -= 0.04;
        
        float radius = leafW * baseRadius;
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius * 0.6);
        
        // Gradient theo chiều cao
        if(yPos >= centerY) {
            // phía dưới 
            setcolor(COLOR(14, 20, 32));
            setfillstyle(SOLID_FILL, COLOR(14, 20, 32));
        } else if(yPos >= centerY - leafH * 0.35) {
            // giữa
            setcolor(COLOR(18, 28, 40));
            setfillstyle(SOLID_FILL, COLOR(18, 28, 40));
        } else if(yPos >= centerY - leafH * 0.65) {
            // trên giữa
            setcolor(COLOR(22, 38, 35));
            setfillstyle(SOLID_FILL, COLOR(22, 38, 35));
        } else {
            // ngọn
            setcolor(COLOR(28, 50, 38));
            setfillstyle(SOLID_FILL, COLOR(28, 50, 38));
        }
        
        int sizeW = 16 + (i % 9) * 2;
        int sizeH = 18 + (i % 7) * 2;
        fillellipse(xPos, yPos, sizeW, sizeH);
    }
    
    // viền ngoài
    
    for(int i = 0; i < 72; i++) {
        int angle = i * 5 + 2.5;
        float radiusVar = (i % 15) * 0.02;
        float baseRadius = 0.82 + radiusVar;
        
        if(i % 3 == 0) baseRadius += 0.12;
        if(i % 5 == 2) baseRadius += 0.08;
        if(i % 7 == 0) baseRadius -= 0.1;
        if(i % 11 == 0) baseRadius += 0.06;
        
        float radius = leafW * baseRadius;
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius * 0.55);
        
        // Gradient viền
        if(yPos >= centerY + leafH * 0.1) {
            // cưới cùng
            setcolor(COLOR(16, 24, 30));
            setfillstyle(SOLID_FILL, COLOR(16, 24, 30));
        } else if(yPos >= centerY - leafH * 0.2) {
            // giữa dưới
            setcolor(COLOR(20, 32, 35));
            setfillstyle(SOLID_FILL, COLOR(20, 32, 35));
        } else if(yPos >= centerY - leafH * 0.5) {
            // giữa trên
            setcolor(COLOR(24, 42, 38));
            setfillstyle(SOLID_FILL, COLOR(24, 42, 38));
        } else {
            // ngọn
            setcolor(COLOR(30, 55, 42));
            setfillstyle(SOLID_FILL, COLOR(30, 55, 42));
        }
        
        int sizeW = 8 + (i % 7) * 2;
        int sizeH = 10 + (i % 5) * 2;
        fillellipse(xPos, yPos, sizeW, sizeH);
    }
    
    // Lớp 7: Lá chi tiết nhỏ nhất
    setcolor(COLOR(35, 65, 48));
    setfillstyle(SOLID_FILL, COLOR(35, 65, 48));
    fillellipse(x, centerY - leafH * 0.55, leafW * 0.28, leafH * 0.22);
    fillellipse(x - leafW * 0.12, centerY - leafH * 0.52, leafW * 0.22, leafH * 0.18);
    fillellipse(x + leafW * 0.12, centerY - leafH * 0.52, leafW * 0.22, leafH * 0.18);
    
    // Đỉnh cây - ánh trăng mạnh nhất
    setcolor(COLOR(40, 75, 52));
    setfillstyle(SOLID_FILL, COLOR(40, 75, 52));
    fillellipse(x, centerY - leafH * 0.7, leafW * 0.18, leafH * 0.15);
    
    // Chóp đỉnh - sáng nhất
    setcolor(COLOR(45, 85, 55));
    setfillstyle(SOLID_FILL, COLOR(45, 85, 55));
    fillellipse(x, centerY - height * 0.26, 20, 16);
    fillellipse(x - 10, centerY - height * 0.24, 14, 11);
    fillellipse(x + 10, centerY - height * 0.25, 13, 10);
    
    // Lá rụng
    setcolor(COLOR(18, 28, 38));
    setfillstyle(SOLID_FILL, COLOR(18, 28, 38));
    
    int fallingLeaves[][2] = {
        {-120, 70}, {-140, 40}, {-95, 15},
        {110, 65}, {130, 35}, {85, 10},
        {-70, -80}, {60, -85}, {-25, -95}, {20, -90}
    };
    
    for(int i = 0; i < 10; i++) {
        int leafX = x + fallingLeaves[i][0];
        int leafY = centerY + fallingLeaves[i][1];
        int size = 4 + (i % 3);
        
        if(i % 2 == 0) {
            setcolor(COLOR(25, 40, 35));
            setfillstyle(SOLID_FILL, COLOR(25, 40, 35));
        }
        
        fillellipse(leafX, leafY, size, size + 1);
    }
}

#endif 
