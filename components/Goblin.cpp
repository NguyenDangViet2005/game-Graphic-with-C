#ifndef GOBLIN_H
#define GOBLIN_H

#include <graphics.h>
#include <math.h>

#ifndef S
#define S(val) ((int)((val) * scale))
#endif

// Hàm vẽ đa giác tô màu có viền chi tiết
static void drawGoblinDetailedPoly(int numPoints, int* points, int fillColor, int outlineColor, int thickness = 2) {
    setfillstyle(SOLID_FILL, fillColor);
    fillpoly(numPoints, points);
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickness);
    drawpoly(numPoints, points);
    line(points[(numPoints - 1) * 2], points[(numPoints - 1) * 2 + 1], points[0], points[1]);
}

// Vẽ Goblin: Bỏ bóng chân, chuyển động 2 chân chạy, khôi phục rìu 1 lưỡi và thêm vệt chém vòng cung
void drawGoblin(int x, int y, float scale, float timeSec, float attackProgress = 0.0f) {
    // Hoạt ảnh nhấp nhô cơ thể khi chạy
    float wave = sin(timeSec * 12.0f); // Tần số chạy nhanh
    int bounceY = S(abs(wave) * 2.0f);
    
    // Tính toán góc vung chân khi chạy (2 chân nghịch pha nhau)
    float legSwing = sin(timeSec * 12.0f);
    int swingXL = (int)(legSwing * S(9));
    int swingYL = (legSwing > 0.0f) ? (int)(legSwing * S(5)) : 0;
    
    int swingXR = (int)(-legSwing * S(9));
    int swingYR = (legSwing < 0.0f) ? (int)(-legSwing * S(5)) : 0;
    
    // Bảng màu sắc
    int skinGreen = COLOR(135, 195, 45);        // Da xanh sáng
    int skinGreenDark = COLOR(90, 135, 25);     // Da xanh tối
    int skinGreenHighlight = COLOR(175, 225, 75); // Vùng sáng da
    int loinclothRed = COLOR(205, 50, 35);       // Khố đỏ
    int loinclothRedDark = COLOR(140, 25, 15);   // Khố bóng tối
    int bootBrown = COLOR(95, 65, 45);           // Ủng da nâu sáng
    int bootBrownDark = COLOR(60, 40, 25);       // Ủng da nâu tối
    int bootSole = COLOR(40, 25, 15);            // Đế ủng
    int handleBrown = COLOR(120, 45, 40);        // Cán đỏ sẫm
    int handleWrap = COLOR(170, 130, 90);        // Dây quấn cán rìu
    int goldColor = COLOR(245, 190, 35);         // Khóa chốt vàng gắn rìu
    int metalGrey = COLOR(205, 210, 215);        // Lưỡi rìu xám bạc
    int metalDark = COLOR(125, 130, 135);        // Lưỡi rìu bóng tối
    int metalEdge = COLOR(245, 250, 255);        // Rìa lưỡi rìu sáng

    // Tâm khớp nối xoay của rìu (Ngang ngực)
    int cx = x - S(42);
    int cy = y - S(46) + bounceY;

    // Tính toán góc bổ rìu (Bình thường: 45 độ. Khi bổ: xoay xuống chéo đất)
    float swingOffset = 0.0f;
    if (attackProgress > 0.0f && attackProgress < 1.0f) {
        swingOffset = sin(attackProgress * 3.14159265f) * 65.0f;
    }
    float rad = (45.0f - swingOffset) * 3.14159265f / 180.0f;
    float cA = cos(rad);
    float sA = sin(rad);

    // Macro xoay tọa độ điểm nội bộ (lx, ly) quanh tâm (cx, cy)
    #define ROTX(lx, ly) (cx + (int)((lx) * cA - (ly) * sA))
    #define ROTY(lx, ly) (cy + (int)((lx) * sA + (ly) * cA))

    // Tọa độ 2 bàn tay bám trên cán rìu theo góc xoay
    int handLX = ROTX(S(42), 0);
    int handLY = ROTY(S(42), 0);
    int handRX = ROTX(S(15), 0);
    int handRY = ROTY(S(15), 0);

    // --- 2. CHÂN & ỦNG PHÍA SAU (Chân trái - Z-index dưới bụng) ---
    int legLY = y - S(10) - swingYL;
    int thighLPts[] = {
        x + S(10) + swingXL/2, y - S(25) + bounceY / 2,
        x + S(18) + swingXL/2, y - S(25) + bounceY / 2,
        x + S(16) + swingXL, legLY,
        x + S(8) + swingXL, legLY
    };
    drawGoblinDetailedPoly(4, thighLPts, skinGreenDark, BLACK, 2);
    
    int bootLPts[] = {
        x + S(7) + swingXL, legLY,
        x + S(17) + swingXL, legLY,
        x + S(20) + swingXL, y - S(1) - swingYL,
        x + S(9) + swingXL, y - S(1) - swingYL
    };
    drawGoblinDetailedPoly(4, bootLPts, bootBrownDark, BLACK, 2);
    
    int soleLPts[] = {
        x + S(8) + swingXL, y - S(1) - swingYL,
        x + S(21) + swingXL, y - S(1) - swingYL,
        x + S(19) + swingXL, y + S(2) - swingYL,
        x + S(6) + swingXL, y + S(2) - swingYL
    };
    drawGoblinDetailedPoly(4, soleLPts, bootSole, BLACK, 1);

    // --- 3. CHÂN & ỦNG PHÍA TRƯỚC (Chân phải - Z-index dưới bụng) ---
    int legRY = y - S(10) - swingYR;
    int thighRPts[] = {
        x - S(18) + swingXR/2, y - S(25) + bounceY / 2,
        x - S(10) + swingXR/2, y - S(25) + bounceY / 2,
        x - S(8) + swingXR, legRY,
        x - S(16) + swingXR, legRY
    };
    drawGoblinDetailedPoly(4, thighRPts, skinGreen, BLACK, 2);
    
    int bootRPts[] = {
        x - S(17) + swingXR, legRY,
        x - S(7) + swingXR, legRY,
        x - S(5) + swingXR, y - S(1) - swingYR,
        x - S(15) + swingXR, y - S(1) - swingYR
    };
    drawGoblinDetailedPoly(4, bootRPts, bootBrown, BLACK, 2);
    
    int soleRPts[] = {
        x - S(16) + swingXR, y - S(1) - swingYR,
        x - S(4) + swingXR, y - S(1) - swingYR,
        x - S(6) + swingXR, y + S(2) - swingYR,
        x - S(18) + swingXR, y + S(2) - swingYR
    };
    drawGoblinDetailedPoly(4, soleRPts, bootSole, BLACK, 1.5);

    // --- 4. TAY SAU (Bên phải cơ thể, nối từ sườn phải chạy xuống nắm cán rìu chéo dưới) ---
    int forearmLPts[] = {
        x + S(14), y - S(38) + bounceY,
        x + S(18), y - S(34) + bounceY,
        handLX + S(4), handLY + S(4),
        handLX - S(4), handLY - S(4)
    };
    drawGoblinDetailedPoly(4, forearmLPts, skinGreenDark, BLACK, 2);

    // --- 5. RÌU CHIẾN DÀI HƠN NGHIÊNG 45 ĐỘ (Chỉa chéo từ dưới lên trên bên trái) ---
    // Cán rìu nghiêng 45 độ (Tọa độ X và Y thay đổi lượng bằng nhau)
    // Cán rìu nằm gọn trong tay, kết thúc ngay tại vị trí bàn tay nắm
    int rHandlePts[] = {
        ROTX(-S(16), -S(2)), ROTY(-S(16), -S(2)),
        ROTX(-S(16),  S(2)), ROTY(-S(16),  S(2)),
        ROTX( S(42),  S(2)), ROTY( S(42),  S(2)),
        ROTX( S(42), -S(2)), ROTY( S(42), -S(2))
    };
    drawGoblinDetailedPoly(4, rHandlePts, handleBrown, BLACK, 2);

    // Dây quấn cán rìu chéo
    setcolor(handleWrap);
    setlinestyle(SOLID_LINE, 0, 2);
    for (int offset = 10; offset <= 34; offset += 8) {
        line(ROTX(S(offset), -S(2)), ROTY(S(offset), -S(2)),
             ROTX(S(offset) + S(3), S(2)), ROTY(S(offset) + S(3), S(2)));
    }

    // Khớp chốt khóa vàng ở đầu rìu
    int rGoldJointPts[] = {
        ROTX(-S(7), -S(6)), ROTY(-S(7), -S(6)),
        ROTX( S(3), -S(6)), ROTY( S(3), -S(6)),
        ROTX( S(3),  S(6)), ROTY( S(3),  S(6)),
        ROTX(-S(7),  S(6)), ROTY(-S(7),  S(6))
    };
    drawGoblinDetailedPoly(4, rGoldJointPts, goldColor, BLACK, 2);

    // Lưỡi rìu TRÊN (Hướng lên phía +Y)
    int bladeUpPts[] = {
        ROTX(-S(12), S(4)), ROTY(-S(12), S(4)),
        ROTX(-S(22), S(28)), ROTY(-S(22), S(28)),
        ROTX(-S(5), S(32)), ROTY(-S(5), S(32)),
        ROTX(S(2), S(28)), ROTY(S(2), S(28)),
        ROTX(-S(2), S(4)), ROTY(-S(2), S(4))
    };
    drawGoblinDetailedPoly(5, bladeUpPts, metalGrey, BLACK, 2);

    // Viền sắc bén của lưỡi trên
    int bladeUpEdgePts[] = {
        ROTX(-S(22), S(28)), ROTY(-S(22), S(28)),
        ROTX(-S(5), S(32)), ROTY(-S(5), S(32)),
        ROTX(S(2), S(28)), ROTY(S(2), S(28)),
        ROTX(S(1), S(24)), ROTY(S(1), S(24)),
        ROTX(-S(5), S(28)), ROTY(-S(5), S(28)),
        ROTX(-S(18), S(24)), ROTY(-S(18), S(24))
    };
    drawGoblinDetailedPoly(6, bladeUpEdgePts, metalEdge, BLACK, 1);

    // Lưỡi rìu DƯỚI (Hướng xuống phía -Y)
    int bladeDownPts[] = {
        ROTX(-S(12), -S(4)), ROTY(-S(12), -S(4)),
        ROTX(-S(22), -S(28)), ROTY(-S(22), -S(28)),
        ROTX(-S(5), -S(32)), ROTY(-S(5), -S(32)),
        ROTX(S(2), -S(28)), ROTY(S(2), -S(28)),
        ROTX(-S(2), -S(4)), ROTY(-S(2), -S(4))
    };
    drawGoblinDetailedPoly(5, bladeDownPts, metalGrey, BLACK, 2);

    // Bóng tối của lưỡi dưới
    int bladeDownShadowPts[] = {
        ROTX(-S(12), -S(4)), ROTY(-S(12), -S(4)),
        ROTX(-S(2), -S(4)), ROTY(-S(2), -S(4)),
        ROTX(S(2), -S(28)), ROTY(S(2), -S(28)),
        ROTX(-S(5), -S(32)), ROTY(-S(5), -S(32))
    };
    drawGoblinDetailedPoly(4, bladeDownShadowPts, metalDark, BLACK, 1);

    // Viền sắc bén của lưỡi dưới
    int bladeDownEdgePts[] = {
        ROTX(-S(22), -S(28)), ROTY(-S(22), -S(28)),
        ROTX(-S(5), -S(32)), ROTY(-S(5), -S(32)),
        ROTX(S(2), -S(28)), ROTY(S(2), -S(28)),
        ROTX(S(1), -S(24)), ROTY(S(1), -S(24)),
        ROTX(-S(5), -S(28)), ROTY(-S(5), -S(28)),
        ROTX(-S(18), -S(24)), ROTY(-S(18), -S(24))
    };
    drawGoblinDetailedPoly(6, bladeDownEdgePts, metalEdge, BLACK, 1);

    // Mũi nhọn đâm chĩa ở đầu rìu
    int rFrontSpikePts[] = {
        ROTX(-S(16), -S(3)), ROTY(-S(16), -S(3)),
        ROTX(-S(24), -S(4)), ROTY(-S(24), -S(4)),
        ROTX(-S(20), 0), ROTY(-S(20), 0),
        ROTX(-S(24), S(4)), ROTY(-S(24), S(4)),
        ROTX(-S(16), S(3)), ROTY(-S(16), S(3))
    };
    drawGoblinDetailedPoly(5, rFrontSpikePts, metalGrey, BLACK, 1.5);

    // Bàn tay sau nắm cán rìu chéo dưới
    setfillstyle(SOLID_FILL, skinGreenDark);
    fillellipse(handLX, handLY, S(5), S(5));
    setcolor(BLACK);
    ellipse(handLX, handLY, 0, 360, S(5), S(5));

    // --- 5. THÂN MÌNH GOBLIN (Z-INDEX TRÊN CHÂN) ---
    int bodyY = y - S(32) + bounceY;
    setfillstyle(SOLID_FILL, skinGreenDark);
    fillellipse(x, bodyY, S(23), S(19));
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 2);
    ellipse(x, bodyY, 0, 360, S(23), S(19));
    
    // Vùng bụng nổi bật (Highlight che phủ đùi chân bên dưới)
    setfillstyle(SOLID_FILL, skinGreenHighlight);
    fillellipse(x - S(6), bodyY + S(2), S(12), S(10));
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    line(x - S(14), bodyY - S(4), x + S(4), bodyY - S(4));
    line(x - S(6), bodyY - S(4), x - S(6), bodyY + S(8));

    // --- 6. KHỐ ĐỎ RÁCH RƯỚI ---
    int loinPts[] = {
        x - S(18), y - S(22) + bounceY,
        x + S(18), y - S(22) + bounceY,
        x + S(13), y - S(8) + bounceY,
        x + S(3), y - S(2) + bounceY,
        x - S(7), y - S(11) + bounceY,
        x - S(15), y - S(5) + bounceY
    };
    drawGoblinDetailedPoly(6, loinPts, loinclothRed, BLACK, 2);
    
    int loinShadowPts[] = {
        x - S(7), y - S(11) + bounceY,
        x - S(15), y - S(5) + bounceY,
        x - S(10), y - S(18) + bounceY,
    };
    drawGoblinDetailedPoly(3, loinShadowPts, loinclothRedDark, BLACK, 1);

    // --- 7. ĐẦU GOBLIN ---
    int headX = x - S(4);
    int headY = y - S(59) + bounceY;
    setfillstyle(SOLID_FILL, skinGreen);
    fillellipse(headX, headY, S(28), S(23));
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 2);
    ellipse(headX, headY, 0, 360, S(28), S(23));

    // --- 8. HAI TAI NHỌN DÀI ---
    // Tai Trái
    int earLPts[] = {
        headX - S(18), headY - S(12),
        headX - S(39), headY - S(33),
        headX - S(25), headY
    };
    drawGoblinDetailedPoly(3, earLPts, skinGreen, BLACK, 2);
    int earLInnerPts[] = {
        headX - S(20), headY - S(13),
        headX - S(35), headY - S(29),
        headX - S(25), headY - S(3)
    };
    drawGoblinDetailedPoly(3, earLInnerPts, skinGreenDark, BLACK, 1);
    
    // Tai Phải
    int earRPts[] = {
        headX + S(18), headY - S(12),
        headX + S(37), headY - S(31),
        headX + S(25), headY
    };
    drawGoblinDetailedPoly(3, earRPts, skinGreen, BLACK, 2);
    int earRInnerPts[] = {
        headX + S(20), headY - S(13),
        headX + S(33), headY - S(27),
        headX + S(25), headY - S(3)
    };
    drawGoblinDetailedPoly(3, earRInnerPts, skinGreenDark, BLACK, 1);

    // --- 9. ĐÔI MẮT XẾCH GIẬN DỮ ---
    int eyeLPts[] = {
        headX - S(22), headY - S(5),
        headX - S(10), headY - S(4),
        headX - S(15), headY - S(10)
    };
    drawGoblinDetailedPoly(3, eyeLPts, WHITE, BLACK, 2);
    int eyeRPts[] = {
        headX - S(6), headY - S(5),
        headX + S(6), headY - S(4),
        headX + S(1), headY - S(10)
    };
    drawGoblinDetailedPoly(3, eyeRPts, WHITE, BLACK, 2);
    
    setfillstyle(SOLID_FILL, RED);
    fillellipse(headX - S(16), headY - S(6), S(2), S(2));
    fillellipse(headX, headY - S(6), S(2), S(2));
    
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);
    line(headX - S(24), headY - S(12), headX - S(8), headY - S(9));
    line(headX - S(8), headY - S(9), headX + S(8), headY - S(11));

    // --- 10. MŨI TO TRÒN ---
    int noseX = headX - S(16);
    int noseY = headY + S(3);
    setfillstyle(SOLID_FILL, skinGreen);
    fillellipse(noseX, noseY, S(10), S(7));
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 2);
    ellipse(noseX, noseY, 0, 360, S(10), S(7));

    // --- 11. HAI CHIẾC RĂNG NANH TRẮNG BẮT CHÉO ---
    int fang1Pts[] = {
        headX - S(10), headY + S(12),
        headX - S(6), headY + S(12),
        headX - S(8), headY + S(7)
    };
    drawGoblinDetailedPoly(3, fang1Pts, WHITE, BLACK, 2);
    int fang2Pts[] = {
        headX - S(4), headY + S(12),
        headX + S(1), headY + S(12),
        headX - S(1), headY + S(6)
    };
    drawGoblinDetailedPoly(3, fang2Pts, WHITE, BLACK, 2);

    // --- 12. TAY TRƯỚC (Bên trái cơ thể, nối từ sườn trái chạy tới bàn tay nắm cán rìu chéo trên) ---
    int forearmRPts[] = {
        x - S(22), y - S(35) + bounceY,
        x - S(18), y - S(30) + bounceY,
        handRX + S(3), handRY + S(3),
        handRX - S(3), handRY - S(3)
    };
    drawGoblinDetailedPoly(4, forearmRPts, skinGreen, BLACK, 2);
    
    // Bàn tay trước nắm chặt cán rìu
    setfillstyle(SOLID_FILL, skinGreen);
    fillellipse(handRX, handRY, S(7), S(7));
    setcolor(BLACK);
    ellipse(handRX, handRY, 0, 360, S(7), S(7));
    
    fillellipse(handRX - S(2), handRY - S(2), S(3), S(3));
    fillellipse(handRX + S(1), handRY - S(3), S(3), S(3));
    fillellipse(handRX + S(3), handRY - S(1), S(3), S(3));

    // --- 14. TAY BÊN PHẢI MÀN HÌNH (Thêm mới bên phải cơ thể, nối vào viền bụng) ---
    int handRightX = x + S(23);
    int handRightY = y - S(24) + bounceY;
    int forearmRightPts[] = {
        x + S(16), y - S(35) + bounceY,
        x + S(20), y - S(29) + bounceY,
        handRightX + S(2), handRightY + S(2),
        handRightX - S(2), handRightY - S(2)
    };
    drawGoblinDetailedPoly(4, forearmRightPts, skinGreen, BLACK, 2);
    
    // Bàn tay phải màn hình
    setfillstyle(SOLID_FILL, skinGreen);
    fillellipse(handRightX, handRightY, S(6), S(6));
    setcolor(BLACK);
    ellipse(handRightX, handRightY, 0, 360, S(6), S(6));
    
    // Ngón tay
    fillellipse(handRightX - S(1), handRightY + S(3), S(2.5), S(2.5));
    fillellipse(handRightX + S(2), handRightY + S(2), S(2.5), S(2.5));

    // --- 13. HIỆU ỨNG VỆT CHÉM VÒNG CUNG (Vung rìu chém tựa Explorer) ---
    if (attackProgress > 0.0f && attackProgress < 1.0f) {
        // Vẽ vệt chém trắng/xám bán trong suốt dạng vòng cung phía trước rìu
        setcolor(COLOR(230, 235, 245));
        setlinestyle(SOLID_LINE, 0, S(4));
        // Tâm cung nằm ở cx, cy, bán kính quét rộng S(55) -> S(65)
        arc(cx, cy, 140, 230, S(58));
        setlinestyle(SOLID_LINE, 0, S(2));
        setcolor(WHITE);
        arc(cx, cy, 150, 220, S(53));
    }

    // Khôi phục kiểu vẽ nét mặc định
    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
