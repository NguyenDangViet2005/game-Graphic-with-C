#ifndef FIREBALL_H
#define FIREBALL_H

#include <graphics.h>

void drawFireball(float x, float y, int isMask = 0) {
    const int pixel = 3;
    const int color0 = -1;
    const int color1 = isMask ? BLACK : COLOR(20, 80, 160);   // Dark ghostly blue edge
    const int color2 = isMask ? BLACK : COLOR(40, 140, 210);  // Ghostly blue
    const int color3 = isMask ? BLACK : COLOR(80, 200, 245);  // Cyan glow
    const int color4 = isMask ? BLACK : COLOR(150, 240, 255); // Pale cyan inner aura
    const int color5 = isMask ? BLACK : COLOR(230, 255, 255); // Bright white hot core

    const char* pixels[] = {
        "00001110000",
        "00122222100",
        "01233333210",
        "12344444321",
        "12345554321",
        "12345554321",
        "12345554321",
        "12344444321",
        "01233333210",
        "00122222100",
        "00001110000"
    };

    int rows = sizeof(pixels) / sizeof(pixels[0]);
    int cols = 11;
    int startX = (int)x - (cols * pixel) / 2;
    int startY = (int)y - (rows * pixel) / 2;

    if (isMask) {
        setfillstyle(SOLID_FILL, WHITE);
        bar(startX, startY, startX + cols * pixel, startY + rows * pixel);
    }

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            int drawColor = color0;
            switch (pixels[r][c]) {
                case '1': drawColor = color1; break;
                case '2': drawColor = color2; break;
                case '3': drawColor = color3; break;
                case '4': drawColor = color4; break;
                case '5': drawColor = color5; break;
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
