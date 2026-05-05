#ifndef ALGORITHMS_INDEX_H
#define ALGORITHMS_INDEX_H

#include "bresenham.cpp"
#include "midpoint.cpp"
#include "polygon_fill.cpp"
#include "fractal.cpp"
#include <graphics.h>

// Wrapper functions để thay thế các hàm graphics.h chuẩn

// Thay thế hàm line() bằng Bresenham (hoặc dùng hàm gốc nếu muốn nhanh)
inline void algorithmLine(int x1, int y1, int x2, int y2) {
    line(x1, y1, x2, y2);  // Dùng hàm gốc, nhanh hơn
    // bresenhamLine(x1, y1, x2, y2);  // Dùng thuật toán tự code
}

// Thay thế hàm line() với độ dày
inline void algorithmThickLine(int x1, int y1, int x2, int y2, int thickness) {
    bresenhamThickLine(x1, y1, x2, y2, thickness);
}

// Thay thế hàm circle() bằng Midpoint (hoặc dùng hàm gốc nếu muốn nhanh)
inline void algorithmCircle(int x, int y, int radius) {
    circle(x, y, radius);  // Dùng hàm gốc, nhanh hơn
    // midpointCircle(x, y, radius);  // Dùng thuật toán tự code
}

// Thay thế hàm fillellipse() bằng Midpoint (hoặc dùng hàm gốc nếu muốn nhanh)
inline void algorithmFillEllipse(int x, int y, int radiusX, int radiusY) {
    fillellipse(x, y, radiusX, radiusY);  // Dùng hàm gốc, nhanh hơn
    // midpointFilledEllipse(x, y, radiusX, radiusY);  // Dùng thuật toán tự code
}

// Thay thế hàm ellipse() bằng Midpoint (chỉ viền) (hoặc dùng hàm gốc nếu muốn nhanh)
inline void algorithmEllipse(int x, int y, int radiusX, int radiusY) {
    ellipse(x, y, 0, 360, radiusX, radiusY);  // Dùng hàm gốc, nhanh hơn
    // midpointEllipse(x, y, radiusX, radiusY);  // Dùng thuật toán tự code
}

// Thay thế hàm fillcircle() bằng Midpoint
inline void algorithmFillCircle(int x, int y, int radius) {
    midpointFilledCircle(x, y, radius);
}

// Wrapper functions cho thuật toán tô màu đa giác

// Thay thế floodfill() bằng thuật toán đệ quy
inline void algorithmFloodFill(int x, int y, int newColor) {
    int oldColor = getpixel(x, y);
    if (oldColor != newColor) {
        recursiveFloodFill(x, y, newColor, oldColor);
    }
}

// Thay thế floodfill() bằng thuật toán stack (an toàn hơn)
inline void algorithmStackFloodFill(int x, int y, int newColor) {
    int oldColor = getpixel(x, y);
    if (oldColor != newColor) {
        stackFloodFill(x, y, newColor, oldColor);
    }
}

// Tô đa giác bằng scanline
inline void algorithmFillPoly(int points[], int numPoints) {
    scanlineFillPolygon(points, numPoints, getcolor());
}

// Boundary fill đệ quy
inline void algorithmBoundaryFill(int x, int y, int boundaryColor) {
    recursiveBoundaryFill(x, y, getcolor(), boundaryColor);
}

// Boundary fill stack
inline void algorithmStackBoundaryFill(int x, int y, int boundaryColor) {
    stackBoundaryFill(x, y, getcolor(), boundaryColor);
}

// Macro để dễ dàng chuyển đổi
// #define USE_ALGORITHM_GRAPHICS  // Tạm thời disable
#ifdef USE_ALGORITHM_GRAPHICS
    #define line(x1, y1, x2, y2) algorithmLine(x1, y1, x2, y2)
    #define circle(x, y, r) algorithmCircle(x, y, r)
    #define fillellipse(x, y, rx, ry) algorithmFillEllipse(x, y, rx, ry)
    #define ellipse(x, y, start, end, rx, ry) algorithmEllipse(x, y, rx, ry)
    // Chỉ thay thế một số hàm fillpoly, không phải tất cả
    #define floodfill(x, y, color) algorithmStackFloodFill(x, y, color)
#endif

#endif