#ifndef FIREBALL_H
#define FIREBALL_H

#include <graphics.h>

void drawFireball(float x, float y) {
    const int pixel = 2;
    const int color0 = -1;
    const int color1 = COLOR(40, 140, 200);
    const int color2 = COLOR(70, 200, 240);
    const int color3 = COLOR(140, 240, 255);
    const int color4 = COLOR(200, 255, 255);

    const char* pixels[] = {
        "000220000",
        "002332000",
        "023443200",
        "023443200",
        "233444320",
        "233444320",
        "023443200",
        "022333200",
        "002222000"
    };

    int rows = sizeof(pixels) / sizeof(pixels[0]);
    int cols = 9;
    int startX = (int)x - (cols * pixel) / 2;
    int startY = (int)y - (rows * pixel) / 2;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int drawColor = color0;
            switch (pixels[r][c]) {
                case '1': drawColor = color1; break;
                case '2': drawColor = color2; break;
                case '3': drawColor = color3; break;
                case '4': drawColor = color4; break;
                default: drawColor = color0; break;
            }

            if (drawColor != color0) {
                setfillstyle(SOLID_FILL, drawColor);
                bar(startX + c * pixel, startY + r * pixel,
                    startX + (c + 1) * pixel, startY + (r + 1) * pixel);
            }
        }
    }
}

#endif
