#ifndef MIDPOINT_H
#define MIDPOINT_H

#include <graphics.h>
#include <cstdlib>

// Thuật toán Midpoint vẽ đường thẳng (tất cả các octant)
void midpointLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int sx = (dx >= 0) ? 1 : -1;
    int sy = (dy >= 0) ? 1 : -1;
    dx = abs(dx);
    dy = abs(dy);

    int x = x1;
    int y = y1;

    putpixel(x, y, getcolor());

    if (dx >= dy) {
        int d = 2 * dy - dx;
        int incrE = 2 * dy;
        int incrNE = 2 * (dy - dx);

        for (int i = 0; i < dx; i++) {
            x += sx;
            if (d > 0) {
                y += sy;
                d += incrNE;
            } else {
                d += incrE;
            }
            putpixel(x, y, getcolor());
        }
    } else {
        int d = 2 * dx - dy;
        int incrE = 2 * dx;
        int incrNE = 2 * (dx - dy);

        for (int i = 0; i < dy; i++) {
            y += sy;
            if (d > 0) {
                x += sx;
                d += incrNE;
            } else {
                d += incrE;
            }
            putpixel(x, y, getcolor());
        }
    }
}

// Thuật toán Midpoint vẽ đường tròn
void midpointCircle(int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    int incrE = 3;                // 2*x + 3, bat dau khi x=0
    int incrSE = -2 * radius + 5; // 2*(x - y) + 5, bat dau khi x=0, y=radius
    
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
    
    plotCirclePoints(centerX, centerY, x, y);
    
    while (x < y) {
        x++;
        if (d < 0) {
            d += incrE;
            incrSE += 2;
        } else {
            y--;
            d += incrSE;
            incrSE += 4;
        }
        incrE += 2;
        plotCirclePoints(centerX, centerY, x, y);
    }
}

// Thuật toán Midpoint vẽ ellipse
void midpointEllipse(int centerX, int centerY, int radiusX, int radiusY) {
    int x = 0;
    int y = radiusY;
    
    // Vẽ 4 điểm đối xứng
    auto plotEllipsePoints = [&](int cx, int cy, int x, int y) {
        putpixel(cx + x, cy + y, getcolor());
        putpixel(cx - x, cy + y, getcolor());
        putpixel(cx + x, cy - y, getcolor());
        putpixel(cx - x, cy - y, getcolor());
    };
    
    // Vùng 1: dy/dx < -1
    int rx2 = radiusX * radiusX;
    int ry2 = radiusY * radiusY;
    int twoRx2 = 2 * rx2;
    int twoRy2 = 2 * ry2;
    
    int p1 = ry2 - rx2 * radiusY + (rx2 / 4);
    int dx = 0;
    int dy = twoRx2 * y;
    
    plotEllipsePoints(centerX, centerY, x, y);
    
    // Vùng 1
    while (dx < dy) {
        x++;
        dx = twoRy2 * x;
        
        if (p1 < 0) {
            p1 += dx + ry2;
        } else {
            y--;
            dy = twoRx2 * y;
            p1 += dx - dy + ry2;
        }
        plotEllipsePoints(centerX, centerY, x, y);
    }
    
    // Vùng 2: dy/dx >= -1
    int p2 = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    
    while (y > 0) {
        y--;
        dy = twoRx2 * y;
        
        if (p2 > 0) {
            p2 += rx2 - dy;
        } else {
            x++;
            dx = twoRy2 * x;
            p2 += dx - dy + rx2;
        }
        plotEllipsePoints(centerX, centerY, x, y);
    }
}

// Vẽ đường tròn với fill
void midpointFilledCircle(int centerX, int centerY, int radius) {
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    
    // Vẽ đường ngang để fill
    auto drawHorizontalLine = [&](int cx, int cy, int x1, int x2, int y) {
        line(cx + x1, cy + y, cx + x2, cy + y);
    };
    
    drawHorizontalLine(centerX, centerY, -x, x, y);
    drawHorizontalLine(centerX, centerY, -x, x, -y);
    
    while (x < y) {
        x++;
        if (d < 0) {
            d += 2 * x + 1;
        } else {
            y--;
            d += 2 * (x - y) + 1;
        }
        
        drawHorizontalLine(centerX, centerY, -x, x, y);
        drawHorizontalLine(centerX, centerY, -x, x, -y);
        drawHorizontalLine(centerX, centerY, -y, y, x);
        drawHorizontalLine(centerX, centerY, -y, y, -x);
    }
}

// Vẽ ellipse với fill
void midpointFilledEllipse(int centerX, int centerY, int radiusX, int radiusY) {
    int x = 0;
    int y = radiusY;
    
    // Vẽ đường ngang để fill
    auto drawHorizontalLine = [&](int cx, int cy, int x1, int x2, int y) {
        line(cx + x1, cy + y, cx + x2, cy + y);
    };
    
    // Vùng 1
    int rx2 = radiusX * radiusX;
    int ry2 = radiusY * radiusY;
    int twoRx2 = 2 * rx2;
    int twoRy2 = 2 * ry2;
    
    int p1 = ry2 - rx2 * radiusY + (rx2 / 4);
    int dx = 0;
    int dy = twoRx2 * y;
    
    drawHorizontalLine(centerX, centerY, -x, x, y);
    drawHorizontalLine(centerX, centerY, -x, x, -y);
    
    while (dx < dy) {
        x++;
        dx = twoRy2 * x;
        
        if (p1 < 0) {
            p1 += dx + ry2;
        } else {
            y--;
            dy = twoRx2 * y;
            p1 += dx - dy + ry2;
        }
        
        drawHorizontalLine(centerX, centerY, -x, x, y);
        drawHorizontalLine(centerX, centerY, -x, x, -y);
    }
    
    // Vùng 2
    int p2 = ry2 * (x + 0.5) * (x + 0.5) + rx2 * (y - 1) * (y - 1) - rx2 * ry2;
    
    while (y > 0) {
        y--;
        dy = twoRx2 * y;
        
        if (p2 > 0) {
            p2 += rx2 - dy;
        } else {
            x++;
            dx = twoRy2 * x;
            p2 += dx - dy + rx2;
        }
        
        drawHorizontalLine(centerX, centerY, -x, x, y);
        drawHorizontalLine(centerX, centerY, -x, x, -y);
    }
}

#endif