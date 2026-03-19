#ifndef CLOUD_H
#define CLOUD_H

#include <graphics.h>

// Vẽ đám mây
void drawCloud(int x, int y, int size) {
    // Lớp đám mây tối nhất
    setcolor(COLOR(60, 65, 75));
    setfillstyle(SOLID_FILL, COLOR(60, 65, 75));
    fillellipse(x, y + size*0.1, size*1.05, size*0.65);
    fillellipse(x - size*0.75, y + size*0.35, size*0.85, size*0.55);
    fillellipse(x + size*0.75, y + size*0.25, size*0.95, size*0.65);
    
    // Lớp đám mây chính
    setcolor(COLOR(70, 75, 85));
    setfillstyle(SOLID_FILL, COLOR(70, 75, 85));
    
    fillellipse(x, y, size, size*0.6);
    fillellipse(x - size*0.7, y + size*0.3, size*0.8, size*0.5);
    fillellipse(x + size*0.7, y + size*0.2, size*0.9, size*0.6);
    fillellipse(x - size*0.3, y - size*0.4, size*0.7, size*0.5);
    fillellipse(x + size*0.4, y - size*0.3, size*0.6, size*0.4);
    
    // Thêm chi tiết bồng bềnh
    fillellipse(x - size*0.5, y + size*0.1, size*0.5, size*0.35);
    fillellipse(x + size*0.5, y, size*0.55, size*0.4);
    fillellipse(x, y - size*0.2, size*0.6, size*0.38);
    fillellipse(x - size*0.15, y + size*0.15, size*0.45, size*0.3);
    fillellipse(x + size*0.2, y + size*0.05, size*0.5, size*0.32);
    
    // Lớp sáng (ánh trăng chiếu vào phần trên)
    setcolor(COLOR(85, 90, 100));
    setfillstyle(SOLID_FILL, COLOR(85, 90, 100));
    fillellipse(x - size*0.2, y - size*0.35, size*0.5, size*0.3);
    fillellipse(x + size*0.25, y - size*0.25, size*0.4, size*0.25);
    fillellipse(x + size*0.55, y - size*0.1, size*0.35, size*0.22);
    
    // Vẽ outline
    setcolor(COLOR(40, 45, 55));
    setlinestyle(SOLID_LINE, 0, 1);
    // Viền trái
    ellipse(x - size*0.7, y + size*0.3, 120, 240, size*0.8, size*0.5);
    // Viền phải
    ellipse(x + size*0.7, y + size*0.2, 300, 60, size*0.9, size*0.6);
    // Viền trên phải
    ellipse(x + size*0.4, y - size*0.3, 20, 160, size*0.6, size*0.4);
    // Viền trên trái
    ellipse(x - size*0.3, y - size*0.4, 30, 150, size*0.7, size*0.5);
}

#endif
