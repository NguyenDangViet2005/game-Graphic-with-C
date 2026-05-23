#ifndef EXPLORER_H
#define EXPLORER_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"

#define S(val) ((int)((val) * scale)) // macro scale tọa độ

static void rotatePoint(float x, float y, float cx, float cy, float cosA, float sinA, int& outX, int& outY) {
    float tx = x - cx;
    float ty = y - cy;
    float rx = tx * cosA - ty * sinA;
    float ry = tx * sinA + ty * cosA;
    outX = (int)(rx + cx);
    outY = (int)(ry + cy);
}

static void buildRotatedPoly(const int* pts, int count, float cx, float cy, float cosA, float sinA, int* outPts) {
    for (int i = 0; i < count; i++) {
        rotatePoint((float)pts[i * 2], (float)pts[i * 2 + 1], cx, cy, cosA, sinA, outPts[i * 2], outPts[i * 2 + 1]);
    }
}

void drawExplorer(int x, int y, float scale, float armAngle, float headAngle) {
    // Bảng màu nhân vật
    int armorDark = COLOR(45, 50, 70);      // Giáp tối
    int armorMain = COLOR(80, 90, 110);     // Giáp sáng
    int goldDark = COLOR(180, 130, 30);     // Vàng đậm
    int goldMain = COLOR(240, 180, 40);     // Vàng chính
    int goldLight = COLOR(255, 220, 100);   // Vàng sáng
    int gemColor = COLOR(220, 40, 40);      // Đỏ ngọc
    int eyeColor = COLOR(255, 240, 50);     // Vàng mắt
    int glowColor = COLOR(255, 255, 150);   // Ánh sáng
    int outlineColor = BLACK;               // Viền đen
    
    // độ dày nét vẽ tùy theo scale
    int thickNormal = scale > 1.5f ? 2 : 1;
    int thickBold = scale > 1.5f ? 3 : 2;

    setlinestyle(SOLID_LINE, 0, thickNormal);

    // ống đựng tên sau lưng
    int quiverX = x - S(22);
    int quiverY = y - S(40);
    setfillstyle(SOLID_FILL, armorDark);
    int quiver[] = {quiverX, quiverY-S(15), quiverX+S(12), quiverY-S(5), quiverX-S(5), quiverY+S(15), quiverX-S(12), quiverY+S(5)};
    fillpoly(4, quiver); drawpoly(4, quiver);
    
    // 3 mũi tên trong ống
    setcolor(goldLight);
    setlinestyle(SOLID_LINE, 0, thickBold);
    bresenhamLine(quiverX+S(2), quiverY-S(12), quiverX-S(8), quiverY-S(30));
    bresenhamLine(quiverX+S(6), quiverY-S(9), quiverX-S(2), quiverY-S(32));
    bresenhamLine(quiverX+S(10), quiverY-S(6), quiverX+S(4), quiverY-S(28));
    
    // lông tên đỏ
    setcolor(gemColor);
    bresenhamLine(quiverX-S(8), quiverY-S(30), quiverX-S(12), quiverY-S(27));
    bresenhamLine(quiverX-S(2), quiverY-S(32), quiverX-S(6), quiverY-S(29));
    bresenhamLine(quiverX+S(4), quiverY-S(28), quiverX, quiverY-S(25));
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // chân trái - đùi
    setfillstyle(SOLID_FILL, armorDark);
    bar(x - S(20), y - S(25), x - S(5), y - S(10));
    setcolor(outlineColor);
    rectangle(x - S(20), y - S(25), x - S(5), y - S(10));
    
    // giáp gối trái
    setfillstyle(SOLID_FILL, goldDark);
    int kneeL[] = {x-S(22), y-S(28), x-S(5), y-S(28), x-S(6), y-S(16), x-S(20), y-S(16)};
    fillpoly(4, kneeL); drawpoly(4, kneeL);

    // ống và bàn chân trái
    setfillstyle(SOLID_FILL, armorDark);
    bar(x - S(20), y - S(10), x - S(5), y);
    setfillstyle(SOLID_FILL, armorMain);
    int bootL[] = {x-S(25), y, x-S(5), y, x-S(5), y-S(10), x-S(16), y-S(10)};
    fillpoly(4, bootL); drawpoly(4, bootL);

    // tay trái
    setfillstyle(SOLID_FILL, armorDark);
    bar(x - S(30), y - S(35), x - S(18), y - S(15));
    setcolor(outlineColor);
    rectangle(x - S(30), y - S(35), x - S(18), y - S(15));
    
    // nắm tay trái
    setfillstyle(SOLID_FILL, armorMain);
    midpointFilledCircle(x - S(24), y - S(12), S(6));
    midpointCircle(x - S(24), y - S(12), S(6));

    // chân phải - đùi
    setfillstyle(SOLID_FILL, armorMain);
    bar(x + S(5), y - S(25), x + S(20), y - S(10));
    setcolor(outlineColor);
    rectangle(x + S(5), y - S(25), x + S(20), y - S(10));

    // giáp gối phải
    setfillstyle(SOLID_FILL, armorDark);
    int kneeR[] = {x+S(3), y-S(28), x+S(22), y-S(28), x+S(21), y-S(16), x+S(4), y-S(16)};
    fillpoly(4, kneeR); drawpoly(4, kneeR);
    setcolor(goldMain);
    bresenhamLine(x+S(3), y-S(28), x+S(22), y-S(28));
    setcolor(outlineColor);

    // ống và bàn chân phải
    setfillstyle(SOLID_FILL, armorMain);
    bar(x + S(5), y - S(10), x + S(20), y);
    setfillstyle(SOLID_FILL, armorDark);
    int bootR[] = {x+S(5), y, x+S(25), y, x+S(18), y-S(10), x+S(5), y-S(10)};
    fillpoly(4, bootR); drawpoly(4, bootR);

    // thân - giáp ngực
    setfillstyle(SOLID_FILL, armorMain);
    int torso[] = {x-S(18), y-S(50), x+S(18), y-S(50), x+S(18), y-S(25), x-S(18), y-S(25)};
    fillpoly(4, torso); drawpoly(4, torso);
    
    // viền vàng chữ v trên ngực (đậm và dày hơn)
    setcolor(goldMain);
    setlinestyle(SOLID_LINE, 0, thickBold + 1);
    bresenhamLine(x-S(18), y-S(40), x+S(4), y-S(25));
    bresenhamLine(x+S(18), y-S(40), x+S(4), y-S(25));
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // đai lưng
    setfillstyle(SOLID_FILL, goldDark);
    bar(x-S(18), y-S(25), x+S(18), y-S(15));
    rectangle(x-S(18), y-S(25), x+S(18), y-S(15));

    // ngọc đỏ trên đai
    setcolor(BLACK);
    midpointCircle(x+S(4), y-S(20), S(9));
    setcolor(goldMain);
    midpointFilledCircle(x+S(4), y-S(20), S(8)); 
    setcolor(goldLight);
    midpointCircle(x+S(4), y-S(20), S(8));
    setcolor(gemColor);
    midpointFilledCircle(x+S(4), y-S(20), S(5));

    // giáp háng
    setfillstyle(SOLID_FILL, armorMain);
    int groin[] = {x-S(10), y-S(15), x+S(14), y-S(15), x+S(10), y-S(5), x-S(2), y-S(5)};
    fillpoly(4, groin); drawpoly(4, groin);
    setcolor(goldMain);
    bresenhamLine(x-S(10), y-S(15), x-S(2), y-S(5));
    bresenhamLine(x+S(14), y-S(15), x+S(10), y-S(5));
    setcolor(outlineColor);

    // tay phải cầm cung (xoay quanh khop)
    float armCos = (float)cos(armAngle);
    float armSin = (float)sin(armAngle);
    float armPivotX = (float)(x + S(25));
    float armPivotY = (float)(y - S(35));
    setfillstyle(SOLID_FILL, armorMain);
    int armR[] = {x+S(15), y-S(40), x+S(30), y-S(40), x+S(40), y-S(30), x+S(25), y-S(30)};
    int armRRot[8];
    buildRotatedPoly(armR, 4, armPivotX, armPivotY, armCos, armSin, armRRot);
    fillpoly(4, armRRot); drawpoly(4, armRRot);

    // nắm tay phải
    setfillstyle(SOLID_FILL, armorDark);
    int handX = 0;
    int handY = 0;
    rotatePoint((float)(x + S(40)), (float)(y - S(30)), armPivotX, armPivotY, armCos, armSin, handX, handY);
    midpointFilledCircle(handX, handY, S(7));
    midpointCircle(handX, handY, S(7));

    // cung tên
    int bowX = x + S(40);
    int bowY = y - S(30);
    int bowXr = 0;
    int bowYr = 0;
    rotatePoint((float)bowX, (float)bowY, armPivotX, armPivotY, armCos, armSin, bowXr, bowYr);
    float bowAngleOffset = armAngle * 180.0f / 3.1415926f;
    setlinestyle(SOLID_LINE, 0, thickBold);
    
    setcolor(goldMain);
    arc(bowXr - S(10), bowYr, (int)(280 + bowAngleOffset), (int)(80 + bowAngleOffset), S(25));
    setcolor(armorDark);
    arc(bowXr - S(12), bowYr, (int)(285 + bowAngleOffset), (int)(75 + bowAngleOffset), S(23));
    
    // tay cầm cung
    setfillstyle(SOLID_FILL, armorDark);
    bar(bowXr-S(2), bowYr-S(6), bowXr+S(5), bowYr+S(6));
    setcolor(outlineColor);
    rectangle(bowXr-S(2), bowYr-S(6), bowXr+S(5), bowYr+S(6));
    setcolor(gemColor);
    midpointFilledCircle(bowXr+S(1), bowYr, S(2));

    // dây cung
    setcolor(glowColor);
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    int lineA0x = 0, lineA0y = 0, lineA1x = 0, lineA1y = 0;
    int lineB0x = 0, lineB0y = 0, lineB1x = 0, lineB1y = 0;
    rotatePoint((float)(bowX - S(4)), (float)(bowY - S(24)), armPivotX, armPivotY, armCos, armSin, lineA0x, lineA0y);
    rotatePoint((float)(bowX - S(14)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, lineA1x, lineA1y);
    rotatePoint((float)(bowX - S(4)), (float)(bowY + S(24)), armPivotX, armPivotY, armCos, armSin, lineB0x, lineB0y);
    rotatePoint((float)(bowX - S(14)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, lineB1x, lineB1y);
    bresenhamLine(lineA0x, lineA0y, lineA1x, lineA1y);
    bresenhamLine(lineB0x, lineB0y, lineB1x, lineB1y);
    
    // mũi tên năng lượng
    setcolor(goldLight);
    setlinestyle(SOLID_LINE, 0, thickBold);
    int arrowLx = 0, arrowLy = 0, arrowRx = 0, arrowRy = 0;
    rotatePoint((float)(bowX - S(14)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, arrowLx, arrowLy);
    rotatePoint((float)(bowX + S(16)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, arrowRx, arrowRy);
    bresenhamLine(arrowLx, arrowLy, arrowRx, arrowRy);
    
    // đầu mũi tên
    setfillstyle(SOLID_FILL, eyeColor);
    int arrowHead[] = {bowX+S(16), bowY, bowX+S(10), bowY-S(4), bowX+S(13), bowY, bowX+S(10), bowY+S(4)};
    int arrowHeadRot[8];
    buildRotatedPoly(arrowHead, 4, armPivotX, armPivotY, armCos, armSin, arrowHeadRot);
    fillpoly(4, arrowHeadRot);
    setcolor(glowColor);
    drawpoly(4, arrowHeadRot);

    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // đầu và mũ
    int headX = x;
    int headY = y - S(65);
    float headCos = (float)cos(headAngle);
    float headSin = (float)sin(headAngle);
    float headPivotX = (float)headX;
    float headPivotY = (float)headY;

    // giáp vai
    setfillstyle(SOLID_FILL, armorDark);
    int shoulderL[] = {x-S(16), y-S(50), x-S(28), y-S(45), x-S(34), y-S(30), x-S(18), y-S(35)};
    fillpoly(4, shoulderL); drawpoly(4, shoulderL);
    setcolor(goldMain);
    bresenhamLine(x-S(28), y-S(45), x-S(34), y-S(30)); 
    setcolor(outlineColor);

    setfillstyle(SOLID_FILL, armorDark);
    int shoulderR[] = {x+S(16), y-S(50), x+S(28), y-S(45), x+S(34), y-S(30), x+S(18), y-S(35)};
    fillpoly(4, shoulderR); drawpoly(4, shoulderR);
    setcolor(goldMain);
    bresenhamLine(x+S(28), y-S(45), x+S(34), y-S(30));
    setcolor(outlineColor);

    // mũ giáp chính
    setfillstyle(SOLID_FILL, armorDark);
    int helmet[] = {
        headX - S(22), headY + S(15),
        headX - S(25), headY - S(8),
        headX - S(15), headY - S(25),
        headX + S(15), headY - S(25),
        headX + S(25), headY - S(8),
        headX + S(22), headY + S(15),
        headX + S(10), headY + S(25),
        headX - S(10), headY + S(25)
    };
    int helmetRot[16];
    buildRotatedPoly(helmet, 8, headPivotX, headPivotY, headCos, headSin, helmetRot);
    fillpoly(8, helmetRot); drawpoly(8, helmetRot);

    // giáp cằm
    int helmetBottom[] = {
        headX - S(22), headY + S(15),
        headX - S(15), headY + S(30),
        headX + S(15), headY + S(30),
        headX + S(22), headY + S(15),
        headX + S(10), headY + S(25),
        headX - S(10), headY + S(25)
    };
    int helmetBottomRot[12];
    buildRotatedPoly(helmetBottom, 6, headPivotX, headPivotY, headCos, headSin, helmetBottomRot);
    fillpoly(6, helmetBottomRot); drawpoly(6, helmetBottomRot);

    // cặp sừng
    setfillstyle(SOLID_FILL, armorDark);
    int hornL[] = {headX-S(22), headY-S(5), headX-S(38), headY-S(35), headX-S(15), headY-S(22)};
    int hornLRot[6];
    buildRotatedPoly(hornL, 3, headPivotX, headPivotY, headCos, headSin, hornLRot);
    fillpoly(3, hornLRot); drawpoly(3, hornLRot);
    setcolor(armorMain);
    int hornLL0x = 0, hornLL0y = 0, hornLL1x = 0, hornLL1y = 0;
    rotatePoint((float)(headX-S(22)), (float)(headY-S(5)), headPivotX, headPivotY, headCos, headSin, hornLL0x, hornLL0y);
    rotatePoint((float)(headX-S(29)), (float)(headY-S(22)), headPivotX, headPivotY, headCos, headSin, hornLL1x, hornLL1y);
    bresenhamLine(hornLL0x, hornLL0y, hornLL1x, hornLL1y); 
    setcolor(outlineColor);

    int hornR[] = {headX+S(22), headY-S(5), headX+S(38), headY-S(35), headX+S(15), headY-S(22)};
    int hornRRot[6];
    buildRotatedPoly(hornR, 3, headPivotX, headPivotY, headCos, headSin, hornRRot);
    fillpoly(3, hornRRot); drawpoly(3, hornRRot);
    setcolor(armorMain);
    int hornRL0x = 0, hornRL0y = 0, hornRL1x = 0, hornRL1y = 0;
    rotatePoint((float)(headX+S(22)), (float)(headY-S(5)), headPivotX, headPivotY, headCos, headSin, hornRL0x, hornRL0y);
    rotatePoint((float)(headX+S(29)), (float)(headY-S(22)), headPivotX, headPivotY, headCos, headSin, hornRL1x, hornRL1y);
    bresenhamLine(hornRL0x, hornRL0y, hornRL1x, hornRL1y);
    setcolor(outlineColor);

    // chóp mũ có ngọc
    int crest[] = {headX-S(2), headY-S(23), headX+S(10), headY-S(42), headX+S(14), headY-S(23)};
    setfillstyle(SOLID_FILL, armorMain);
    int crestRot[6];
    buildRotatedPoly(crest, 3, headPivotX, headPivotY, headCos, headSin, crestRot);
    fillpoly(3, crestRot); drawpoly(3, crestRot);

    setcolor(BLACK);
    int gemX1 = 0, gemY1 = 0;
    rotatePoint((float)(headX+S(6)), (float)(headY - S(18)), headPivotX, headPivotY, headCos, headSin, gemX1, gemY1);
    midpointEllipse(gemX1, gemY1, S(7), S(9));
    setcolor(goldMain);
    midpointFilledEllipse(gemX1, gemY1, S(6), S(8));
    setcolor(goldLight);
    midpointEllipse(gemX1, gemY1, S(6), S(8));
    setcolor(gemColor);
    midpointFilledEllipse(gemX1, gemY1, S(4), S(6));

    // khe nhìn
    setfillstyle(SOLID_FILL, BLACK);
    int visor[] = {
        headX - S(8), headY,
        headX - S(10), headY + S(10),
        headX + S(2),  headY + S(20),
        headX + S(12), headY + S(12), 
        headX + S(20), headY + S(20),
        headX + S(25), headY + S(8),
        headX + S(22), headY
    };
    int visorRot[14];
    buildRotatedPoly(visor, 7, headPivotX, headPivotY, headCos, headSin, visorRot);
    fillpoly(7, visorRot);
    
    // viền khe nhìn (xám nhạt)
    setcolor(COLOR(180, 180, 180));
    setlinestyle(SOLID_LINE, 0, thickBold);
    for(int i=0; i<6; i++) {
        bresenhamLine(visorRot[i*2], visorRot[i*2+1], visorRot[i*2+2], visorRot[i*2+3]);
    }
    bresenhamLine(visorRot[12], visorRot[13], visorRot[0], visorRot[1]);
    
    // đôi mắt phát sáng
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickNormal);
    setfillstyle(SOLID_FILL, eyeColor);
    
    int eyeL[] = {headX - S(5), headY + S(6), headX + S(4), headY + S(8), headX, headY + S(12)};
    int eyeLRot[6];
    buildRotatedPoly(eyeL, 3, headPivotX, headPivotY, headCos, headSin, eyeLRot);
    fillpoly(3, eyeLRot);
    
    int eyeR[] = {headX + S(23), headY + S(6), headX + S(15), headY + S(8), headX + S(19), headY + S(11)};
    int eyeRRot[6];
    buildRotatedPoly(eyeR, 3, headPivotX, headPivotY, headCos, headSin, eyeRRot);
    fillpoly(3, eyeRRot);

    setcolor(glowColor);
    drawpoly(3, eyeLRot);
    drawpoly(3, eyeRRot);

    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
