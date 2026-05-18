#ifndef FOOT_GLOW_H
#define FOOT_GLOW_H

#include <graphics.h>
#include "../algorithms/index.cpp"

void drawFootGlow(int x, int y, float scale) {
    int goldDark = COLOR(180, 130, 30);
    int goldMain = COLOR(240, 180, 40);
    int glowColor = COLOR(255, 255, 150);

    setlinestyle(SOLID_LINE, 0, scale > 1.5f ? 3 : 2);
    setcolor(goldDark);
    algorithmEllipse(x, y, 48 * scale, 14 * scale);

    setlinestyle(SOLID_LINE, 0, scale > 1.5f ? 2 : 1);
    setcolor(goldMain);
    algorithmEllipse(x, y, 56 * scale, 18 * scale);

    setcolor(glowColor);
    algorithmEllipse(x, y, 40 * scale, 10 * scale);
}

#endif
