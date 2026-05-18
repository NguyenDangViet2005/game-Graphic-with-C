#ifndef BRESENHAM_H
#define BRESENHAM_H

#include <graphics.h>
#include <cmath>

// Thuật toán Bresenham vẽ đường thẳng
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int err = dx - dy;
    
    int x = x1, y = y1;
    
    while (true) {
        putpixel(x, y, getcolor());
        
        if (x == x2 && y == y2) break;
        
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x += sx;
        }
        if (e2 < dx) {
            err += dx;
            y += sy;
        }
    }
}

// Thuật toán Bresenham vẽ đường tròn
void bresenhamCircle(int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;

    // Vẽ 8 điểm đối xứng
    auto plotCirclePoints = [&](int cx, int cy, int x, int y) {
        putpixel(cx + x, cy + y, getcolor());
        putpixel(cx - x, cy + y, getcolor());
        putpixel(cx + x, cy - y, getcolor());
        putpixel(cx - x, cy - y, getcolor());
        putpixel(cx + y, cy + x, getcolor());
        putpixel(cx - y, cy + x, getcolor());
        putpixel(cx + y, cy - x, getcolor());
        putpixel(cx - y, cy - x, getcolor());
    };

    while (y >= x) {
        plotCirclePoints(centerX, centerY, x, y);
        x++;
        if (d > 0) {
            y--;
            d += 4 * (x - y) + 10;
        } else {
            d += 4 * x + 6;
        }
    }
}

// Thuật toán Bresenham vẽ đường thẳng với độ dày
void bresenhamThickLine(int x1, int y1, int x2, int y2, int thickness) {
    if (thickness <= 1) {
        bresenhamLine(x1, y1, x2, y2);
        return;
    }
    
    // Tính vector vuông góc với đường thẳng
    int dx = x2 - x1;
    int dy = y2 - y1;
    double length = sqrt(dx * dx + dy * dy);
    
    if (length == 0) return;
    
    // Vector đơn vị vuông góc
    double perpX = -dy / length;
    double perpY = dx / length;
    
    // Vẽ nhiều đường song song
    int halfThick = thickness / 2;
    for (int i = -halfThick; i <= halfThick; i++) {
        int offsetX = (int)(i * perpX);
        int offsetY = (int)(i * perpY);
        bresenhamLine(x1 + offsetX, y1 + offsetY, x2 + offsetX, y2 + offsetY);
    }
}

#endif