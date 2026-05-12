#ifndef MENU_CACHE_CPP
#define MENU_CACHE_CPP
#include "../../components/LoadingScreen.cpp"
#include "Menu.cpp"

void loadAndDrawBackground() {
    if (cachedBackground == NULL) {
        // Bat dau loading
        drawLoadingScreen(0, "Vui long cho...");
        delay(150);
        
        // Ve vao buffer an trong khi hien thi progress
        int oldPage = getactivepage();
        setactivepage(1);  // Ve vao page an
        
        cleardevice();
        setbkcolor(BLACK);
        
        // Load tung phan voi status text
        setactivepage(0);
        drawLoadingScreen(15, "Dang tai...");
        setactivepage(1);
        delay(80);
        
        setactivepage(0);
        drawLoadingScreen(35, "Dang tai moi truong...");
        setactivepage(1);
        delay(80);
        
        // Ve background (phan cham nhat)
        drawMenuBackground();
        
        setactivepage(0);
        drawLoadingScreen(75, "Dang tai canh vat");
        setactivepage(1);
        delay(80);
        
        // Luu lai hinh anh vao RAM
        unsigned int size = imagesize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        cachedBackground = malloc(size);
        getimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cachedBackground);
        
        setactivepage(0);
        drawLoadingScreen(95, "Hoan thanh...");
        delay(100);
        
        // Hoan thanh loading
        drawLoadingScreen(100, "Bat dau!");
        delay(400);
        
        // Hien thi menu
        putimage(0, 0, cachedBackground, COPY_PUT);
        setactivepage(oldPage);
    } else {
        // Chi viec day bo nho ra man hinh, sieu nhanh
        putimage(0, 0, cachedBackground, COPY_PUT);
    }
}

#endif
