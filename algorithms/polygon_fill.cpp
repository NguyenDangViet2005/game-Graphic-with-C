#ifndef POLYGON_FILL_H
#define POLYGON_FILL_H

#include <graphics.h>
#include <stack>
#include <vector>
#include <algorithm>

// Thuật toán Flood Fill đệ quy
void recursiveFloodFill(int x, int y, int newColor, int oldColor) {
    // Kiểm tra biên
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    // Kiểm tra màu hiện tại
    int currentColor = getpixel(x, y);
    if (currentColor != oldColor || currentColor == newColor) {
        return;
    }
    
    // Tô màu điểm hiện tại
    putpixel(x, y, newColor);
    
    // Đệ quy 4 hướng
    recursiveFloodFill(x + 1, y, newColor, oldColor);
    recursiveFloodFill(x - 1, y, newColor, oldColor);
    recursiveFloodFill(x, y + 1, newColor, oldColor);
    recursiveFloodFill(x, y - 1, newColor, oldColor);
}

// Thuật toán Flood Fill không đệ quy (dùng stack để tránh stack overflow)
void stackFloodFill(int x, int y, int newColor, int oldColor) {
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    if (getpixel(x, y) != oldColor || oldColor == newColor) {
        return;
    }
    
    std::stack<std::pair<int, int>> pixelStack;
    pixelStack.push({x, y});
    
    while (!pixelStack.empty()) {
        auto [px, py] = pixelStack.top();
        pixelStack.pop();
        
        if (px < 0 || px >= getmaxx() || py < 0 || py >= getmaxy()) {
            continue;
        }
        
        if (getpixel(px, py) != oldColor) {
            continue;
        }
        
        putpixel(px, py, newColor);
        
        // Thêm 4 điểm kề vào stack
        pixelStack.push({px + 1, py});
        pixelStack.push({px - 1, py});
        pixelStack.push({px, py + 1});
        pixelStack.push({px, py - 1});
    }
}

// Thuật toán Scanline Fill cho đa giác (phiên bản đơn giản)
void scanlineFillPolygon(int points[], int numPoints, int fillColor) {
    if (numPoints < 3) return;
    
    // Tìm min/max Y
    int minY = points[1], maxY = points[1];
    for (int i = 1; i < numPoints; i++) {
        int y = points[i * 2 + 1];
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }
    
    // Duyệt từng scanline
    for (int y = minY; y <= maxY; y++) {
        int intersections[100]; // Mảng tĩnh thay vì vector
        int count = 0;
        
        // Tìm giao điểm với các cạnh
        for (int i = 0; i < numPoints; i++) {
            int j = (i + 1) % numPoints;
            int x1 = points[i * 2], y1 = points[i * 2 + 1];
            int x2 = points[j * 2], y2 = points[j * 2 + 1];
            
            // Kiểm tra nếu scanline cắt cạnh
            if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
                if (y1 != y2) {
                    int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                    intersections[count++] = x;
                }
            }
        }
        
        // Sắp xếp giao điểm bằng bubble sort
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (intersections[j] > intersections[j + 1]) {
                    int temp = intersections[j];
                    intersections[j] = intersections[j + 1];
                    intersections[j + 1] = temp;
                }
            }
        }
        
        // Tô màu giữa các cặp giao điểm
        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
                    putpixel(x, y, fillColor);
                }
            }
        }
    }
}

// Thuật toán Boundary Fill đệ quy
void recursiveBoundaryFill(int x, int y, int fillColor, int boundaryColor) {
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    int currentColor = getpixel(x, y);
    
    // Nếu là màu biên hoặc đã tô rồi thì dừng
    if (currentColor == boundaryColor || currentColor == fillColor) {
        return;
    }
    
    // Tô màu điểm hiện tại
    putpixel(x, y, fillColor);
    
    // Đệ quy 4 hướng
    recursiveBoundaryFill(x + 1, y, fillColor, boundaryColor);
    recursiveBoundaryFill(x - 1, y, fillColor, boundaryColor);
    recursiveBoundaryFill(x, y + 1, fillColor, boundaryColor);
    recursiveBoundaryFill(x, y - 1, fillColor, boundaryColor);
}

// Thuật toán Boundary Fill không đệ quy
void stackBoundaryFill(int x, int y, int fillColor, int boundaryColor) {
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    std::stack<std::pair<int, int>> pixelStack;
    pixelStack.push({x, y});
    
    while (!pixelStack.empty()) {
        auto [px, py] = pixelStack.top();
        pixelStack.pop();
        
        if (px < 0 || px >= getmaxx() || py < 0 || py >= getmaxy()) {
            continue;
        }
        
        int currentColor = getpixel(px, py);
        if (currentColor == boundaryColor || currentColor == fillColor) {
            continue;
        }
        
        putpixel(px, py, fillColor);
        
        // Thêm 4 điểm kề vào stack
        pixelStack.push({px + 1, py});
        pixelStack.push({px - 1, py});
        pixelStack.push({px, py + 1});
        pixelStack.push({px, py - 1});
    }
}

// Tô đa giác với pattern (họa tiết) - phiên bản đơn giản
void patternFillPolygon(int points[], int numPoints, int pattern[][8], int patternSize) {
    if (numPoints < 3) return;
    
    // Tìm min/max Y
    int minY = points[1], maxY = points[1];
    for (int i = 1; i < numPoints; i++) {
        int y = points[i * 2 + 1];
        if (y < minY) minY = y;
        if (y > maxY) maxY = y;
    }
    
    // Duyệt từng scanline
    for (int y = minY; y <= maxY; y++) {
        int intersections[100]; // Mảng tĩnh
        int count = 0;
        
        // Tìm giao điểm với các cạnh
        for (int i = 0; i < numPoints; i++) {
            int j = (i + 1) % numPoints;
            int x1 = points[i * 2], y1 = points[i * 2 + 1];
            int x2 = points[j * 2], y2 = points[j * 2 + 1];
            
            if ((y1 <= y && y < y2) || (y2 <= y && y < y1)) {
                if (y1 != y2) {
                    int x = x1 + (y - y1) * (x2 - x1) / (y2 - y1);
                    intersections[count++] = x;
                }
            }
        }
        
        // Sắp xếp bằng bubble sort
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (intersections[j] > intersections[j + 1]) {
                    int temp = intersections[j];
                    intersections[j] = intersections[j + 1];
                    intersections[j + 1] = temp;
                }
            }
        }
        
        // Tô màu với pattern
        for (int i = 0; i < count; i += 2) {
            if (i + 1 < count) {
                for (int x = intersections[i]; x <= intersections[i + 1]; x++) {
                    int patternX = x % patternSize;
                    int patternY = y % patternSize;
                    if (pattern[patternY][patternX] == 1) {
                        putpixel(x, y, getcolor());
                    }
                }
            }
        }
    }
}

#endif