#ifndef ENERGY_WAVE_H
#define ENERGY_WAVE_H

#include <graphics.h>
#include "../algorithms/index.cpp"
#include "../algorithms/polygon_fill.cpp"

void drawEnergyWave(int left, int right, int y) {
    int height = 22;
    int top = y - height / 2;
    int bottom = top + height;

    // Boundary fill de quy (vung nho, co bien ro dang hinh song nang luong)
    // - Ve bien hinh chu nhat bang mau boundary (WHITE)
    // - To mau phan ben trong cua song nang luong, dung lai khi gap bien
    setcolor(WHITE);
    rectangle(left, top, right, bottom);
    setcolor(WHITE);
    // To tu diem ben trong de dam bao chi to phan ruot song
    recursiveBoundaryFill(left + 1, top + 1, getcolor(), WHITE);

    setcolor(COLOR(220, 40, 40));
    // Bresenham line (thick)
    bresenhamThickLine(left, top, right, top, 2);
    bresenhamThickLine(left, bottom, right, bottom, 2);
}

#endif
