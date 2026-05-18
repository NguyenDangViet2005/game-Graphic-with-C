#ifndef EXPLORER_MIRRORED_H
#define EXPLORER_MIRRORED_H

#include <graphics.h>
#include "../algorithms/index.cpp"

#define S(val) ((int)((val) * scale)) // macro scale tọa do

void drawExplorerMirrored(int x, int y, float scale) {
    // Bang mau nhan vat
    int armorDark = COLOR(45, 50, 70);      // Giap toi
    int armorMain = COLOR(80, 90, 110);     // Giap sang
    int goldDark = COLOR(180, 130, 30);     // Vang dam
    int goldMain = COLOR(240, 180, 40);     // Vang chinh
    int goldLight = COLOR(255, 220, 100);   // Vang sang
    int gemColor = COLOR(220, 40, 40);      // Do ngoc
    int eyeColor = COLOR(255, 240, 50);     // Vang mat
    int glowColor = COLOR(255, 255, 150);   // Anh sang
    int outlineColor = BLACK;               // Vien den
    
    // do day net ve tuy theo scale
    int thickNormal = scale > 1.5f ? 2 : 1;
    int thickBold = scale > 1.5f ? 3 : 2;

    setlinestyle(SOLID_LINE, 0, thickNormal);

    // ong dung ten sau lung
    int quiverX = x + S(22);
    int quiverY = y - S(40);
    setfillstyle(SOLID_FILL, armorDark);
    int quiver[] = {quiverX, quiverY-S(15), quiverX-S(12), quiverY-S(5), quiverX+S(5), quiverY+S(15), quiverX+S(12), quiverY+S(5)};
    fillpoly(4, quiver); drawpoly(4, quiver);
    
    // 3 mui ten trong ong
    setcolor(goldLight);
    setlinestyle(SOLID_LINE, 0, thickBold);
    bresenhamLine(quiverX-S(2), quiverY-S(12), quiverX+S(8), quiverY-S(30));
    bresenhamLine(quiverX-S(6), quiverY-S(9), quiverX+S(2), quiverY-S(32));
    bresenhamLine(quiverX-S(10), quiverY-S(6), quiverX-S(4), quiverY-S(28));
    
    // long ten do
    setcolor(gemColor);
    bresenhamLine(quiverX+S(8), quiverY-S(30), quiverX+S(12), quiverY-S(27));
    bresenhamLine(quiverX+S(2), quiverY-S(32), quiverX+S(6), quiverY-S(29));
    bresenhamLine(quiverX-S(4), quiverY-S(28), quiverX, quiverY-S(25));
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // chan trai - dui
    setfillstyle(SOLID_FILL, armorDark);
    bar(x + S(5), y - S(25), x + S(20), y - S(10));
    setcolor(outlineColor);
    rectangle(x + S(5), y - S(25), x + S(20), y - S(10));
    
    // giap goi trai
    setfillstyle(SOLID_FILL, goldDark);
    int kneeL[] = {x+S(22), y-S(28), x+S(5), y-S(28), x+S(6), y-S(16), x+S(20), y-S(16)};
    fillpoly(4, kneeL); drawpoly(4, kneeL);

    // ong va ban chan trai
    setfillstyle(SOLID_FILL, armorDark);
    bar(x + S(5), y - S(10), x + S(20), y);
    setfillstyle(SOLID_FILL, armorMain);
    int bootL[] = {x+S(25), y, x+S(5), y, x+S(5), y-S(10), x+S(16), y-S(10)};
    fillpoly(4, bootL); drawpoly(4, bootL);

    // tay trai
    setfillstyle(SOLID_FILL, armorDark);
    bar(x + S(18), y - S(35), x + S(30), y - S(15));
    setcolor(outlineColor);
    rectangle(x + S(18), y - S(35), x + S(30), y - S(15));
    
    // nam tay trai
    setfillstyle(SOLID_FILL, armorMain);
    midpointFilledCircle(x + S(24), y - S(12), S(6));
    midpointCircle(x + S(24), y - S(12), S(6));

    // chan phai - dui
    setfillstyle(SOLID_FILL, armorMain);
    bar(x - S(20), y - S(25), x - S(5), y - S(10));
    setcolor(outlineColor);
    rectangle(x - S(20), y - S(25), x - S(5), y - S(10));

    // giap goi phai
    setfillstyle(SOLID_FILL, armorDark);
    int kneeR[] = {x-S(3), y-S(28), x-S(22), y-S(28), x-S(21), y-S(16), x-S(4), y-S(16)};
    fillpoly(4, kneeR); drawpoly(4, kneeR);
    setcolor(goldMain);
    bresenhamLine(x-S(3), y-S(28), x-S(22), y-S(28));
    setcolor(outlineColor);

    // ong va ban chan phai
    setfillstyle(SOLID_FILL, armorMain);
    bar(x - S(20), y - S(10), x - S(5), y);
    setfillstyle(SOLID_FILL, armorDark);
    int bootR[] = {x-S(5), y, x-S(25), y, x-S(18), y-S(10), x-S(5), y-S(10)};
    fillpoly(4, bootR); drawpoly(4, bootR);

    // than - giap nguc
    setfillstyle(SOLID_FILL, armorMain);
    int torso[] = {x+S(18), y-S(50), x-S(18), y-S(50), x-S(18), y-S(25), x+S(18), y-S(25)};
    fillpoly(4, torso); drawpoly(4, torso);
    
    // vien vang chu v tren nguc (dam va day hon)
    setcolor(goldMain);
    setlinestyle(SOLID_LINE, 0, thickBold + 1);
    bresenhamLine(x+S(18), y-S(40), x-S(4), y-S(25));
    bresenhamLine(x-S(18), y-S(40), x-S(4), y-S(25));
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // dai lung
    setfillstyle(SOLID_FILL, goldDark);
    bar(x+S(18), y-S(25), x-S(18), y-S(15));
    rectangle(x+S(18), y-S(25), x-S(18), y-S(15));

    // ngoc do tren dai
    setcolor(BLACK);
    midpointCircle(x-S(4), y-S(20), S(9));
    setcolor(goldMain);
    midpointFilledCircle(x-S(4), y-S(20), S(8)); 
    setcolor(goldLight);
    midpointCircle(x-S(4), y-S(20), S(8));
    setcolor(gemColor);
    midpointFilledCircle(x-S(4), y-S(20), S(5));

    // giap hang
    setfillstyle(SOLID_FILL, armorMain);
    int groin[] = {x+S(10), y-S(15), x-S(14), y-S(15), x-S(10), y-S(5), x+S(2), y-S(5)};
    fillpoly(4, groin); drawpoly(4, groin);
    setcolor(goldMain);
    bresenhamLine(x+S(10), y-S(15), x+S(2), y-S(5));
    bresenhamLine(x-S(14), y-S(15), x-S(10), y-S(5));
    setcolor(outlineColor);

    // tay phai cam cung
    setfillstyle(SOLID_FILL, armorMain);
    int armR[] = {x-S(15), y-S(40), x-S(30), y-S(40), x-S(40), y-S(30), x-S(25), y-S(30)};
    fillpoly(4, armR); drawpoly(4, armR);

    // nam tay phai
    setfillstyle(SOLID_FILL, armorDark);
    midpointFilledCircle(x-S(40), y-S(30), S(7));
    midpointCircle(x-S(40), y-S(30), S(7));

    // cung ten
    int bowX = x - S(40);
    int bowY = y - S(30);
    setlinestyle(SOLID_LINE, 0, thickBold);
    
    setcolor(goldMain);
    arc(bowX + S(10), bowY, 100, 260, S(25));
    setcolor(armorDark);
    arc(bowX + S(12), bowY, 105, 255, S(23));
    
    // tay cam cung
    setfillstyle(SOLID_FILL, armorDark);
    bar(bowX-S(5), bowY-S(6), bowX+S(2), bowY+S(6));
    setcolor(outlineColor);
    rectangle(bowX-S(5), bowY-S(6), bowX+S(2), bowY+S(6));
    setcolor(gemColor);
    midpointFilledCircle(bowX-S(1), bowY, S(2));

    // day cung
    setcolor(glowColor);
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    bresenhamLine(bowX + S(4), bowY - S(24), bowX + S(14), bowY);
    bresenhamLine(bowX + S(4), bowY + S(24), bowX + S(14), bowY);
    
    // mui ten nang luong
    setcolor(goldLight);
    setlinestyle(SOLID_LINE, 0, thickBold);
    bresenhamLine(bowX + S(14), bowY, bowX - S(16), bowY);
    
    // dau mui ten
    setfillstyle(SOLID_FILL, eyeColor);
    int arrowHead[] = {bowX-S(16), bowY, bowX-S(10), bowY-S(4), bowX-S(13), bowY, bowX-S(10), bowY+S(4)};
    fillpoly(4, arrowHead);
    setcolor(glowColor);
    drawpoly(4, arrowHead);

    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // dau va mu
    int headX = x;
    int headY = y - S(65);

    // giap vai
    setfillstyle(SOLID_FILL, armorDark);
    int shoulderL[] = {x+S(16), y-S(50), x+S(28), y-S(45), x+S(34), y-S(30), x+S(18), y-S(35)};
    fillpoly(4, shoulderL); drawpoly(4, shoulderL);
    setcolor(goldMain);
    bresenhamLine(x+S(28), y-S(45), x+S(34), y-S(30)); 
    setcolor(outlineColor);

    setfillstyle(SOLID_FILL, armorDark);
    int shoulderR[] = {x-S(16), y-S(50), x-S(28), y-S(45), x-S(34), y-S(30), x-S(18), y-S(35)};
    fillpoly(4, shoulderR); drawpoly(4, shoulderR);
    setcolor(goldMain);
    bresenhamLine(x-S(28), y-S(45), x-S(34), y-S(30));
    setcolor(outlineColor);

    // mu giap chinh
    setfillstyle(SOLID_FILL, armorDark);
    int helmet[] = {
        headX + S(22), headY + S(15),
        headX + S(25), headY - S(8),
        headX + S(15), headY - S(25),
        headX - S(15), headY - S(25),
        headX - S(25), headY - S(8),
        headX - S(22), headY + S(15),
        headX - S(10), headY + S(25),
        headX + S(10), headY + S(25)
    };
    fillpoly(8, helmet); drawpoly(8, helmet);

    // giap cam
    int helmetBottom[] = {
        headX + S(22), headY + S(15),
        headX + S(15), headY + S(30),
        headX - S(15), headY + S(30),
        headX - S(22), headY + S(15),
        headX - S(10), headY + S(25),
        headX + S(10), headY + S(25)
    };
    fillpoly(6, helmetBottom); drawpoly(6, helmetBottom);

    // cap sung
    setfillstyle(SOLID_FILL, armorDark);
    int hornL[] = {headX+S(22), headY-S(5), headX+S(38), headY-S(35), headX+S(15), headY-S(22)};
    fillpoly(3, hornL); drawpoly(3, hornL);
    setcolor(armorMain);
    bresenhamLine(headX+S(22), headY-S(5), headX+S(29), headY-S(22)); 
    setcolor(outlineColor);

    int hornR[] = {headX-S(22), headY-S(5), headX-S(38), headY-S(35), headX-S(15), headY-S(22)};
    fillpoly(3, hornR); drawpoly(3, hornR);
    setcolor(armorMain);
    bresenhamLine(headX-S(22), headY-S(5), headX-S(29), headY-S(22));
    setcolor(outlineColor);

    // chop mu co ngoc
    int crest[] = {headX+S(2), headY-S(23), headX-S(10), headY-S(42), headX-S(14), headY-S(23)};
    setfillstyle(SOLID_FILL, armorMain);
    fillpoly(3, crest); drawpoly(3, crest);

    setcolor(BLACK);
    midpointEllipse(headX-S(6), headY - S(18), S(7), S(9));
    setcolor(goldMain);
    midpointFilledEllipse(headX-S(6), headY - S(18), S(6), S(8));
    setcolor(goldLight);
    midpointEllipse(headX-S(6), headY - S(18), S(6), S(8));
    setcolor(gemColor);
    midpointFilledEllipse(headX-S(6), headY - S(18), S(4), S(6));

    // khe nhin
    setfillstyle(SOLID_FILL, BLACK);
    int visor[] = {
        headX + S(8), headY,
        headX + S(10), headY + S(10),
        headX - S(2),  headY + S(20),
        headX - S(12), headY + S(12), 
        headX - S(20), headY + S(20),
        headX - S(25), headY + S(8),
        headX - S(22), headY
    };
    fillpoly(7, visor);
    
    // vien khe nhin (xam nhat)
    setcolor(COLOR(180, 180, 180));
    setlinestyle(SOLID_LINE, 0, thickBold);
    for(int i=0; i<6; i++) {
        bresenhamLine(visor[i*2], visor[i*2+1], visor[i*2+2], visor[i*2+3]);
    }
    bresenhamLine(visor[12], visor[13], visor[0], visor[1]);
    
    // doi mat phat sang
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickNormal);
    setfillstyle(SOLID_FILL, eyeColor);
    
    int eyeL[] = {headX + S(5), headY + S(6), headX - S(4), headY + S(8), headX, headY + S(12)};
    fillpoly(3, eyeL);
    
    int eyeR[] = {headX - S(23), headY + S(6), headX - S(15), headY + S(8), headX - S(19), headY + S(11)};
    fillpoly(3, eyeR);

    setcolor(glowColor);
    drawpoly(3, eyeL);
    drawpoly(3, eyeR);

    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
