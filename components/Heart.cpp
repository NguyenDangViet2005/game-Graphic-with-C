#ifndef HEART_H
#define HEART_H

#include <graphics.h>
#include <stdio.h>
#include "../algorithms/index.cpp"

// Vẽ trái tim pixel art theo style ảnh tham khảo
void drawHeart(int x, int y, int scale = 2) {
    // Ma trận pixel của trái tim (0 = trong suốt, 2 = đỏ tối, 3 = đỏ, 4 = đỏ sáng, 5 = highlight trắng)
    int heartPattern[13][15] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,4,4,4,0,0,0,4,4,4,0,0,0},
        {0,0,4,3,3,3,4,0,4,3,3,5,4,0,0},
        {0,0,3,3,3,3,3,3,3,3,5,3,3,0,0},
        {0,3,3,3,3,3,3,3,3,3,3,3,3,3,0},
        {0,3,2,2,3,3,3,3,3,3,3,3,3,3,0},
        {0,3,2,2,3,3,3,3,3,3,3,3,3,3,0},
        {0,0,2,2,3,3,3,3,3,3,3,3,3,0,0},
        {0,0,0,2,2,3,3,3,3,3,3,3,0,0,0},
        {0,0,0,0,2,2,3,3,3,3,3,0,0,0,0},
        {0,0,0,0,0,2,2,3,3,3,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,3,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,3,0,0,0,0,0,0,0}
    };
    
    // Màu sắc tương ứng
    int colors[6];
    colors[0] = COLOR(255, 255, 255); // Transparent     
    colors[2] = COLOR(220, 20, 20);   // Đỏ tối
    colors[3] = COLOR(255, 0, 0);     // Đỏ chính
    colors[4] = COLOR(255, 120, 120); // Đỏ sáng
    colors[5] = WHITE;                 // Highlight trắng
    
    // Vẽ từng pixel màu (không viền)
    for(int i = 0; i < 13; i++) {
        for(int j = 0; j < 15; j++) {
            int pixelType = heartPattern[i][j];
            if(pixelType > 0) {
                setfillstyle(SOLID_FILL, colors[pixelType]);
                // Vẽ pixel với kích thước scale (sửa để các ô vuông kề khít nhau, không hiện viền rãnh)
                bar(x + j * scale, y + i * scale, 
                    x + j * scale + scale, y + i * scale + scale);
            }
        }
    }
    
    // Vẽ viền outline bao ngoài bằng đường line
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    
    // Phần trên trái
    midpointLine(x + 3*scale, y, x + 5*scale, y);
    midpointLine(x + 3*scale, y, x + 2*scale, y + scale);
    midpointLine(x + 2*scale, y + scale, x + scale, y + 2*scale);
    midpointLine(x + scale, y + 2*scale, x + scale, y + 3*scale);
    midpointLine(x + scale, y + 3*scale, x, y + 4*scale);
    
    // Cạnh trái xuống
    midpointLine(x, y + 4*scale, x, y + 6*scale);
    midpointLine(x, y + 6*scale, x + scale, y + 7*scale);
    midpointLine(x + scale, y + 7*scale, x + 2*scale, y + 8*scale);
    midpointLine(x + 2*scale, y + 8*scale, x + 3*scale, y + 9*scale);
    midpointLine(x + 3*scale, y + 9*scale, x + 4*scale, y + 10*scale);
    midpointLine(x + 4*scale, y + 10*scale, x + 5*scale, y + 11*scale);
    midpointLine(x + 5*scale, y + 11*scale, x + 6*scale, y + 12*scale);
    
    // Đáy (đỉnh tim)
    midpointLine(x + 6*scale, y + 12*scale, x + 7*scale, y + 12*scale);
    midpointLine(x + 7*scale, y + 12*scale, x + 8*scale, y + 12*scale);
    
    // Cạnh phải lên
    midpointLine(x + 8*scale, y + 12*scale, x + 9*scale, y + 11*scale);
    midpointLine(x + 9*scale, y + 11*scale, x + 10*scale, y + 10*scale);
    midpointLine(x + 10*scale, y + 10*scale, x + 11*scale, y + 9*scale);
    midpointLine(x + 11*scale, y + 9*scale, x + 12*scale, y + 8*scale);
    midpointLine(x + 12*scale, y + 8*scale, x + 13*scale, y + 7*scale);
    midpointLine(x + 13*scale, y + 7*scale, x + 14*scale, y + 6*scale);
    midpointLine(x + 14*scale, y + 6*scale, x + 14*scale, y + 4*scale);
    
    // Phần trên phải
    midpointLine(x + 14*scale, y + 4*scale, x + 13*scale, y + 3*scale);
    midpointLine(x + 13*scale, y + 3*scale, x + 13*scale, y + 2*scale);
    midpointLine(x + 13*scale, y + 2*scale, x + 12*scale, y + scale);
    midpointLine(x + 12*scale, y + scale, x + 11*scale, y);
    midpointLine(x + 11*scale, y, x + 9*scale, y);
    
    // Phần lõm giữa
    midpointLine(x + 9*scale, y, x + 8*scale, y + scale);
    midpointLine(x + 8*scale, y + scale, x + 7*scale, y + scale);
    midpointLine(x + 7*scale, y + scale, x + 6*scale, y);
    midpointLine(x + 6*scale, y, x + 5*scale, y);
}

// Vẽ nhiều trái tim liên tiếp (cho HP)
void drawHearts(int x, int y, int count, int scale = 2, int spacing = 5) {
    int heartWidth = 15 * scale;
    for(int i = 0; i < count; i++) {
        drawHeart(x + i * (heartWidth + spacing), y, scale);
    }
}

static void drawEnergyBar(int x, int y, int mana, int manaMax) {
    int barW = 120;
    int barH = 10;
    int filled = mana;
    if (filled < 0) filled = 0;
    if (filled > manaMax) filled = manaMax;

    setfillstyle(SOLID_FILL, COLOR(25, 40, 70));
    bar(x, y, x + barW, y + barH);

    int fillW = (manaMax > 0) ? (barW * filled) / manaMax : 0;
    if (fillW > 0) {
        int isFull = (manaMax > 0 && filled >= manaMax);
        int fillColor = isFull ? COLOR(220, 60, 60) : COLOR(80, 180, 255);
        setfillstyle(SOLID_FILL, fillColor);
        bar(x, y, x + fillW, y + barH);
    }

    setcolor(COLOR(10, 10, 10));
    rectangle(x, y, x + barW, y + barH);
}

void drawBossHealthBar(int hp, int maxHp) {
    int screenW = 1200;
    int barW = 600;
    int barH = 16;
    int x = (screenW - barW) / 2;
    int y = 40;

    // Vẽ khung viền hộp đen bảo vệ bên ngoài
    setfillstyle(SOLID_FILL, COLOR(15, 10, 10));
    bar(x - 4, y - 4, x + barW + 4, y + barH + 4);
    
    // Vẽ viền ngoài kiểu gothic đỏ tối
    setcolor(COLOR(139, 0, 0));
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x - 4, y - 4, x + barW + 4, y + barH + 4);
    
    // Vẽ nền thanh máu rỗng (màu đỏ tối đậm)
    setfillstyle(SOLID_FILL, COLOR(50, 10, 10));
    bar(x, y, x + barW, y + barH);

    // Vẽ thanh máu còn lại (màu đỏ tươi rực rỡ)
    if (hp > 0) {
        if (hp > maxHp) hp = maxHp;
        int fillW = (barW * hp) / maxHp;
        setfillstyle(SOLID_FILL, COLOR(210, 20, 30));
        bar(x, y, x + fillW, y + barH);

        // Highlight viền sáng trên đỉnh
        setcolor(COLOR(255, 120, 120));
        setlinestyle(SOLID_LINE, 0, 1);
        line(x, y + 2, x + fillW, y + 2);
    }

    // Viền trong ngăn chia
    setcolor(COLOR(10, 10, 10));
    setlinestyle(SOLID_LINE, 0, 1);
    rectangle(x, y, x + barW, y + barH);

    // Vẽ tên Boss
    setcolor(COLOR(230, 40, 40));
    settextstyle(BOLD_FONT, HORIZ_DIR, 2);
    setbkcolor(COLOR(15, 10, 10)); // Tránh nhiễu chữ
    char bossName[64];
    sprintf(bossName, "%s: %d / %d", gCurrentLanguage->boss_name, hp, maxHp);
    int textW = textwidth(bossName);
    outtextxy(x + (barW - textW) / 2, y - 28, bossName);
}

// Vẽ text HP, điểm, năng lượng
void drawGameStats(int hp, int score, int mana, int manaMax, int skillReady) {
    // Text HP
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(20, 20, (char*)gCurrentLanguage->hud_hp);
    
    // Vẽ trái tim
    drawHearts(70, 20, hp, 2, 5);
    
    // Text điểm
    setcolor(YELLOW);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char scoreText[50];
    sprintf(scoreText, "%s: %d", gCurrentLanguage->hud_score, score);
    outtextxy(20, 50, scoreText);

    // Nang luong bar
    setcolor(COLOR(160, 200, 255));
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    outtextxy(20, 78, (char*)gCurrentLanguage->hud_energy);
    drawEnergyBar(110, 80, mana, manaMax);

    (void)skillReady;
}

#endif
