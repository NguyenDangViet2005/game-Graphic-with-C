#ifndef POWER_ATTACK_H
#define POWER_ATTACK_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"

void drawPowerAttack(int left, int right, int y, float phase) {
    if (left > right) {
        int tmp = left;
        left = right;
        right = tmp;
    }

    int outerH = 34; // Cyan/Blue Outer Glow
    int midH = 20;   // Yellow body
    int coreH = 10;  // White core

    int outerTop = y - outerH / 2;
    int outerBottom = y + outerH / 2;
    int midTop = y - midH / 2;
    int midBottom = y + midH / 2;
    int coreTop = y - coreH / 2;
    int coreBottom = y + coreH / 2;

    // 1. Vẽ lớp phát sáng ngoài cùng (Cyan / Light Blue)
    setfillstyle(SOLID_FILL, COLOR(0, 230, 255));
    bar(left, outerTop, right, outerBottom);

    // 2. Vẽ thân laser màu vàng (Yellow)
    setfillstyle(SOLID_FILL, COLOR(255, 255, 0));
    bar(left, midTop, right, midBottom);

    // 3. Vẽ lõi laser màu trắng (White Core)
    setfillstyle(SOLID_FILL, WHITE);
    bar(left, coreTop, right, coreBottom);

    // 4. Vẽ các đường truyền dẫn năng lượng dạng zigzag chạy dọc tia laser
    setcolor(COLOR(0, 162, 232));
    setlinestyle(SOLID_LINE, 0, 3);
    
    int segmentWidth = 40;
    for (int x = left; x < right; x += segmentWidth) {
        // Sử dụng sin và phase để tạo sóng điện chuyển động nhấp nhô tuần hoàn
        float angle1 = phase * 10.0f + x * 0.04f;
        float angle2 = phase * 10.0f + (x + segmentWidth) * 0.04f;
        
        int yOffset1 = (int)(sin(angle1) * 36.0f);
        int yOffset2 = (int)(sin(angle2) * 36.0f);
        
        int nextX = x + segmentWidth;
        if (nextX > right) nextX = right;
        
        line(x, y + yOffset1, nextX, y + yOffset2);
    }
    setlinestyle(SOLID_LINE, 0, 1);

    // 5. Vẽ các mảnh tàn lửa / bụi năng lượng nhỏ bay xung quanh tia laser
    for (int x = left + 10; x < right; x += 70) {
        float sparkPhase = phase * 8.0f + x * 0.03f;
        int sparkY1 = y - 45 - (int)(fabs(sin(sparkPhase)) * 20.0f);
        int sparkY2 = y + 45 + (int)(fabs(cos(sparkPhase)) * 20.0f);
        
        setcolor(COLOR(0, 180, 255));
        setfillstyle(SOLID_FILL, COLOR(0, 180, 255));
        
        // Mảnh lửa phía trên (hình tam giác nhỏ lệch)
        int pts1[] = {
            x, sparkY1 - 4,
            x + 5, sparkY1 + 1,
            x - 3, sparkY1 + 3,
            x, sparkY1 - 4
        };
        fillpoly(4, pts1);
        
        // Mảnh lửa phía dưới
        int pts2[] = {
            x + 25, sparkY2 - 3,
            x + 28, sparkY2 + 2,
            x + 20, sparkY2 + 4,
            x + 25, sparkY2 - 3
        };
        fillpoly(4, pts2);
    }
}

#endif
