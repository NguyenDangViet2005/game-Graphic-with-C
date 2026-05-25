#ifndef EXPLORER_MIRRORED_H
#define EXPLORER_MIRRORED_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"

#define S(val) ((int)((val) * scale)) // macro scale tọa do

static void rotatePointMirrored(float x, float y, float cx, float cy, float cosA, float sinA, int& outX, int& outY) {
    float tx = x - cx;
    float ty = y - cy;
    float rx = tx * cosA - ty * sinA;
    float ry = tx * sinA + ty * cosA;
    outX = (int)(rx + cx);
    outY = (int)(ry + cy);
}

static void buildRotatedPolyMirrored(const int* pts, int count, float cx, float cy, float cosA, float sinA, int* outPts) {
    for (int i = 0; i < count; i++) {
        rotatePointMirrored((float)pts[i * 2], (float)pts[i * 2 + 1], cx, cy, cosA, sinA, outPts[i * 2], outPts[i * 2 + 1]);
    }
}

void drawExplorerMirrored(int x, int y, float scale, float armAngle, float headAngle, int weaponType = 0, float slashProgress = 0.0f) {
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
    
    if (weaponType == 0) {
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
    } else {
        // Khi dung kiem, ve bao kiem cheo don gian sau lung
        setcolor(armorDark);
        setlinestyle(SOLID_LINE, 0, thickBold);
        bresenhamLine(quiverX, quiverY, quiverX + S(10), quiverY - S(25));
        setlinestyle(SOLID_LINE, 0, thickNormal);
        setcolor(outlineColor);
    }

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

    if (weaponType == 1 && slashProgress > 0.0f && slashProgress < 1.0f) {
        armAngle = -1.2f + slashProgress * 2.7f;
    }
    // tay phai cam cung (xoay quanh khop)
    float armCos = (float)cos(armAngle);
    float armSin = (float)sin(armAngle);
    float armPivotX = (float)(x - S(25));
    float armPivotY = (float)(y - S(35));
    setfillstyle(SOLID_FILL, armorMain);
    int armR[] = {x-S(15), y-S(40), x-S(30), y-S(40), x-S(40), y-S(30), x-S(25), y-S(30)};
    int armRRot[8];
    buildRotatedPolyMirrored(armR, 4, armPivotX, armPivotY, armCos, armSin, armRRot);
    fillpoly(4, armRRot); drawpoly(4, armRRot);

    // nam tay phai
    setfillstyle(SOLID_FILL, armorDark);
    int handX = 0;
    int handY = 0;
    rotatePointMirrored((float)(x - S(40)), (float)(y - S(30)), armPivotX, armPivotY, armCos, armSin, handX, handY);
    midpointFilledCircle(handX, handY, S(7));
    midpointCircle(handX, handY, S(7));

    if (weaponType == 0) {
        // cung ten
        int bowX = x - S(40);
        int bowY = y - S(30);
        int bowXr = 0;
        int bowYr = 0;
        rotatePointMirrored((float)bowX, (float)bowY, armPivotX, armPivotY, armCos, armSin, bowXr, bowYr);
        float bowAngleOffset = armAngle * 180.0f / 3.1415926f;
        setlinestyle(SOLID_LINE, 0, thickBold);
        
        setcolor(goldMain);
        arc(bowXr + S(10), bowYr, (int)(100 + bowAngleOffset), (int)(260 + bowAngleOffset), S(25));
        setcolor(armorDark);
        arc(bowXr + S(12), bowYr, (int)(105 + bowAngleOffset), (int)(255 + bowAngleOffset), S(23));
        
        // tay cam cung
        setfillstyle(SOLID_FILL, armorDark);
        bar(bowXr-S(5), bowYr-S(6), bowXr+S(2), bowYr+S(6));
        setcolor(outlineColor);
        rectangle(bowXr-S(5), bowYr-S(6), bowXr+S(2), bowYr+S(6));
        setcolor(gemColor);
        midpointFilledCircle(bowXr-S(1), bowYr, S(2));

        // day cung
        setcolor(glowColor);
        setlinestyle(SOLID_LINE, 0, thickNormal); 
        int lineA0x = 0, lineA0y = 0, lineA1x = 0, lineA1y = 0;
        int lineB0x = 0, lineB0y = 0, lineB1x = 0, lineB1y = 0;
        rotatePointMirrored((float)(bowX + S(4)), (float)(bowY - S(24)), armPivotX, armPivotY, armCos, armSin, lineA0x, lineA0y);
        rotatePointMirrored((float)(bowX + S(14)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, lineA1x, lineA1y);
        rotatePointMirrored((float)(bowX + S(4)), (float)(bowY + S(24)), armPivotX, armPivotY, armCos, armSin, lineB0x, lineB0y);
        rotatePointMirrored((float)(bowX + S(14)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, lineB1x, lineB1y);
        bresenhamLine(lineA0x, lineA0y, lineA1x, lineA1y);
        bresenhamLine(lineB0x, lineB0y, lineB1x, lineB1y);
        
        // mui ten nang luong
        setcolor(goldLight);
        setlinestyle(SOLID_LINE, 0, thickBold);
        int arrowLx = 0, arrowLy = 0, arrowRx = 0, arrowRy = 0;
        rotatePointMirrored((float)(bowX + S(14)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, arrowLx, arrowLy);
        rotatePointMirrored((float)(bowX - S(16)), (float)(bowY), armPivotX, armPivotY, armCos, armSin, arrowRx, arrowRy);
        bresenhamLine(arrowLx, arrowLy, arrowRx, arrowRy);
        
        // dau mui ten
        setfillstyle(SOLID_FILL, eyeColor);
        int arrowHead[] = {bowX-S(16), bowY, bowX-S(10), bowY-S(4), bowX-S(13), bowY, bowX-S(10), bowY+S(4)};
        int arrowHeadRot[8];
        buildRotatedPolyMirrored(arrowHead, 4, armPivotX, armPivotY, armCos, armSin, arrowHeadRot);
        fillpoly(4, arrowHeadRot);
        setcolor(glowColor);
        drawpoly(4, arrowHeadRot);

        setlinestyle(SOLID_LINE, 0, thickNormal); 
        setcolor(outlineColor);
    } else {
        // Vẽ kiếm năng lượng mới
        // Hilt (Chuôi kiếm)
        int hilt[] = {
            x - S(26), y - S(32),
            x - S(40), y - S(32),
            x - S(40), y - S(28),
            x - S(26), y - S(28)
        };
        int hiltRot[8];
        buildRotatedPolyMirrored(hilt, 4, armPivotX, armPivotY, armCos, armSin, hiltRot);
        setfillstyle(SOLID_FILL, armorDark);
        fillpoly(4, hiltRot);
        setcolor(outlineColor);
        drawpoly(4, hiltRot);

        // Guard (Chắn kiếm)
        int guard[] = {
            x - S(39), y - S(43),
            x - S(42), y - S(43),
            x - S(42), y - S(17),
            x - S(39), y - S(17)
        };
        int guardRot[8];
        buildRotatedPolyMirrored(guard, 4, armPivotX, armPivotY, armCos, armSin, guardRot);
        setfillstyle(SOLID_FILL, goldMain);
        fillpoly(4, guardRot);
        setcolor(outlineColor);
        drawpoly(4, guardRot);

        // Blade Outer (Lưỡi kiếm phát sáng)
        int blade[] = {
            x - S(41), y - S(34),
            x - S(92), y - S(34),
            x - S(99), y - S(30),
            x - S(92), y - S(26),
            x - S(41), y - S(26)
        };
        int bladeRot[10];
        buildRotatedPolyMirrored(blade, 5, armPivotX, armPivotY, armCos, armSin, bladeRot);
        setfillstyle(SOLID_FILL, COLOR(0, 220, 255)); // Cyan
        fillpoly(5, bladeRot);
        setcolor(COLOR(100, 240, 255));
        drawpoly(5, bladeRot);

        // Blade Inner Core (Lõi trắng)
        int core[] = {
            x - S(42), y - S(31),
            x - S(89), y - S(31),
            x - S(94), y - S(30),
            x - S(89), y - S(29),
            x - S(42), y - S(29)
        };
        int coreRot[10];
        buildRotatedPolyMirrored(core, 5, armPivotX, armPivotY, armCos, armSin, coreRot);
        setfillstyle(SOLID_FILL, WHITE);
        fillpoly(5, coreRot);

        setlinestyle(SOLID_LINE, 0, thickNormal); 
        setcolor(outlineColor);
    }

    // dau va mu
    int headX = x;
    int headY = y - S(65);
    float headCos = (float)cos(headAngle);
    float headSin = (float)sin(headAngle);
    float headPivotX = (float)headX;
    float headPivotY = (float)headY;

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
    int helmetRot[16];
    buildRotatedPolyMirrored(helmet, 8, headPivotX, headPivotY, headCos, headSin, helmetRot);
    fillpoly(8, helmetRot); drawpoly(8, helmetRot);

    // giap cam
    int helmetBottom[] = {
        headX + S(22), headY + S(15),
        headX + S(15), headY + S(30),
        headX - S(15), headY + S(30),
        headX - S(22), headY + S(15),
        headX - S(10), headY + S(25),
        headX + S(10), headY + S(25)
    };
    int helmetBottomRot[12];
    buildRotatedPolyMirrored(helmetBottom, 6, headPivotX, headPivotY, headCos, headSin, helmetBottomRot);
    fillpoly(6, helmetBottomRot); drawpoly(6, helmetBottomRot);

    // cap sung
    setfillstyle(SOLID_FILL, armorDark);
    int hornL[] = {headX+S(22), headY-S(5), headX+S(38), headY-S(35), headX+S(15), headY-S(22)};
    int hornLRot[6];
    buildRotatedPolyMirrored(hornL, 3, headPivotX, headPivotY, headCos, headSin, hornLRot);
    fillpoly(3, hornLRot); drawpoly(3, hornLRot);
    setcolor(armorMain);
    int hornLL0x = 0, hornLL0y = 0, hornLL1x = 0, hornLL1y = 0;
    rotatePointMirrored((float)(headX+S(22)), (float)(headY-S(5)), headPivotX, headPivotY, headCos, headSin, hornLL0x, hornLL0y);
    rotatePointMirrored((float)(headX+S(29)), (float)(headY-S(22)), headPivotX, headPivotY, headCos, headSin, hornLL1x, hornLL1y);
    bresenhamLine(hornLL0x, hornLL0y, hornLL1x, hornLL1y); 
    setcolor(outlineColor);

    int hornR[] = {headX-S(22), headY-S(5), headX-S(38), headY-S(35), headX-S(15), headY-S(22)};
    int hornRRot[6];
    buildRotatedPolyMirrored(hornR, 3, headPivotX, headPivotY, headCos, headSin, hornRRot);
    fillpoly(3, hornRRot); drawpoly(3, hornRRot);
    setcolor(armorMain);
    int hornRL0x = 0, hornRL0y = 0, hornRL1x = 0, hornRL1y = 0;
    rotatePointMirrored((float)(headX-S(22)), (float)(headY-S(5)), headPivotX, headPivotY, headCos, headSin, hornRL0x, hornRL0y);
    rotatePointMirrored((float)(headX-S(29)), (float)(headY-S(22)), headPivotX, headPivotY, headCos, headSin, hornRL1x, hornRL1y);
    bresenhamLine(hornRL0x, hornRL0y, hornRL1x, hornRL1y);
    setcolor(outlineColor);

    // chop mu co ngoc
    int crest[] = {headX+S(2), headY-S(23), headX-S(10), headY-S(42), headX-S(14), headY-S(23)};
    setfillstyle(SOLID_FILL, armorMain);
    int crestRot[6];
    buildRotatedPolyMirrored(crest, 3, headPivotX, headPivotY, headCos, headSin, crestRot);
    fillpoly(3, crestRot); drawpoly(3, crestRot);

    setcolor(BLACK);
    int gemX1 = 0, gemY1 = 0;
    rotatePointMirrored((float)(headX-S(6)), (float)(headY - S(18)), headPivotX, headPivotY, headCos, headSin, gemX1, gemY1);
    midpointEllipse(gemX1, gemY1, S(7), S(9));
    setcolor(goldMain);
    midpointFilledEllipse(gemX1, gemY1, S(6), S(8));
    setcolor(goldLight);
    midpointEllipse(gemX1, gemY1, S(6), S(8));
    setcolor(gemColor);
    midpointFilledEllipse(gemX1, gemY1, S(4), S(6));

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
    int visorRot[14];
    buildRotatedPolyMirrored(visor, 7, headPivotX, headPivotY, headCos, headSin, visorRot);
    fillpoly(7, visorRot);
    
    // vien khe nhin (xam nhat)
    setcolor(COLOR(180, 180, 180));
    setlinestyle(SOLID_LINE, 0, thickBold);
    for(int i=0; i<6; i++) {
        bresenhamLine(visorRot[i*2], visorRot[i*2+1], visorRot[i*2+2], visorRot[i*2+3]);
    }
    bresenhamLine(visorRot[12], visorRot[13], visorRot[0], visorRot[1]);
    
    // doi mat phat sang
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickNormal);
    setfillstyle(SOLID_FILL, eyeColor);
    
    int eyeL[] = {headX + S(5), headY + S(6), headX - S(4), headY + S(8), headX, headY + S(12)};
    int eyeLRot[6];
    buildRotatedPolyMirrored(eyeL, 3, headPivotX, headPivotY, headCos, headSin, eyeLRot);
    fillpoly(3, eyeLRot);
    
    int eyeR[] = {headX - S(23), headY + S(6), headX - S(15), headY + S(8), headX - S(19), headY + S(11)};
    int eyeRRot[6];
    buildRotatedPolyMirrored(eyeR, 3, headPivotX, headPivotY, headCos, headSin, eyeRRot);
    fillpoly(3, eyeRRot);

    setcolor(glowColor);
    drawpoly(3, eyeLRot);
    drawpoly(3, eyeRRot);

    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
