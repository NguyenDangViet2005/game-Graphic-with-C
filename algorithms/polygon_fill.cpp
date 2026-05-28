#ifndef POLYGON_FILL_H
#define POLYGON_FILL_H

#include <graphics.h>


// Thuật toán Boundary Fill đệ quy giới hạn biên để an toàn tuyệt đối chống tràn stack
void recursiveBoundaryFillBounded(int x, int y, int fillColor, int boundaryColor, int minX, int minY, int maxX, int maxY, int depth = 0) {
    if (x < minX || x > maxX || y < minY || y > maxY) {
        return;
    }
    if (depth > 120) { // Giới hạn độ sâu đệ quy tối ưu cho vật thể nhỏ
        return;
    }
    
    int currentColor = getpixel(x, y);
    if (currentColor == boundaryColor || currentColor == fillColor) {
        return;
    }
    
    putpixel(x, y, fillColor);
    
    recursiveBoundaryFillBounded(x + 1, y, fillColor, boundaryColor, minX, minY, maxX, maxY, depth + 1);
    recursiveBoundaryFillBounded(x - 1, y, fillColor, boundaryColor, minX, minY, maxX, maxY, depth + 1);
    recursiveBoundaryFillBounded(x, y + 1, fillColor, boundaryColor, minX, minY, maxX, maxY, depth + 1);
    recursiveBoundaryFillBounded(x, y - 1, fillColor, boundaryColor, minX, minY, maxX, maxY, depth + 1);
}

#endif