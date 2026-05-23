#ifndef POLYGON_FILL_H
#define POLYGON_FILL_H

#include <graphics.h>

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

#endif