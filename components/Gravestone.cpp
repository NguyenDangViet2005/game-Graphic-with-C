#ifndef GRAVESTONE_H
#define GRAVESTONE_H

#include <graphics.h>
#include <cmath>
#include "../algorithms/index.cpp"

// Vẽ ngôi mộ pixel art với chữ RIP - phong cách tối
void drawGravestone(int x, int y, int width, int height) {
    // Tăng width lên 1.4 lần
    width = (int)(width * 1.4);
    
    // Bóng đổ
    setcolor(COLOR(10, 10, 15));
    setfillstyle(SOLID_FILL, COLOR(10, 10, 15));
    bar(x + 5, y - 3, x + width + 5, y + 2);
    
    // Viền tối bên trái (tạo chiều sâu)
    setcolor(COLOR(30, 30, 40));
    setfillstyle(SOLID_FILL, COLOR(30, 30, 40));
    bar(x - 4, y - height + 5, x, y);
    
    // Thân bia mộ chính - màu xám tối
    setcolor(COLOR(90, 90, 100));
    setfillstyle(SOLID_FILL, COLOR(90, 90, 100));
    bar(x, y - height, x + width, y);
    
    // Viền đen đậm
    setcolor(COLOR(25, 25, 35));
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x, y - height, x + width, y);
    setlinestyle(SOLID_LINE, 0, 1);
    
    // Đỉnh tròn pixel art
    setcolor(COLOR(90, 90, 100));
    setfillstyle(SOLID_FILL, COLOR(90, 90, 100));
    
    int centerX = x + width / 2;
    int topY = y - height;
    int radius = width / 2;
    
    for (int i = -radius; i <= radius; i++) {
        int h = (int)sqrt(radius * radius - i * i);
        bar(centerX + i, topY - h, centerX + i + 1, topY);
    }
    
    // Viền đỉnh
    setcolor(COLOR(25, 25, 35));
    setlinestyle(SOLID_LINE, 0, 2);
    arc(centerX, topY, 0, 180, radius);
    setlinestyle(SOLID_LINE, 0, 1);
    
    // Phần sáng nhẹ bên phải
    setcolor(COLOR(105, 105, 115));
    setfillstyle(SOLID_FILL, COLOR(105, 105, 115));
    bar(x + width - 10, y - height + 12, x + width - 3, y - 12);
    
    // Vết nứt
    setcolor(COLOR(60, 60, 70));
    // Bresenham line
    bresenhamLine(x + 8, y - height / 3, x + 12, y - height / 4);
    bresenhamLine(x + width - 8, y - height / 2, x + width - 5, y - height / 3);
    bresenhamLine(x + width / 2 - 5, y - height + 18, x + width / 2 - 2, y - 15);
    
    // Chấm nhỏ (vết thời gian)
    setcolor(COLOR(70, 70, 80));
    putpixel(x + 10, y - height + 20, COLOR(70, 70, 80));
    putpixel(x + width - 12, y - height / 2 + 8, COLOR(70, 70, 80));
    putpixel(x + 15, y - 18, COLOR(70, 70, 80));
    putpixel(x + width - 18, y - height + 25, COLOR(70, 70, 80));
    
    // Vẽ chữ "RIP" pixel art - màu tím tối
    int textStartX = x + width / 2 - 15;
    int textStartY = y - height / 2 - 8;
    
    setcolor(COLOR(60, 40, 90));
    setfillstyle(SOLID_FILL, COLOR(60, 40, 90));
    
    // Chữ R
    bar(textStartX, textStartY, textStartX + 3, textStartY + 14);
    bar(textStartX, textStartY, textStartX + 8, textStartY + 3);
    bar(textStartX + 8, textStartY, textStartX + 10, textStartY + 7);
    bar(textStartX, textStartY + 6, textStartX + 8, textStartY + 9);
    bar(textStartX + 5, textStartY + 9, textStartX + 10, textStartY + 14);
    
    // Chữ I
    bar(textStartX + 13, textStartY, textStartX + 16, textStartY + 14);
    
    // Chữ P
    bar(textStartX + 19, textStartY, textStartX + 22, textStartY + 14);
    bar(textStartX + 19, textStartY, textStartX + 27, textStartY + 3);
    bar(textStartX + 27, textStartY, textStartX + 29, textStartY + 7);
    bar(textStartX + 19, textStartY + 6, textStartX + 27, textStartY + 9);
    
    // Viền chữ tối hơn
    setcolor(COLOR(40, 25, 70));
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(textStartX - 2, textStartY - 2, textStartX + 30, textStartY + 15);
    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
