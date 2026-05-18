#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <graphics.h>
#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "../algorithms/polygon_fill.cpp"

// Vị trí và kích thước nút
const int PAUSE_BTN_W = 50;
const int PAUSE_BTN_H = 50;

// Vẽ nút Menu/Pause (hình vuông vàng, viền nâu, gạch dóng)
void drawPauseButton(int x, int y) {
    // Viền ngoài (vàng nhạt)
    setcolor(COLOR(255, 230, 120));
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x, y, x + PAUSE_BTN_W, y + PAUSE_BTN_H);

    // Nền trong (xanh dương đậm)
    setfillstyle(SOLID_FILL, COLOR(5, 15, 60));
    bar(x + 2, y + 2, x + PAUSE_BTN_W - 2, y + PAUSE_BTN_H - 2);

    // Icon menu (3 dòng)
    setfillstyle(SOLID_FILL, COLOR(255, 230, 120));
    setcolor(COLOR(255, 230, 120));

    for(int i = 0; i < 3; i++) {
        int rowY = y + 15 + i * 10;

        // dấu chấm
        fillellipse(x + 14, rowY, 3, 3);

        // thanh ngang
        bar(x + 22, rowY - 2, x + PAUSE_BTN_W - 12, rowY + 2);
    }
}

// Kiểm tra click
int isClickOnPauseButton(int mx, int my, int btnX, int btnY) {
    return (mx >= btnX && mx <= btnX + PAUSE_BTN_W && 
            my >= btnY && my <= btnY + PAUSE_BTN_H);
}

// Hàm hỗ trợ vẽ nút trong Pause Menu để tái sử dụng
void drawSinglePauseMenuBtn(int index, int selected, int boxX, int boxY, int boxW, int btnW, int btnH, int startY, int spacing, const char* text) {
    int bX = boxX + (boxW - btnW) / 2;
    int bY = startY + index * (btnH + spacing);
    
    int borderColor = selected ? COLOR(255, 255, 0) : WHITE;
    int fillColor = selected ? COLOR(30, 45, 75) : COLOR(20, 30, 50);

    setcolor(borderColor);
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(bX, bY, bX + btnW, bY + btnH);

    setfillstyle(SOLID_FILL, fillColor);
    bar(bX + 1, bY + 1, bX + btnW - 1, bY + btnH - 1);
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    if (selected) setbkcolor(COLOR(30, 45, 75));
    else setbkcolor(COLOR(20, 30, 50));
    
    int tw = textwidth((char*)text);
    int th = 24; // textheight có thể không tồn tại trong bản đồ họa này, dùng hardcode theo font 3.
    outtextxy(bX + (btnW - tw)/2, bY + (btnH - th)/2, (char*)text);
}

// Vẽ menu Pause (overlay đè lên màn hình hiện tại)
// Trả về: 0 = Tiếp tục, 1 = Thoát ra menu chính
int showPauseMenuOverlay() {
    int boxW = 400;
    int boxH = 300;
    int boxX = (SCREEN_WIDTH - boxW) / 2;
    int boxY = (SCREEN_HEIGHT - boxH) / 2;
    
    // Lưu lại vùng background với margin thêm để bao gồm cả viền dày
    int margin = 10;
    int saveX1 = boxX - margin;
    int saveY1 = boxY - margin;
    int saveX2 = boxX + boxW + margin;
    int saveY2 = boxY + boxH + margin;
    
    unsigned int overlaySize = imagesize(saveX1, saveY1, saveX2, saveY2);
    void* savedBg = malloc(overlaySize);
    getimage(saveX1, saveY1, saveX2, saveY2, savedBg);
    
    // Nền khung menu
    setfillstyle(SOLID_FILL, COLOR(15, 25, 45)); // màu menu
    bar(boxX, boxY, boxX + boxW, boxY + boxH);
    
    // Viền khung
    setcolor(COLOR(255, 230, 100));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(boxX, boxY, boxX + boxW, boxY + boxH);
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(100, 120, 150));
    rectangle(boxX + 5, boxY + 5, boxX + boxW - 5, boxY + boxH - 5);
    
    // Tiêu đề
    char title[] = "TAM DUNG";
    settextstyle(BOLD_FONT, HORIZ_DIR, 5);
    setcolor(COLOR(255, 230, 100));
    setbkcolor(COLOR(15, 25, 45));
    int titleWidth = textwidth(title);
    outtextxy(boxX + (boxW - titleWidth) / 2, boxY + 30, title);
    
    // Các Text/Button
    const char* options[] = {"Choi Tiep", "Thoat Ra Menu"};
    int numOptions = 2;
    int currentSelection = 0;
    
    int btnW = 300;
    int btnH = 60;
    int startY = boxY + 110;
    int spacing = 20;
    int bX = boxX + (boxW - btnW) / 2;
    int bY[2];
    for (int i = 0; i < numOptions; i++) {
        bY[i] = startY + i * (btnH + spacing);
    }

    // Lam sạch buffer phím/chuột
    while(kbhit()) getch();
    while(ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
    
    // Ve lan dau
    for(int i=0; i<numOptions; i++) {
        drawSinglePauseMenuBtn(i, i == currentSelection, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[i]);
    }
    
    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();
            for(int i=0; i<numOptions; i++) {
                if (mx >= bX && mx <= bX + btnW && my >= bY[i] && my <= bY[i] + btnH) {
                    putimage(saveX1, saveY1, savedBg, COPY_PUT);
                    free(savedBg);
                    return i;
                }
            }
        }
        
        int mx = mousex();
        int my = mousey();
        for(int i=0; i<numOptions; i++) {
            if (mx >= bX && mx <= bX + btnW && my >= bY[i] && my <= bY[i] + btnH) {
                if (currentSelection != i) {
                    drawSinglePauseMenuBtn(currentSelection, 0, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[currentSelection]);
                    currentSelection = i;
                    drawSinglePauseMenuBtn(currentSelection, 1, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[currentSelection]);
                }
            }
        }
        
        if(kbhit()) {
            char key = getch();
            if(key == 0 || key == -32) {
                key = getch();
                if(key == 72) { // up
                    drawSinglePauseMenuBtn(currentSelection, 0, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[currentSelection]);
                    currentSelection--;
                    if(currentSelection < 0) currentSelection = numOptions - 1;
                    drawSinglePauseMenuBtn(currentSelection, 1, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[currentSelection]);
                } else if(key == 80) { // down
                    drawSinglePauseMenuBtn(currentSelection, 0, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[currentSelection]);
                    currentSelection++;
                    if(currentSelection >= numOptions) currentSelection = 0;
                    drawSinglePauseMenuBtn(currentSelection, 1, boxX, boxY, boxW, btnW, btnH, startY, spacing, options[currentSelection]);
                }
            } else if(key == 13) { // enter
                putimage(saveX1, saveY1, savedBg, COPY_PUT);
                free(savedBg);
                return currentSelection;
            } else if(key == 27) { // esc (tiep tuc)
                putimage(saveX1, saveY1, savedBg, COPY_PUT);
                free(savedBg);
                return 0;
            }
        }
        delay(10);
    }
    
    putimage(saveX1, saveY1, savedBg, COPY_PUT);
    free(savedBg);
    return 0;
}

#endif
