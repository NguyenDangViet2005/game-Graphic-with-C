#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <graphics.h>
#include "../configs/Config.cpp"
#include "Cloud.cpp"

// Vẽ background (trời, đám mây, đất, cỏ)
void drawBackground() {
    //vẽ nền trời Gradient từ đen xanh đậm đến xanh dương nhạt
    for(int i = 0; i < GROUND_Y; i++) {
        float ratio = (float)i / GROUND_Y;
        int r = 3 + (int)(ratio * 12);   
        int g = 5 + (int)(ratio * 15); 
        int b = 15 + (int)(ratio * 25); 
        setcolor(COLOR(r, g, b));
        line(0, i, SCREEN_WIDTH, i);
    }
    
    // Vẽ mặt trăng ở góc trên bên phải
    int moonX = SCREEN_WIDTH - 150;
    int moonY = 80;
    int moonRadius = 50;
    
    // Ánh sáng mặt trăng
    setcolor(COLOR(40, 45, 65));
    setfillstyle(SOLID_FILL, COLOR(40, 45, 65));
    fillellipse(moonX, moonY, moonRadius + 15, moonRadius + 15);
    
    setcolor(COLOR(60, 65, 85));
    setfillstyle(SOLID_FILL, COLOR(60, 65, 85));
    fillellipse(moonX, moonY, moonRadius + 8, moonRadius + 8);
    
    // Mặt trăng chính - màu trắng xám nhạt
    setcolor(COLOR(220, 225, 230));
    setfillstyle(SOLID_FILL, COLOR(220, 225, 230));
    fillellipse(moonX, moonY, moonRadius, moonRadius);
    
    // Chi tiết trên mặt trăng
    setcolor(COLOR(190, 195, 200));
    setfillstyle(SOLID_FILL, COLOR(190, 195, 200));
    fillellipse(moonX - 15, moonY - 10, 12, 10);
    fillellipse(moonX + 18, moonY + 5, 10, 8);
    fillellipse(moonX + 5, moonY + 18, 8, 7);
    fillellipse(moonX - 10, moonY + 12, 6, 5);
    
    // Đám mây
    drawCloud(200, 100, 40);
    drawCloud(500, 150, 35);
    drawCloud(850, 80, 45);
    drawCloud(1050, 120, 38);
    
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
            line(i + 10, GROUND_Y + 5, i + 10, GROUND_Y + h - 3);
            line(i + 25, GROUND_Y + 8, i + 25, GROUND_Y + h - 2);
        }
    }
    
    // Chi tiết bụi cỏ nhỏ xíu
    for(int i = 0; i < 50; i++) {
        int gx = 20 + i * 24;
        int gy = GROUND_Y + 2 + (i % 6);
        
        if(i % 3 == 0) {
            setcolor(COLOR(22, 32, 36));
            line(gx, gy, gx, gy - 3);
            line(gx + 1, gy, gx + 1, gy - 4);
        }
    }
    
    // Border mặt đất
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);
    line(0, GROUND_Y, SCREEN_WIDTH, GROUND_Y);
}

#endif 
