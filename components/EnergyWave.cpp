#ifndef ENERGY_WAVE_H
#define ENERGY_WAVE_H

#include <graphics.h>

void drawEnergyWave(int left, int right, int y) {
    int height = 22;
    int top = y - height / 2;
    int bottom = top + height;

    setfillstyle(SOLID_FILL, WHITE);
    bar(left, top, right, bottom);

    setcolor(COLOR(220, 40, 40));
    line(left, top, right, top);
    line(left, bottom, right, bottom);
}

#endif
