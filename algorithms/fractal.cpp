#ifndef FRACTAL_H
#define FRACTAL_H

#include <graphics.h>
#include <cmath>

// Thuật toán Fractal Tree (Cây phân nhánh đệ quy) - phiên bản Dark Forest
void drawDarkFractalTree(int x, int y, double angle, int depth, int length) {
    if (depth == 0) return;
    
    // Tính điểm cuối của nhánh
    int x2 = x + (int)(length * cos(angle * 3.14159 / 180.0));
    int y2 = y - (int)(length * sin(angle * 3.14159 / 180.0));
    
    // Màu sắc tối hơn nhiều, khô cằn
    int darkness = 10 + (depth * 4);
    if (darkness > 35) darkness = 35;
    
    setcolor(COLOR(darkness, darkness - 3, darkness - 5));
    
    // Độ dày nhánh giảm dần
    int thickness = depth > 4 ? 2 : 1;
    setlinestyle(SOLID_LINE, 0, thickness);
    
    // Vẽ nhánh
    line(x, y, x2, y2);
    
    // Thêm ngẫu nhiên cho tự nhiên hơn
    int randomLeft = 20 + (depth % 10);
    int randomRight = 20 + ((depth + 3) % 10);
    
    // Đệ quy vẽ 2-3 nhánh con
    double angleLeft = angle + randomLeft;
    double angleRight = angle - randomRight;
    int newLength = (int)(length * 0.65);
    
    drawDarkFractalTree(x2, y2, angleLeft, depth - 1, newLength);
    drawDarkFractalTree(x2, y2, angleRight, depth - 1, newLength);
    
    // Thêm nhánh thứ 3 cho cây già
    if (depth > 5 && depth % 2 == 0) {
        drawDarkFractalTree(x2, y2, angle, depth - 2, newLength - 5);
    }
    
    setlinestyle(SOLID_LINE, 0, 1);
}

// Thuật toán Koch Snowflake (Bông tuyết Koch)
void drawKochLine(int x1, int y1, int x2, int y2, int depth) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
        return;
    }
    
    // Chia đoạn thẳng thành 3 phần
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    int x3 = x1 + dx / 3;
    int y3 = y1 + dy / 3;
    
    int x5 = x1 + 2 * dx / 3;
    int y5 = y1 + 2 * dy / 3;
    
    // Tính điểm đỉnh tam giác đều
    double angle = atan2(dy, dx);
    int len = (int)sqrt(dx * dx + dy * dy) / 3;
    int x4 = x3 + (int)(len * cos(angle + 3.14159 / 3.0));
    int y4 = y3 + (int)(len * sin(angle + 3.14159 / 3.0));
    
    // Đệ quy vẽ 4 đoạn
    drawKochLine(x1, y1, x3, y3, depth - 1);
    drawKochLine(x3, y3, x4, y4, depth - 1);
    drawKochLine(x4, y4, x5, y5, depth - 1);
    drawKochLine(x5, y5, x2, y2, depth - 1);
}

// Vẽ mạng nhện bằng Koch Curve
void drawSpiderWeb(int centerX, int centerY, int radius) {
    setcolor(COLOR(60, 60, 70));
    
    // Vẽ 8 tia từ tâm
    for (int i = 0; i < 8; i++) {
        double angle = i * 45 * 3.14159 / 180.0;
        int x = centerX + (int)(radius * cos(angle));
        int y = centerY + (int)(radius * sin(angle));
        
        // Dùng Koch line cho tia
        drawKochLine(centerX, centerY, x, y, 2);
    }
    
    // Vẽ vòng tròn Koch
    int points = 6;
    for (int r = radius / 3; r <= radius; r += radius / 3) {
        for (int i = 0; i < points; i++) {
            double angle1 = i * (360.0 / points) * 3.14159 / 180.0;
            double angle2 = (i + 1) * (360.0 / points) * 3.14159 / 180.0;
            
            int x1 = centerX + (int)(r * cos(angle1));
            int y1 = centerY + (int)(r * sin(angle1));
            int x2 = centerX + (int)(r * cos(angle2));
            int y2 = centerY + (int)(r * sin(angle2));
            
            drawKochLine(x1, y1, x2, y2, 1);
        }
    }
}

// Vẽ cỏ gai bằng Koch Curve
void drawThornyGrass(int x, int y, int height) {
    setcolor(COLOR(30, 50, 35));
    
    // 3 cọng cỏ gai
    for (int i = 0; i < 3; i++) {
        int offsetX = x + (i - 1) * 8;
        int topX = offsetX + (i % 2 == 0 ? 5 : -5);
        int topY = y - height - (i * 3);
        
        drawKochLine(offsetX, y, topX, topY, 2);
    }
}


// Thuật toán Dragon Curve (Đường cong Rồng) - cho rễ cây
void drawDragonCurve(int x1, int y1, int x2, int y2, int depth, int direction) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
        return;
    }
    
    // Tính điểm giữa và xoay 90 độ
    int dx = x2 - x1;
    int dy = y2 - y1;
    
    int xm = (x1 + x2) / 2 + direction * (dy) / 2;
    int ym = (y1 + y2) / 2 - direction * (dx) / 2;
    
    // Đệ quy vẽ 2 nửa
    drawDragonCurve(x1, y1, xm, ym, depth - 1, 1);
    drawDragonCurve(xm, ym, x2, y2, depth - 1, -1);
}

// Thuật toán Levy C-Curve (Đường cong C)
void drawLevyCCurve(int x1, int y1, int x2, int y2, int depth) {
    if (depth == 0) {
        line(x1, y1, x2, y2);
        return;
    }

    // Tính điểm giữa xoay 90 độ (Levy C-curve)
    int xm = (x1 + x2) / 2 + (y1 - y2) / 2;
    int ym = (y1 + y2) / 2 + (x2 - x1) / 2;

    drawLevyCCurve(x1, y1, xm, ym, depth - 1);
    drawLevyCCurve(xm, ym, x2, y2, depth - 1);
}



// Cụm rễ trang trí bằng Dragon curve (gần mặt đất)
void drawDragonRootOrnament(int x, int y, int scale) {
    int dx = 70 * scale;
    int dy = 26 * scale;

    setcolor(COLOR(22, 28, 36));
    drawDragonCurve(x, y, x + dx, y - dy, 8, 1);

    setcolor(COLOR(18, 22, 30));
    drawDragonCurve(x + dx / 3, y + 4 * scale, x + dx + 14 * scale, y - 10 * scale, 7, -1);
}

#endif
