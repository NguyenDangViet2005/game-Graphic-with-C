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
void drawKochSnowflake(int centerX, int centerY, int size, int depth) {
    // 3 đỉnh của tam giác đều
    int x1 = centerX;
    int y1 = centerY - size;
    
    int x2 = centerX - (int)(size * 0.866);
    int y2 = centerY + size / 2;
    
    int x3 = centerX + (int)(size * 0.866);
    int y3 = centerY + size / 2;
    
    // Vẽ 3 cạnh với Koch curve
    drawKochLine(x1, y1, x2, y2, depth);
    drawKochLine(x2, y2, x3, y3, depth);
    drawKochLine(x3, y3, x1, y1, depth);
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

// Vẽ rễ cây bằng Dragon Curve - phong cách Dark
void drawDarkRoots(int x, int y, int width) {
    setcolor(COLOR(35, 25, 20));
    setlinestyle(SOLID_LINE, 0, 2);
    
    // Rễ trái
    drawDragonCurve(x - 10, y, x - width, y + 25, 6, 1);
    
    // Rễ phải
    drawDragonCurve(x + 10, y, x + width, y + 25, 6, -1);
    
    // Rễ giữa
    setcolor(COLOR(30, 20, 15));
    drawDragonCurve(x, y, x + 5, y + 30, 5, 1);
    
    setlinestyle(SOLID_LINE, 0, 1);
}

// Sierpinski Triangle (Tam giác Sierpinski)
void drawSierpinskiTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int depth) {
    if (depth == 0) {
        // Vẽ tam giác đầy
        int points[] = {x1, y1, x2, y2, x3, y3};
        drawpoly(3, points);
        return;
    }
    
    // Tính điểm giữa các cạnh
    int x12 = (x1 + x2) / 2;
    int y12 = (y1 + y2) / 2;
    
    int x23 = (x2 + x3) / 2;
    int y23 = (y2 + y3) / 2;
    
    int x31 = (x3 + x1) / 2;
    int y31 = (y3 + y1) / 2;
    
    // Đệ quy vẽ 3 tam giác con
    drawSierpinskiTriangle(x1, y1, x12, y12, x31, y31, depth - 1);
    drawSierpinskiTriangle(x12, y12, x2, y2, x23, y23, depth - 1);
    drawSierpinskiTriangle(x31, y31, x23, y23, x3, y3, depth - 1);
}


// Mandelbrot Set (Tập Mandelbrot - đơn giản hóa)
void drawMandelbrotPixel(int screenX, int screenY, int width, int height, 
                         double xMin, double xMax, double yMin, double yMax) {
    // Chuyển tọa độ màn hình sang tọa độ phức
    double x0 = xMin + (xMax - xMin) * screenX / width;
    double y0 = yMin + (yMax - yMin) * screenY / height;
    
    double x = 0, y = 0;
    int iteration = 0;
    int maxIteration = 50;
    
    // Kiểm tra điểm có thuộc tập Mandelbrot không
    while (x*x + y*y <= 4 && iteration < maxIteration) {
        double xtemp = x*x - y*y + x0;
        y = 2*x*y + y0;
        x = xtemp;
        iteration++;
    }
    
    // Tô màu dựa trên số lần lặp
    if (iteration == maxIteration) {
        putpixel(screenX, screenY, BLACK);
    } else {
        int color = (iteration * 255) / maxIteration;
        putpixel(screenX, screenY, COLOR(color, color / 2, 255 - color));
    }
}

// Vẽ Mandelbrot Set trong vùng cho trước
void drawMandelbrotSet(int x, int y, int width, int height) {
    double xMin = -2.5, xMax = 1.0;
    double yMin = -1.0, yMax = 1.0;
    
    for (int i = 0; i < width; i += 2) { // Bỏ qua pixel để nhanh hơn
        for (int j = 0; j < height; j += 2) {
            drawMandelbrotPixel(x + i, y + j, width, height, xMin, xMax, yMin, yMax);
        }
    }
}

// Fractal Circle Pattern (Họa tiết vòng tròn Fractal)
void drawFractalCircles(int x, int y, int radius, int depth) {
    if (depth == 0 || radius < 2) return;
    
    // Vẽ vòng tròn chính
    circle(x, y, radius);
    
    // Vẽ 6 vòng tròn con xung quanh
    int newRadius = radius / 3;
    double angleStep = 60; // 360/6 = 60 độ
    
    for (int i = 0; i < 6; i++) {
        double angle = i * angleStep * 3.14159 / 180.0;
        int newX = x + (int)((radius - newRadius) * cos(angle));
        int newY = y + (int)((radius - newRadius) * sin(angle));
        
        drawFractalCircles(newX, newY, newRadius, depth - 1);
    }
}

// Vẽ mây huyền bí bằng Koch Curve
void drawMysticalCloud(int x, int y, int width, int height) {
    setcolor(COLOR(40, 45, 60));
    
    // Viền mây bằng Koch Curve
    int points[][2] = {
        {x - width/2, y},
        {x - width/3, y - height/2},
        {x, y - height},
        {x + width/3, y - height/2},
        {x + width/2, y},
        {x + width/3, y + height/3},
        {x - width/3, y + height/3}
    };
    
    for (int i = 0; i < 6; i++) {
        drawKochLine(points[i][0], points[i][1], 
                     points[i+1][0], points[i+1][1], 2);
    }
    drawKochLine(points[6][0], points[6][1], points[0][0], points[0][1], 2);
}

#endif
