#ifndef GHOST_H
#define GHOST_H

#include <graphics.h>

// Vẽ con ma pixel art
void drawGhost(int x, int y, int isMask = 0) {
    int colorBlack = BLACK;
    int colorWhite = isMask ? BLACK : COLOR(240, 245, 255); // Trắng sáng
    int colorLight = isMask ? BLACK : COLOR(190, 205, 235); // Xanh nhạt
    int colorMid   = isMask ? BLACK : COLOR(140, 155, 200); // Xanh tím giữa
    int colorDark  = isMask ? BLACK : COLOR(90, 100, 150);  // Tím đậm
    int colorDeep  = isMask ? BLACK : COLOR(40, 45, 70);    // Tím rất đậm/Đen
    
    int colorRed   = isMask ? BLACK : COLOR(255, 50, 50);   // Đỏ tà ác (glowing red eyes)
    
    int pixelSize = 3;
    int startX = x + 2 * pixelSize; // Căn chỉnh lại tâm
    int startY = y - 46 * pixelSize;

    if (isMask) {
        setfillstyle(SOLID_FILL, WHITE);
        bar(startX, startY, startX + 25 * pixelSize, startY + 46 * pixelSize);
    }
    
    const char* pixels[] = {
        "                         ",
        "         00000           ",
        "       001111100         ",
        "      01111111110        ",
        "     0111111111110       ",
        "     01111111111110      ",
        "    0111111111111110     ",
        "    0111111111111110     ",
        "    0111001110011110     ",
        "    0116600100661110     ", // Glowing evil slanted red eyes
        "    0110660106600110     ",
        "    0110066166000110     ",
        "    0110000100000110     ",
        "    0111001110011110     ",
        "    0111111111111110     ",
        "    0111111111111110     ",
        " 00 0111110011111110     ",
        "01100111100001111110     ",
        "01110111100001111110     ",
        "01111011110011111110   0 ",
        "01111111111111111110  010",
        "01111111111111111110  010",
        "0211111111111111111100110",
        "0221111111111111111110110",
        "032111111111111111111110 ",
        "032211111111111111111120 ",
        "032211111111111111111120 ",
        "043221111111111111111220 ",
        "043321111111111111111230 ",
        "054322111111111111112230 ",
        "054322111111111111112330 ",
        "054322111111111111112330 ",
        "055432211111111111122340 ",
        " 05432211111111111223340 ",
        " 0054322111111111223340  ",
        "  054432111111112233450  ",
        "  054432111111112233450  ",
        "  055432211111122334450  ",
        "0 05543321111122334450   ",
        "  05043221111223344550   ",
        " 0 005432111223344550  0 ",
        "     00542233445500      ",
        "       0554344550        ",
        "       005444550         ",
        "         055500     0    ",
        "          000            "
    };

    int rows = sizeof(pixels) / sizeof(pixels[0]);
    
    for (int r = 0; r < rows; r++) {
        for (int c = 0; pixels[r][c] != '\0'; c++) {
            char p = pixels[r][c];
            if (p >= '0' && p <= '6') {
                int drawColor = colorBlack;
                switch(p) {
                    case '0': drawColor = colorBlack; break;
                    case '1': drawColor = colorWhite; break;
                    case '2': drawColor = colorLight; break;
                    case '3': drawColor = colorMid; break;
                    case '4': drawColor = colorDark; break;
                    case '5': drawColor = colorDeep; break;
                    case '6': drawColor = colorRed; break;
                }
                setfillstyle(SOLID_FILL, drawColor);
                bar(startX + c * pixelSize, startY + r * pixelSize,
                    startX + (c + 1) * pixelSize, startY + (r + 1) * pixelSize);
            }
        }
    }
}

#endif
