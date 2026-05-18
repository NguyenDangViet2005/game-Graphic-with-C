#ifndef POWER_ATTACK_H
#define POWER_ATTACK_H

#include <graphics.h>
#include <math.h>

void drawPowerAttack(int left, int right, int y, float phase) {
    if (left > right) {
        int tmp = left;
        left = right;
        right = tmp;
    }

    int outerH = 24;
    int midH = 16;
    int coreH = 8;

    int outerTop = y - outerH / 2;
    int outerBottom = y + outerH / 2;
    int midTop = y - midH / 2;
    int midBottom = y + midH / 2;
    int coreTop = y - coreH / 2;
    int coreBottom = y + coreH / 2;

    setfillstyle(SOLID_FILL, COLOR(255, 80, 20));
    bar(left, outerTop, right, outerBottom);

    setfillstyle(SOLID_FILL, COLOR(255, 170, 50));
    bar(left, midTop, right, midBottom);

    setfillstyle(SOLID_FILL, WHITE);
    bar(left, coreTop, right, coreBottom);

    setcolor(COLOR(220, 30, 30));
    line(left, outerTop, right, outerTop);
    line(left, outerBottom, right, outerBottom);

    for (int x = left; x < right; x += 12) {
        float t = (float)sin(phase + x * 0.06f);
        int flare = (int)(4 + 6 * (t > 0.0f ? t : -t));
        int flareTop = outerTop - flare;
        int flareBottom = outerBottom + flare;

        setfillstyle(SOLID_FILL, COLOR(255, 120, 30));
        bar(x, flareTop, x + 8, outerTop);
        bar(x, outerBottom, x + 8, flareBottom);

        setfillstyle(SOLID_FILL, COLOR(255, 210, 90));
        bar(x + 2, flareTop + 2, x + 6, outerTop - 1);
        bar(x + 2, outerBottom + 1, x + 6, flareBottom - 2);
    }
}

#endif
