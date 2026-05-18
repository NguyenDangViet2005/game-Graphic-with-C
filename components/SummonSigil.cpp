#ifndef SUMMON_SIGIL_H
#define SUMMON_SIGIL_H

#include <graphics.h>
#include <cmath>
#include "../configs/Config.cpp"
#include "../algorithms/index.cpp"
#include "../algorithms/fractal.cpp"

// Cong trieu hoi nho (hop phong cach Dark Forest)
void drawSummonSigil(int x, int y, float scale = 1.0f) {
    int outerR = (int)(52 * scale);
    int ringR1 = (int)(46 * scale);
    int ringR2 = (int)(38 * scale);
    int ringR3 = (int)(28 * scale);
    int coreR = (int)(12 * scale);

    auto polar = [&](double deg, int r) {
        double rad = deg * 3.14159 / 180.0;
        int px = x + (int)std::round(r * std::cos(rad));
        int py = y - (int)std::round(r * std::sin(rad));
        return std::pair<int, int>(px, py);
    };

    // Vong ngoai va ring trung
    setcolor(COLOR(200, 60, 60));
    bresenhamCircle(x, y, outerR);
    setcolor(COLOR(170, 50, 50));
    bresenhamCircle(x, y, ringR1);
    setcolor(COLOR(140, 40, 40));
    bresenhamCircle(x, y, ringR2);
    setcolor(COLOR(120, 35, 35));
    bresenhamCircle(x, y, ringR3);

    // Ngôi sao sáu cánh
    setcolor(COLOR(220, 80, 80));
    auto p0 = polar(90, ringR2);
    auto p1 = polar(210, ringR2);
    auto p2 = polar(330, ringR2);
    bresenhamLine(p0.first, p0.second, p1.first, p1.second);
    bresenhamLine(p1.first, p1.second, p2.first, p2.second);
    bresenhamLine(p2.first, p2.second, p0.first, p0.second);

    auto q0 = polar(270, ringR2);
    auto q1 = polar(30, ringR2);
    auto q2 = polar(150, ringR2);
    bresenhamLine(q0.first, q0.second, q1.first, q1.second);
    bresenhamLine(q1.first, q1.second, q2.first, q2.second);
    bresenhamLine(q2.first, q2.second, q0.first, q0.second);

    // Vong trong va tam
    setcolor(COLOR(200, 70, 70));
    bresenhamCircle(x, y, coreR);
    setcolor(COLOR(120, 35, 35));
    bresenhamCircle(x, y, (int)(6 * scale));

    // Dragon curve nhu dong nang luong
    setcolor(COLOR(90, 40, 55));
    drawDragonCurve(x - ringR2 + 6, y + 6, x + ringR2 - 6, y - 8, 9, 1);
    setcolor(COLOR(90, 40, 55));
    drawDragonCurve(x + ringR2 - 6, y + 6, x - ringR2 + 6, y - 8, 9, -1);

    // C-curve nhu rune nhe
    setcolor(COLOR(170, 70, 70));
    drawLevyCCurve(x - ringR1 + 8, y - 4, x - ringR2 + 4, y - 16, 7);
    drawLevyCCurve(x + ringR2 - 4, y - 16, x + ringR1 - 8, y - 4, 7);
    drawLevyCCurve(x - ringR2 + 4, y + 16, x - ringR1 + 8, y + 4, 7);
    drawLevyCCurve(x + ringR1 - 8, y + 4, x + ringR2 - 4, y + 16, 7);

    // Rune cham nho quanh ring
    setcolor(COLOR(200, 80, 80));
    for (int i = 0; i < 8; i++) {
        auto dot = polar(i * 45.0, ringR3);
        bresenhamCircle(dot.first, dot.second, (int)(2 * scale));
    }
}

#endif
