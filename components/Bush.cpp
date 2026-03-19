#ifndef BUSH_H
#define BUSH_H

#include <graphics.h>
#include <math.h>

// Vẽ bụi cỏ chi tiết với gradient tối
void drawDarkBush(int x, int y, int radius) {
    radius = radius * 0.7;
    int centerY = y - radius * 0.3;
    
    // lớp nền bụi cỏ - màu tối nhất
    setcolor(COLOR(10, 15, 22));
    setfillstyle(SOLID_FILL, COLOR(10, 15, 22));
    fillellipse(x, centerY, radius * 0.9, radius * 0.7);
    fillellipse(x - radius * 0.5, centerY + radius * 0.2, radius * 0.6, radius * 0.5);
    fillellipse(x + radius * 0.5, centerY + radius * 0.2, radius * 0.6, radius * 0.5);
    
    // Layer 1: Phần dưới - tối nhất
    setcolor(COLOR(12, 18, 28));
    setfillstyle(SOLID_FILL, COLOR(12, 18, 28));
    
    for(int i = 0; i < 24; i++) {
        int angle = i * 15;
        float radius1 = radius * (0.65 + (i % 5) * 0.03);
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius1);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius1 * 0.65);

        if(yPos >= centerY - radius * 0.2) {
            int sizeW = 10 + (i % 4) * 2;
            int sizeH = 12 + (i % 3) * 2;
            fillellipse(xPos, yPos, sizeW, sizeH);
        }
    }

    // Layer 2: Phần giữa - tối vừa
    setcolor(COLOR(16, 24, 35));
    setfillstyle(SOLID_FILL, COLOR(16, 24, 35));
    
    for(int i = 0; i < 28; i++) {
        int angle = i * 12.86;
        float radius2 = radius * (0.7 + (i % 6) * 0.025);
        
        // Tạo độ nhấp nhô
        if(i % 3 == 0) radius2 += radius * 0.05;
        if(i % 5 == 0) radius2 -= radius * 0.03;
        
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius2);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius2 * 0.6);
        
        // Vẽ phần giữa
        if(yPos >= centerY - radius * 0.5 && yPos < centerY + radius * 0.1) {
            int sizeW = 9 + (i % 5) * 2;
            int sizeH = 11 + (i % 4) * 2;
            fillellipse(xPos, yPos, sizeW, sizeH);
        }
    }
    
    // Layer 3: Phần trên - xanh hơn
    setcolor(COLOR(20, 32, 38));
    setfillstyle(SOLID_FILL, COLOR(20, 32, 38));
    
    for(int i = 0; i < 32; i++) {
        int angle = i * 11.25;
        float radius3 = radius * (0.75 + (i % 7) * 0.02);
        
        // Tạo viền lởm chởm
        if(i % 4 == 0) radius3 += radius * 0.08;
        if(i % 6 == 2) radius3 += radius * 0.05;
        if(i % 7 == 0) radius3 -= radius * 0.04;
        
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius3);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius3 * 0.55);
        
        // Vẽ phần trên
        if(yPos < centerY - radius * 0.2) {
            int sizeW = 8 + (i % 6) * 2;
            int sizeH = 10 + (i % 5) * 2;
            fillellipse(xPos, yPos, sizeW, sizeH);
        }
    }

    // Layer 4: Đỉnh - xanh lá nhạt
    setcolor(COLOR(25, 42, 35));
    setfillstyle(SOLID_FILL, COLOR(25, 42, 35));
    
    for(int i = 0; i < 20; i++) {
        int angle = i * 18;
        float radius4 = radius * (0.8 + (i % 8) * 0.015);
        
        if(i % 3 == 0) radius4 += radius * 0.1;
        if(i % 5 == 1) radius4 += radius * 0.06;
        
        int xPos = x + (int)(cos(angle * 3.14159 / 180) * radius4);
        int yPos = centerY + (int)(sin(angle * 3.14159 / 180) * radius4 * 0.5);
        
        // trên cùng
        if(yPos < centerY - radius * 0.5) {
            int sizeW = 7 + (i % 4) * 2;
            int sizeH = 8 + (i % 3) * 2;
            fillellipse(xPos, yPos, sizeW, sizeH);
        }
    }
    
    // Đỉnh sáng nhất
    setcolor(COLOR(30, 50, 38));
    setfillstyle(SOLID_FILL, COLOR(30, 50, 38));
    fillellipse(x, centerY - radius * 0.6, radius * 0.25, radius * 0.2);
    fillellipse(x - radius * 0.15, centerY - radius * 0.55, radius * 0.18, radius * 0.15);
    fillellipse(x + radius * 0.15, centerY - radius * 0.55, radius * 0.18, radius * 0.15);
    
    // Highlight 
    setcolor(COLOR(35, 60, 42));
    setfillstyle(SOLID_FILL, COLOR(35, 60, 42));
    fillellipse(x, centerY - radius * 0.7, radius * 0.15, radius * 0.12);
}

#endif
