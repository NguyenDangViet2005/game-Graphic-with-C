#ifndef MENU_CPP
#define MENU_CPP

#include <graphics.h>
#include <conio.h>
#include <string.h>
#include "configs/Config.cpp"
#include "components/index.cpp"

// Caching background để không phải render lại tĩnh
void* cachedBackground = NULL;

void loadAndDrawBackground() {
    if (cachedBackground == NULL) {
        cleardevice();
        setbkcolor(BLACK);
        drawMenuBackground(); // Hàm này render chậm
        
        // Lưu lại hình ảnh vào RAM
        unsigned int size = imagesize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        cachedBackground = malloc(size);
        getimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cachedBackground);
    } else {
        // Chỉ việc đẩy bộ nhớ ra màn hình, siêu nhanh
        putimage(0, 0, cachedBackground, COPY_PUT);
    }
}

// Vẽ tiêu đề game
void drawTitle() {
    char title[] = "MONSTER SLAYER";
    
    settextstyle(BOLD_FONT, HORIZ_DIR, 8); 
    setcolor(COLOR(255, 230, 100)); // Vàng ánh trăng
    setbkcolor(COLOR(10, 15, 30)); // Đặt màu nền chữ tiệp với bầu trời
    
    // Căn giữa text bằng textwidth
    int textLen = textwidth(title);
    int textX = (SCREEN_WIDTH - textLen) / 2;
    outtextxy(textX, 80, title); // Đẩy lên chút xíu so với 100
}

// Vẽ một button menu
void drawMenuButton(int x, int y, int width, int height, const char* text, int isSelected) {
    // Vẽ nền button
    if (isSelected) {
        setfillstyle(SOLID_FILL, COLOR(15, 25, 45));
        setcolor(COLOR(255, 230, 100));
    } else {
        setfillstyle(SOLID_FILL, DARKGRAY);
        setcolor(WHITE);
    }
    
    bar(x, y, x + width, y + height);
    
    // Vẽ viền button
    setlinestyle(SOLID_LINE, 0, 2);
    rectangle(x, y, x + width, y + height);
    
    // Vẽ text - căn giữa chính xác
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
    
    // Set màu nền cho text trùng với nền button
    if (isSelected) {
        setbkcolor(COLOR(15, 25, 45));
    } else {
        setbkcolor(DARKGRAY);
    }
    
    // Căn giữa text - font size 3: mỗi ký tự ~16 pixel rộng, 24 pixel cao
    int textLen = strlen(text);
    int estimatedWidth = textLen * 16;
    int estimatedHeight = 24;
    int textX = x + (width - estimatedWidth) / 2;
    int textY = y + (height - estimatedHeight) / 2;
    outtextxy(textX, textY, (char*)text);
}

// Hàm vẽ toàn bộ menu
void drawMenuScreen(int currentSelection, const char* menuItems[], int totalItems) {
    const int BUTTON_WIDTH = 400;
    const int BUTTON_HEIGHT = 60;
    const int BUTTON_SPACING = 20;
    const int START_Y = 250;
    
    // Vẽ background cực nhanh bằng cache thay vì vẽ lại từ đầu
    loadAndDrawBackground();
    
    // Vẽ tiêu đề
    drawTitle();
    
    // Vẽ các button menu
    for(int i = 0; i < totalItems; i++) {
        int buttonX = SCREEN_WIDTH - BUTTON_WIDTH - 150;
        int buttonY = START_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
        drawMenuButton(buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, 
                     menuItems[i], i == currentSelection);
    }
}

// Hiển thị menu chính
int showMainMenu() {
    const int BUTTON_WIDTH = 400;
    const int BUTTON_HEIGHT = 60;
    const int BUTTON_SPACING = 20;
    const int START_Y = 250;
    
    const char* menuItems[] = {
        "Choi game",
        "Huong dan",
        "Bang diem",
        "Thoat"
    };
    
    int currentSelection = 0;
    int totalItems = 4;
    
    // Vẽ màn hình ban đầu một lần duy nhất
    drawMenuScreen(currentSelection, menuItems, totalItems);
    
    while(1) {
        // Xử lý chuột click
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            
            // Kiểm tra xem click có nằm trong button nào không
            for(int i = 0; i < totalItems; i++) {
                int buttonX = SCREEN_WIDTH - BUTTON_WIDTH - 150;
                int buttonY = START_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
                
                // Kiểm tra xem click có trong vùng button này không
                if(mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
                   my >= buttonY && my <= buttonY + BUTTON_HEIGHT) {
                    return i; // Trả về lựa chọn
                }
            }
        }
        
        // Xử lý hover effect với chuột
        int mx = mousex();
        int my = mousey();
        int oldSelection = currentSelection;
        
        for(int i = 0; i < totalItems; i++) {
            int buttonX = SCREEN_WIDTH - BUTTON_WIDTH - 150;
            int buttonY = START_Y + i * (BUTTON_HEIGHT + BUTTON_SPACING);
            
            // Kiểm tra xem chuột có hover trên button này không
            if(mx >= buttonX && mx <= buttonX + BUTTON_WIDTH &&
               my >= buttonY && my <= buttonY + BUTTON_HEIGHT) {
                if(currentSelection != i) {
                    // Vẽ lại button cũ (unhighlight)
                    int oldButtonY = START_Y + currentSelection * (BUTTON_HEIGHT + BUTTON_SPACING);
                    drawMenuButton(buttonX, oldButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 0);
                    
                    // Vẽ lại button mới (highlight)
                    currentSelection = i;
                    drawMenuButton(buttonX, buttonY, BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 1);
                }
                break;
            }
        }
        
        // Xử lý phím bàn phím
        if(kbhit()) {
            char key = getch();
            
            // Xử lý phím đặc biệt (mũi tên)
            if(key == 0 || key == -32) {
                key = getch();
                int newSelection = currentSelection;
                
                if(key == 72) { // Mũi tên lên
                    newSelection--;
                    if(newSelection < 0) newSelection = totalItems - 1;
                }
                else if(key == 80) { // Mũi tên xuống
                    newSelection++;
                    if(newSelection >= totalItems) newSelection = 0;
                }
                
                if(newSelection != currentSelection) {
                    int buttonX = SCREEN_WIDTH - BUTTON_WIDTH - 150;
                    
                    // Vẽ lại button cũ
                    int oldButtonY = START_Y + currentSelection * (BUTTON_HEIGHT + BUTTON_SPACING);
                    drawMenuButton(buttonX, oldButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 0);
                    
                    // Vẽ lại button mới
                    currentSelection = newSelection;
                    int newButtonY = START_Y + currentSelection * (BUTTON_HEIGHT + BUTTON_SPACING);
                    drawMenuButton(buttonX, newButtonY, BUTTON_WIDTH, BUTTON_HEIGHT, 
                                 menuItems[currentSelection], 1);
                }
            }
            else if(key == 13) { // Enter
                return currentSelection;
            }
            else if(key == 27) { // ESC
                return 3; // Thoát
            }
        }
        
        delay(10); // Delay nhỏ để không tốn CPU
    }
    
    return 3; // Mặc định là thoát
}

// Hiển thị màn hình hướng dẫn
void showInstructions() {
    // Đẩy background từ cache ra thay vì vẽ lại
    loadAndDrawBackground();
    
    // Tiêu đề - căn giữa
    char title[] = "HUONG DAN";
    settextstyle(BOLD_FONT, HORIZ_DIR, 5); // To thêm chút
    
    // Set màu nền text tiệp với khoảng trời mây
    setbkcolor(COLOR(10, 15, 30));
    setcolor(COLOR(255, 230, 100)); // Vàng ánh trăng
    
    int titleWidth = textwidth(title);
    outtextxy((SCREEN_WIDTH - titleWidth) / 2, 80, title);
    
    // Vẽ khung chứa chữ ở bên phải
    int boxX = SCREEN_WIDTH / 2 - 20;
    int boxY = 160;
    int boxW = 550;
    int boxH = 400;
    
    // Nền khung
    setfillstyle(SOLID_FILL, COLOR(15, 20, 35));
    bar(boxX, boxY, boxX + boxW, boxY + boxH);
    
    // Viền khung
    setcolor(COLOR(255, 230, 100));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(boxX, boxY, boxX + boxW, boxY + boxH);
    // Viền trong nhỏ
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(100, 120, 150));
    rectangle(boxX + 5, boxY + 5, boxX + boxW - 5, boxY + boxH - 5);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(240, 240, 250)); // Trắng xám sáng
    setbkcolor(COLOR(15, 20, 35)); // Trùng màu nền khung
    
    int y = boxY + 60;
    int textX = boxX + 40; // Cách mép khung một đoạn
    
    outtextxy(textX, y, (char*)"- Phim MUI TEN: Di chuyen");
    y += 50;
    outtextxy(textX, y, (char*)"- Phim SPACE  : Tan cong");
    y += 50;
    outtextxy(textX, y, (char*)"- Thu thap diem va ne tranh");
    y += 50;
    outtextxy(textX, y, (char*)"  tat ca cac ke thu tren duong");
    y += 50;
    outtextxy(textX, y, (char*)"- Phim ESC    : Tam dung / Thoat");
    
    char backMsg[] = "Nhan ESC de quay lai menu";
    setcolor(COLOR(255, 255, 0)); // vàng
    
    // Text ở ngoài khung, dùng màu nền gốc
    setbkcolor(COLOR(10, 15, 30));
    outtextxy(textX, boxY + boxH + 30, backMsg);
    
    // Chờ ESC
    while(1) {
        if(kbhit()) {
            char key = getch();
            if(key == 27) break;
        }
        delay(50);
    }
}

// Hiển thị bảng điểm
void showScoreboard() {
    // Đẩy background từ cache ra thay vì vẽ lại
    loadAndDrawBackground();
    
    // Tiêu đề - căn giữa
    char title[] = "BANG DIEM";
    settextstyle(BOLD_FONT, HORIZ_DIR, 5); // Cho to giống Hướng dẫn
    setbkcolor(COLOR(10, 15, 30));
    setcolor(COLOR(255, 230, 100)); // Vàng ánh trăng
    
    int titleWidth = textwidth(title);
    outtextxy((SCREEN_WIDTH - titleWidth) / 2, 80, title);
    
    // Vẽ khung chứa chữ ở bên phải
    int boxX = SCREEN_WIDTH / 2 - 20;
    int boxY = 160;
    int boxW = 550;
    int boxH = 400;
    
    // Nền khung
    setfillstyle(SOLID_FILL, COLOR(15, 20, 35));
    bar(boxX, boxY, boxX + boxW, boxY + boxH);
    
    // Viền khung
    setcolor(COLOR(255, 230, 100));
    setlinestyle(SOLID_LINE, 0, 3);
    rectangle(boxX, boxY, boxX + boxW, boxY + boxH);
    // Viền trong nhỏ
    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(COLOR(100, 120, 150));
    rectangle(boxX + 5, boxY + 5, boxX + boxW - 5, boxY + boxH - 5);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(COLOR(240, 240, 250)); // Trắng xám sáng
    setbkcolor(COLOR(15, 20, 35)); // Trùng nền khung
    
    int y = boxY + 60;
    int textX = boxX + 60;
    
    outtextxy(textX, y, (char*)"1. Player 1 ......... 10000 pt");
    y += 50;
    outtextxy(textX, y, (char*)"2. Player 2 .......... 8500 pt");
    y += 50;
    outtextxy(textX, y, (char*)"3. Player 3 .......... 7200 pt");
    y += 50;
    outtextxy(textX, y, (char*)"4. Player 4 .......... 6100 pt");
    y += 50;
    outtextxy(textX, y, (char*)"5. Player 5 .......... 5000 pt");
    
    char backMsg2[] = "Nhan ESC de quay lai menu";
    setcolor(COLOR(255, 255, 0)); // vàng
    
    setbkcolor(COLOR(10, 15, 30));
    outtextxy(textX, boxY + boxH + 30, backMsg2);
    
    // Chờ ESC
    while(1) {
        if(kbhit()) {
            char key = getch();
            if(key == 27) break;
        }
        delay(50);
    }
}

// Hàm chơi game
void playGame() {
    // Khởi tạo HP và điểm số
    int hp = 3;
    int score = 0;
    
    int gameRunning = 1; // 1 = game running, 0 = thoat ra menu
    
    // Tọa độ nút pause
    int pauseBtnX = SCREEN_WIDTH - 70;
    int pauseBtnY = 20;

    // Vẽ màn hình game một lần duy nhất
    cleardevice();
    drawBackground();
    drawDarkForest();
    drawRhino(950, GROUND_Y + 30);
    drawExplorer(200, GROUND_Y + 30);
    drawGameStats(hp, score);
    drawPauseButton(pauseBtnX, pauseBtnY);

    while(kbhit()) getch();
    while(ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);
    
    while(gameRunning) {
        // Xử lý click chuột
        if(ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            if (isClickOnPauseButton(mx, my, pauseBtnX, pauseBtnY)) {
                // Hiển thị popup pause
                int choice = showPauseMenuOverlay();
                if (choice == 1) { // Thoát ra menu
                    gameRunning = 0;
                }
                // choice == 0 nghĩa là chơi tiếp, không làm gì cả
            }
        }
        
        // Xử lý phím
        if(kbhit()) {
            char key = getch();
            if(key == 27) { // ESC cũng mở menu tạm dừng
                int choice = showPauseMenuOverlay();
                if (choice == 1) { // Thoát ra menu
                    gameRunning = 0;
                }
            }
        }
        
        delay(30);
    }
}

// Hàm vòng lặp game chính - quản lý menu và lựa chọn
void gameLoop() {
    int running = 1;
    while(running) {
        int choice = showMainMenu();
        
        switch(choice) {
            case 0: 
                playGame();
                break;
            case 1: 
                showInstructions();
                break;
            case 2: 
                showScoreboard();
                break;
            case 3: 
                running = 0;
                break;
        }
    }
}

#endif
