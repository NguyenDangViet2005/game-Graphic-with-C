#ifndef POLYGON_FILL_H
#define POLYGON_FILL_H

#include <graphics.h>

// Thuật toán Boundary Fill đệ quy
// - Tô vùng được bao bởi boundaryColor.
// - fillColor là màu tô vào bên trong; boundaryColor là màu biên cần dừng.
void recursiveBoundaryFill(int x, int y, int fillColor, int boundaryColor) {
    // Kiểm tra biên màn hình
    if (x < 0 || x >= getmaxx() || y < 0 || y >= getmaxy()) {
        return;
    }
    
    int currentColor = getpixel(x, y);
    
    // Nếu gặp màu biên hoặc đã tô rồi thì dừng
    if (currentColor == boundaryColor || currentColor == fillColor) {
        return;
    }
    
    // Tô màu điểm hiện tại rồi lan ra 4 hướng kề nhau
    putpixel(x, y, fillColor);
    
    // Đệ quy 4 hướng (4-connected)
    recursiveBoundaryFill(x + 1, y, fillColor, boundaryColor);
    recursiveBoundaryFill(x - 1, y, fillColor, boundaryColor);
    recursiveBoundaryFill(x, y + 1, fillColor, boundaryColor);
    recursiveBoundaryFill(x, y - 1, fillColor, boundaryColor);
}

#endif