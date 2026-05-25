#ifndef MENU_BACKGROUND_H
#define MENU_BACKGROUND_H

#include <graphics.h>
#include "../configs/Config.cpp"
#include "Cloud.cpp"
#include "Tree.cpp"
#include "Bush.cpp"
#include "../algorithms/index.cpp"
#include "../algorithms/fractal.cpp"
#include "SummonSigil.cpp"
void drawExplorer(int x, int y, float scale, float armAngle, float headAngle, int weaponType, float slashProgress);

// Vẽ background chung cho Menu, Hướng dẫn, Bảng điểm
void drawMenuBackground() {
    // nền trời Gradient từ đen xanh đậm đến xanh dương nhạt
    for(int i = 0; i < SCREEN_HEIGHT; i++) {
        float ratio = (float)i / SCREEN_HEIGHT;
        int r = 3 + (int)(ratio * 12); 
        int g = 5 + (int)(ratio * 15);   
        int b = 15 + (int)(ratio * 25); 
        setcolor(COLOR(r, g, b));
        // Bresenham line
        bresenhamLine(0, i, SCREEN_WIDTH, i);
    }
    
    // mặt trăng lớn 
    int moonX = 280;
    int moonY = SCREEN_HEIGHT - 220;
    int moonRadius = 160;
    
    // Ánh sáng mặt trăng
    setcolor(COLOR(35, 40, 60));
    setfillstyle(SOLID_FILL, COLOR(35, 40, 60));
    fillellipse(moonX, moonY, moonRadius + 18, moonRadius + 18);
    
    setcolor(COLOR(50, 55, 75));
    setfillstyle(SOLID_FILL, COLOR(50, 55, 75));
    fillellipse(moonX, moonY, moonRadius + 10, moonRadius + 10);
    
    // Mặt trăng chính
    setcolor(COLOR(215, 220, 225));
    setfillstyle(SOLID_FILL, COLOR(215, 220, 225));
    fillellipse(moonX, moonY, moonRadius, moonRadius);
    
    // Chi tiết mặt trăng 
    setcolor(COLOR(185, 190, 195));
    setfillstyle(SOLID_FILL, COLOR(185, 190, 195));
    fillellipse(moonX - 18, moonY - 12, 13, 11);
    fillellipse(moonX + 20, moonY + 8, 11, 9);
    fillellipse(moonX + 8, moonY + 20, 9, 8);
    fillellipse(moonX - 12, moonY + 15, 7, 6);
    fillellipse(moonX - 5, moonY - 25, 6, 5);
    
    // dám mây
    drawCloud(180, 120, 45);
    drawCloud(400, 90, 38);
    drawCloud(650, 140, 42);
    drawCloud(900, 100, 40);
    drawCloud(1050, 130, 36);

    // Bo chi tiet trang tri tren may
    
    // rừng cây phía sau
    // Cây background
    drawFarLayer(100);
    
    // chèn nhiều cây
    drawDarkTree(160, SCREEN_HEIGHT - 35, 330);
    drawDarkTree(380, SCREEN_HEIGHT - 60, 280);
    drawDarkTree(520, SCREEN_HEIGHT - 10, 360);
    drawDarkTree(650, SCREEN_HEIGHT - 45, 310);
    drawDarkTree(760, SCREEN_HEIGHT - 20, 370);
    drawDarkTree(900, SCREEN_HEIGHT - 55, 300);
    drawDarkTree(1050, SCREEN_HEIGHT - 15, 390);
    
    // Cây bên trái - lớn và đầy
    int leftTreeX = 60;
    int leftTreeY = SCREEN_HEIGHT;
    drawDarkTree(leftTreeX, leftTreeY, 450);
    
    // Cây phụ bên trái 
    drawDarkTree(leftTreeX - 110, leftTreeY, 380);
    
    // Cây bên phải - lớn và đầy
    int rightTreeX = SCREEN_WIDTH - 80;
    int rightTreeY = SCREEN_HEIGHT;
    drawDarkTree(rightTreeX, rightTreeY, 460);
    
    // Cây phụ bên phải
    drawDarkTree(rightTreeX - 140, rightTreeY, 390);
    drawDarkTree(rightTreeX + 110, rightTreeY, 370);
    
    // Bụi cỏ bên trái
    for(int i = 0; i < 5; i++) {
        int bx = 30 + i * 50;
        int by = SCREEN_HEIGHT - 20;
        int br = 38 + (i % 3) * 6;
        drawDarkBush(bx, by, br);
    }
    
    // Bụi cỏ bên phải
    for(int i = 0; i < 5; i++) {
        int bx = SCREEN_WIDTH - 280 + i * 55;
        int by = SCREEN_HEIGHT - 20;
        int br = 40 + (i % 3) * 8;
        drawDarkBush(bx, by, br);
    }
    
    // Bụi cỏ giữa (ít hơn để không che menu)
    drawDarkBush(480, SCREEN_HEIGHT - 15, 35);
    drawDarkBush(580, SCREEN_HEIGHT - 18, 32);
    drawDarkBush(780, SCREEN_HEIGHT - 15, 38);
    drawDarkBush(880, SCREEN_HEIGHT - 20, 34);
    
    // === VIỀN ĐẤT DƯỚI ===
    setcolor(COLOR(10, 14, 20));
    setfillstyle(SOLID_FILL, COLOR(10, 14, 20));
    bar(0, SCREEN_HEIGHT - 40, SCREEN_WIDTH, SCREEN_HEIGHT);

    // Re dragon trang tri sat dat
    drawDragonRootOrnament(180, SCREEN_HEIGHT - 10, 1);
    drawDragonRootOrnament(920, SCREEN_HEIGHT - 8, 1);
    
    //  đất
    for(int i = 0; i < SCREEN_WIDTH; i += 60) {
        setcolor(COLOR(8, 12, 18));
        bresenhamLine(i + 20, SCREEN_HEIGHT - 35, i + 20, SCREEN_HEIGHT);
        setcolor(COLOR(12, 16, 22));
        bresenhamLine(i + 40, SCREEN_HEIGHT - 30, i + 40, SCREEN_HEIGHT);
    }
    
    // Cong trieu hoi lon (dat sau nhan vat, khong de len menu item)
    drawSummonSigil(280, SCREEN_HEIGHT - 140, 2.6f);

    // nhân vật 
    drawExplorer(280, SCREEN_HEIGHT - 25, 2.5f, 0.0f, 0.0f, 0, 0.0f);
}

#endif
