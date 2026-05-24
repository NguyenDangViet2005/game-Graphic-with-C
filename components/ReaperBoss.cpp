#ifndef REAPER_BOSS_H
#define REAPER_BOSS_H

#include <graphics.h>
#include <math.h>
#include "../configs/Config.cpp"
#include "../algorithms/index.cpp"

// Macro scale tọa độ
#define S(val) ((int)((val) * scale))

// Hàm hỗ trợ vẽ đa giác tô màu có viền khép kín
static void drawFilledPoly(int numPoints, int* points, int fillColor, int outlineColor, int thickness = 1) {
    setfillstyle(SOLID_FILL, fillColor);
    fillpoly(numPoints, points);
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickness);
    drawpoly(numPoints, points);
    // Đảm bảo đa giác được khép kín hoàn toàn
    line(points[(numPoints - 1) * 2], points[(numPoints - 1) * 2 + 1], points[0], points[1]);
}

// Hàm vẽ linh hồn nhỏ dạng gào thét u ám nâng cao (Screaming Souls)
static void drawMiniGhost(int gx, int gy, float scale, float timeSec, int faceRight) {
    int borderGreen = COLOR(40, 85, 30);
    int bodyGreen = COLOR(155, 235, 120);
    int eyeColor = COLOR(10, 20, 10);
    
    // Đuôi vẫy uốn lượn sinh động theo thời gian
    int tailWiggleX = (int)(sin(timeSec * 7.5f) * S(5));
    int tailWiggleY = (int)(cos(timeSec * 5.0f) * S(3));
    
    // Khai báo tọa độ cho đuôi ma chi tiết hơn
    int tailPts[] = {
        gx - S(6),  gy + S(6),
        gx - S(12) + tailWiggleX, gy + S(18) + tailWiggleY,
        gx + S(2) + tailWiggleX, gy + S(14),
        gx + S(6),  gy + S(6)
    };
    drawFilledPoly(4, tailPts, bodyGreen, borderGreen, 2);
    
    // Đầu tròn của ma
    setfillstyle(SOLID_FILL, bodyGreen);
    setcolor(borderGreen);
    setlinestyle(SOLID_LINE, 0, 2);
    fillellipse(gx, gy, S(12), S(12));
    
    // Vẽ viền tròn đầu
    arc(gx, gy, 0, 360, S(12));
    
    // Hốc mắt rỗng đen lớn biểu cảm kinh dị
    setfillstyle(SOLID_FILL, eyeColor);
    setcolor(eyeColor);
    fillellipse(gx - S(4), gy - S(2), S(3), S(5));
    fillellipse(gx + S(3), gy - S(2), S(3), S(5));
    
    // Đồng tử nhỏ màu xanh lá sáng phát quang bên trong hốc mắt (Tối ưu bằng putpixel)
    putpixel(gx - S(4), gy - S(1), COLOR(200, 255, 180));
    putpixel(gx + S(3), gy - S(1), COLOR(200, 255, 180));
    
    // Miệng há hốc dài gào thét u ám
    setfillstyle(SOLID_FILL, eyeColor);
    fillellipse(gx, gy + S(5), S(4), S(7));
}

// Hàm chính vẽ Boss Reaper với ngoại hình ghê rợn QUAY MẶT VỀ BÊN TRÁI (HƯỚNG EXPLORER)
void drawReaperBoss(int x, int y, float scale, float timeSec) {
    // Tần số và biên độ lơ lửng của Reaper
    float floatVal = sin(timeSec * 2.2f);
    int floatY = (int)(floatVal * 15.0f * scale);
    
    // Tâm vẽ chính (bx, by)
    int bx = x;
    int by = y - S(110) + floatY;
    
    // Bảng màu chi tiết nâng cao
    int cloakDarkShadow = COLOR(10, 8, 14);  // Đen tím kẽ nứt sâu
    int cloakDark = COLOR(24, 18, 32);       // Tím tối đổ bóng
    int cloakMain = COLOR(38, 30, 52);       // Tím đen quỷ dị chính
    int cloakLight = COLOR(75, 62, 100);      // Tím sáng nếp nhăn
    int cloakBright = COLOR(110, 92, 140);   // Tím viền phản chiếu ánh sáng
    int faceVoid = COLOR(2, 2, 4);           // Đen tối của hốc mũ
    int skullGrey = COLOR(38, 34, 44);       // Xám sọ ẩn hiện
    int eyeRed = COLOR(255, 20, 20);         // Đỏ ngọc dữ tợn
    int eyeCore = COLOR(255, 240, 160);      // Nhân vàng sáng mắt
    int handGrey = COLOR(140, 142, 148);     // Xám xương khô
    int boneWhite = COLOR(235, 240, 242);    // Trắng xương sắc nhọn
    int scytheShaft = COLOR(30, 28, 32);     // Sắt cán đen
    int scytheBlade = COLOR(190, 195, 205);   // Thép bạc lưỡi hái
    
    // --- 1. Vẽ bóng đen quỷ dị trên mặt đất ---
    int shadowR = S(65) - (int)(floatVal * S(5));
    setfillstyle(SOLID_FILL, COLOR(8, 8, 12));
    fillellipse(x, y + S(5), shadowR, S(12));
    
    // Vòng ma trận quỷ dị dưới chân Reaper quay mặt về bên trái
    setcolor(COLOR(70, 20, 20));
    setlinestyle(SOLID_LINE, 0, 2);
    ellipse(x, y + S(5), 0, 360, shadowR + S(12), S(16));
    
    // Các ký tự ma thuật nhỏ
    int runeOffset = (int)(timeSec * 50.0f) % 360;
    for (int i = 0; i < 4; i++) {
        float angle = (i * 90 + runeOffset) * 3.14159f / 180.0f;
        int rx = x + (int)(cos(angle) * (shadowR + S(12)));
        int ry = y + S(5) + (int)(sin(angle) * S(16));
        setcolor(COLOR(200, 30, 30));
        line(rx - S(2), ry - S(2), rx + S(2), ry + S(2));
        line(rx + S(2), ry - S(2), rx - S(2), ry + S(2));
    }
    
    // --- 2. Vẽ các linh hồn gào thét bay xung quanh (Tối ưu từ 4 xuống 2 linh hồn để giảm lag) ---
    // Linh hồn 1: Phía trên bên trái
    int g1x = bx - S(105) + (int)(cos(timeSec * 1.6f) * S(18));
    int g1y = by - S(70) + (int)(sin(timeSec * 2.0f) * S(20));
    drawMiniGhost(g1x, g1y, scale, timeSec, 0);
    
    // Linh hồn 2: Phía dưới bên phải
    int g4x = bx + S(120) + (int)(cos(timeSec * 1.7f) * S(14));
    int g4y = by + S(25) + (int)(sin(timeSec * 1.4f) * S(16));
    drawMiniGhost(g4x, g4y, scale, timeSec, 1);
    
    // --- 3. Vẽ Cán Lưỡi Hái liền mạch (Solid Scythe Shaft) - QUAY TRÁI (Đặt bên phải để lưỡi liềm chĩa sang trái) ---
    int shaftX1 = bx + S(20); int shaftY1 = by + S(120);
    int shaftX2 = bx + S(65); int shaftY2 = by - S(120);
    
    // Thân cán sắt đặc liền mạch
    setcolor(scytheShaft);
    setlinestyle(SOLID_LINE, 0, S(5));
    line(shaftX1, shaftY1, shaftX2, shaftY2);
    
    // Viền kim loại sáng dọc cán
    setcolor(COLOR(70, 70, 75));
    setlinestyle(SOLID_LINE, 0, S(2));
    line(shaftX1 + S(1), shaftY1, shaftX2 + S(1), shaftY2);
    
    // Băng vải quấn cán màu đỏ
    setcolor(COLOR(160, 30, 30));
    setlinestyle(SOLID_LINE, 0, S(3));
    line(bx + S(48), by - S(20), bx + S(52), by - S(32));
    line(bx + S(30), by + S(65), bx + S(34), by + S(53));

    // --- 4. Vẽ áo choàng lớp sau (Back Cloak) - QUAY TRÁI ---
    int backCloakPts[] = {
        bx - S(45), by - S(30),
        bx - S(55), by + S(15),
        bx + S(52), by + S(15),
        bx + S(44), by - S(30),
        bx, by - S(65)
    };
    drawFilledPoly(5, backCloakPts, cloakDarkShadow, BLACK, 2);

    // --- 5. Vẽ thân áo choàng chính (Main Cloak Body) - QUAY TRÁI ---
    int bodyCloakPts[] = {
        bx - S(45), by - S(20),
        bx - S(52), by + S(20),
        bx + S(46), by + S(20),
        bx + S(38), by - S(20)
    };
    drawFilledPoly(4, bodyCloakPts, cloakMain, BLACK, 2);

    // Vẽ các tà áo rách rưới bay phấp phới độc lập (Waving Tatters)
    for (int i = 0; i < 5; i++) {
        float freq = 2.8f + i * 0.4f;
        float phase = i * 1.1f;
        int waveX = (int)(sin(timeSec * freq + phase) * S(9));
        int tW = S(18);
        int leftX = bx - S(45) + i * S(19);
        int topY = by + S(18);
        int bottomY = by + S(80) + (int)(cos(timeSec * freq * 0.8f + phase) * S(12));
        
        int tatterPts[] = { leftX, topY, leftX + tW, topY, leftX + tW / 2 + waveX, bottomY };
        drawFilledPoly(3, tatterPts, cloakMain, BLACK, 2);
        
        // Highlight nếp sáng trên tà áo
        setcolor(cloakLight);
        setlinestyle(SOLID_LINE, 0, 2);
        line(leftX + tW / 2, topY, leftX + tW / 2 + waveX / 2, topY + S(35));
    }

    // --- 6. Vẽ dây xích cổ & Huy hiệu Sọ Bạc ---
    setcolor(COLOR(120, 120, 125));
    setlinestyle(DOTTED_LINE, 0, 2);
    line(bx, by - S(10), bx - S(32), by - S(22));
    line(bx, by - S(10), bx + S(32), by - S(22));
    
    // Huy hiệu Sọ Bạc ngực
    setfillstyle(SOLID_FILL, COLOR(190, 190, 195));
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    fillellipse(bx, by - S(10), S(6), S(6));
    circle(bx, by - S(10), S(6));
    bar(bx - S(3), by - S(5), bx + S(3), by - S(1));
    setcolor(BLACK);
    line(bx - S(3), by - S(5), bx - S(3), by - S(1));
    line(bx + S(3), by - S(5), bx + S(3), by - S(1));
    line(bx - S(3), by - S(1), bx + S(3), by - S(1));
    // Răng sọ
    line(bx - S(1), by - S(3), bx - S(1), by - S(1));
    line(bx + S(1), by - S(3), bx + S(1), by - S(1));
    // Hốc mắt
    putpixel(bx - S(2), by - S(9), BLACK);
    putpixel(bx + S(2), by - S(9), BLACK);

    // --- 7. Vẽ cánh tay xương vuốt dài bên trái (Left Claw) - HƯỚNG VỀ PHÍA TRÁI (EXPLORER) ---
    int sleeveLPts[] = {
        bx - S(32), by - S(25),
        bx - S(52), by - S(15),
        bx - S(44), by + S(8),
        bx - S(22), by - S(10)
    };
    drawFilledPoly(4, sleeveLPts, cloakMain, BLACK, 2);
    
    // Cánh tay xương xám vươn sang bên trái
    setcolor(handGrey);
    setlinestyle(SOLID_LINE, 0, S(2));
    line(bx - S(45), by - S(11), bx - S(63), by + S(7));
    line(bx - S(47), by - S(8),  bx - S(65), by + S(10));
    // Khớp cổ tay
    setfillstyle(SOLID_FILL, handGrey);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    fillellipse(bx - S(64), by + S(8), S(4), S(4));
    circle(bx - S(64), by + S(8), S(4));
    
    // Các ngón xương dài nhọn chỉ sang bên trái
    int fingerAngle[] = { -20, 0, 20, 45 };
    for (int f = 0; f < 4; f++) {
        int fx1 = bx - S(64);
        int fy1 = by + S(8);
        
        float rad = (float)(fingerAngle[f]) * 3.14159f / 180.0f;
        int fx2 = fx1 - (int)(cos(rad) * S(10));
        int fy2 = fy1 + (int)(sin(rad) * S(10));
        
        int fx3 = fx2 - (int)(cos(rad - 0.2f) * S(8));
        int fy3 = fy2 + (int)(sin(rad - 0.2f) * S(8));
        
        setcolor(handGrey);
        setlinestyle(SOLID_LINE, 0, S(2));
        line(fx1, fy1, fx2, fy2);
        
        setcolor(boneWhite);
        line(fx2, fy2, fx3, fy3);
        
        // Tối ưu khớp ngón tay từ fillellipse thành putpixel
        putpixel(fx2, fy2, COLOR(190, 195, 200));
    }

    // --- 8. Vẽ đầu và mũ trùm Spooky Hood - ĐỈNH MŨ HƯỚNG VỀ PHÍA SAU (BÊN PHẢI) ---
    int hoodPts[] = {
        bx + S(18), by - S(105), // Đỉnh nhọn xếch sang phải (phía sau đầu khi nhìn trái)
        bx + S(32), by - S(85),
        bx + S(46), by - S(45),
        bx + S(38), by - S(18),
        bx - S(38), by - S(18),
        bx - S(46), by - S(45),
        bx - S(28), by - S(85)
    };
    drawFilledPoly(7, hoodPts, cloakMain, BLACK, 2);

    // Lớp lót trong mũ
    int hoodInnerPts[] = {
        bx + S(12), by - S(100),
        bx + S(28), by - S(82),
        bx + S(42), by - S(44),
        bx + S(35), by - S(18),
        bx - S(35), by - S(18),
        bx - S(42), by - S(44),
        bx - S(24), by - S(82)
    };
    setcolor(cloakDark);
    setlinestyle(SOLID_LINE, 0, 1);
    drawpoly(7, hoodInnerPts);

    // Highlight phản chiếu sáng ở viền trước mũ trùm (bên trái)
    setcolor(cloakBright);
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx - S(15), by - S(105), bx - S(5), by - S(70));
    line(bx - S(5), by - S(70), bx - S(25), by - S(40));

    // Hốc đen khuôn mặt (Face Void) dịch nhẹ sang trái
    int faceX = bx - S(4);
    int faceY = by - S(48);
    setfillstyle(SOLID_FILL, faceVoid);
    setcolor(BLACK);
    fillellipse(faceX, faceY, S(19), S(26));
    
    // Viền sâu trong bóng tối hốc mũ
    setcolor(cloakDark);
    setlinestyle(SOLID_LINE, 0, 2);
    arc(faceX, faceY, 0, 360, S(20));

    // --- 9. Sọ ma quái ẩn hiện inside Hood (Faint Skull) ---
    setfillstyle(SOLID_FILL, skullGrey);
    setcolor(cloakDarkShadow);
    setlinestyle(SOLID_LINE, 0, 1);
    fillellipse(faceX, faceY - S(2), S(12), S(9));
    bar(faceX - S(5), faceY + S(7), faceX + S(5), faceY + S(13));
    setcolor(COLOR(65, 60, 75));
    line(faceX - S(3), faceY + S(10), faceX - S(3), faceY + S(13));
    line(faceX, faceY + S(10), faceX, faceY + S(13));
    line(faceX + S(3), faceY + S(10), faceX + S(3), faceY + S(13));
    
    setfillstyle(SOLID_FILL, faceVoid);
    fillellipse(faceX - S(4), faceY - S(2), S(2), S(3));
    fillellipse(faceX + S(4), faceY - S(2), S(2), S(3));

    // --- 10. Vẽ đôi mắt xếch giận dữ màu đỏ ngọc & Đuôi lửa hướng sang trái ---
    int eyeThick = S(3) + (int)(sin(timeSec * 8.0f) * S(1));
    if (eyeThick < 2) eyeThick = 2;

    // Mắt trái xếch (hướng về trung tâm hốc mặt dịch trái)
    setcolor(eyeRed);
    setlinestyle(SOLID_LINE, 0, eyeThick);
    line(bx - S(16), by - S(55), bx - S(7), by - S(48));
    
    setcolor(eyeCore);
    setlinestyle(SOLID_LINE, 0, 1);
    line(bx - S(13), by - S(53), bx - S(9), by - S(50));
    
    // Mắt phải xếch
    setcolor(eyeRed);
    setlinestyle(SOLID_LINE, 0, eyeThick);
    line(bx + S(2), by - S(55), bx - S(5), by - S(48));
    
    setcolor(eyeCore);
    setlinestyle(SOLID_LINE, 0, 1);
    line(bx + S(0), by - S(53), bx - S(3), by - S(50));

    // Đuôi lửa tâm linh bay từ đuôi mắt dịch về phía trái (Tối ưu bằng putpixel tránh lag)
    int trailW1 = (int)(sin(timeSec * 15.0f) * S(3));
    int trailW2 = (int)(cos(timeSec * 12.0f) * S(3));
    putpixel(bx - S(18) + trailW1, by - S(60), eyeRed);
    putpixel(bx - S(22) + trailW2, by - S(65), eyeRed);
    putpixel(bx + S(12) - trailW1, by - S(60), eyeRed);
    putpixel(bx + S(14) - trailW2, by - S(65), eyeRed);

    // --- 11. Cánh tay nâng cán lưỡi hái (Right Arm) - QUAY TRÁI (Đặt bên phải nâng cán hái) ---
    int armRPts[] = {
        bx + S(28), by - S(25),
        bx + S(46), by - S(20),
        bx + S(52), by - S(8),
        bx + S(38), by - S(5),
        bx + S(25), by - S(15)
    };
    drawFilledPoly(5, armRPts, cloakMain, BLACK, 2);

    // Bàn tay xương xám nắm lấy cán hái bên phải
    int handRPts[] = {
        bx + S(42), by - S(10),
        bx + S(48), by - S(5),
        bx + S(54), by - S(12),
        bx + S(48), by - S(17)
    };
    drawFilledPoly(4, handRPts, handGrey, BLACK, 1);

    // --- 12. Khớp Sọ Bạc nối Lưỡi Hái - QUAY TRÁI (Nằm bên phải cán để chĩa lưỡi liềm qua trái) ---
    int jx = bx + S(65);
    int jy = by - S(120);
    // Sọ dome
    setfillstyle(SOLID_FILL, COLOR(205, 205, 210));
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    fillellipse(jx, jy, S(9), S(9));
    circle(jx, jy, S(9));
    // Sọ jaw
    bar(jx - S(4), jy + S(5), jx + S(4), jy + S(11));
    line(jx - S(4), jy + S(5), jx - S(4), jy + S(11));
    line(jx + S(4), jy + S(5), jx + S(4), jy + S(11));
    line(jx - S(4), jy + S(11), jx + S(4), jy + S(11));
    // Hốc mắt
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(jx - S(3), jy - S(1), S(2), S(3));
    fillellipse(jx + S(3), jy - S(1), S(2), S(3));

    // --- 13. Lưỡi Hái Tử Thần Khổng Lồ - QUAY TRÁI (Lưỡi hái chĩa sang bên trái hướng Explorer) ---
    int bladePts[] = {
        jx, jy,                   // Điểm gắn cán hái (bên phải)
        bx + S(18), by - S(110),  
        bx - S(28), by - S(75),   // Đầu nhọn hoắt (chĩa sang bên trái)
        bx - S(8),  by - S(71),   
        bx + S(35), by - S(90),
        bx + S(58), by - S(102)
    };
    drawFilledPoly(6, bladePts, scytheBlade, BLACK, 2);
    
    // Các vết nứt nẻ
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    line(bx + S(22), by - S(108), bx + S(20), by - S(100));
    line(bx + S(5), by - S(98), bx + S(8), by - S(91));

    // Đường gân thép dọc sống
    setcolor(COLOR(110, 115, 125));
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx + S(60), by - S(116), bx - S(15), by - S(74));

    // Viền đỏ ngọc dạ quang sắc bén bên dưới lưỡi cắt chĩa về bên trái
    setcolor(eyeRed);
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx + S(58), by - S(102), bx - S(28), by - S(75));

    // Khắc 4 cổ tự Rune phát sáng màu đỏ ngọc
    int runeX[] = { bx + S(45), bx + S(28), bx + S(10), bx - S(8) };
    int runeY[] = { by - S(99), by - S(92), by - S(83), by - S(76) };
    for (int r = 0; r < 4; r++) {
        if ((int)(timeSec * 4.0f + r) % 2 == 0) {
            setcolor(COLOR(255, 60, 60));
            setlinestyle(SOLID_LINE, 0, 1);
            line(runeX[r] - S(2), runeY[r], runeX[r] + S(2), runeY[r]);
            line(runeX[r], runeY[r] - S(2), runeX[r], runeY[r] + S(2));
        }
    }
    
    setlinestyle(SOLID_LINE, 0, 1);
}

void drawBossScytheSlash(int bossX, int bossY, float progress) {
    int cx = bossX - 40 - (int)(progress * (bossX + 100.0f));
    int cy = bossY - 40;
    
    int size = 65 + (int)(progress * 25);
    int colors[] = { COLOR(80, 0, 40), COLOR(210, 15, 30), COLOR(255, 140, 140) };
    int thicknesses[] = { 6, 4, 2 };
    int radii[] = { size, size - 8, size - 16 };
    
    for (int i = 0; i < 3; i++) {
        if (radii[i] <= 0) continue;
        setcolor(colors[i]);
        setlinestyle(SOLID_LINE, 0, thicknesses[i]);
        // Vẽ cung từ 100 độ đến 260 độ tạo thành vòng cung lớn quét sang trái
        arc(cx, cy, 100, 260, radii[i]);
        arc(cx - 6, cy, 100, 260, radii[i]);
        
        if (i == 1) {
            // Vẽ các tia lửa/vết nứt năng lượng quét ra phía trước
            setlinestyle(SOLID_LINE, 0, 2);
            for (int j = 0; j < 6; j++) {
                float angle = (110 + j * 26) * 3.1415926f / 180.0f;
                int sx = cx + (int)(cos(angle) * radii[i]);
                int sy = cy + (int)(sin(angle) * radii[i]);
                int ex = sx + (int)(cos(angle) * (18.0f * (1.0f + progress)));
                int ey = sy + (int)(sin(angle) * (18.0f * (1.0f + progress)));
                line(sx, sy, ex, ey);
            }
        }
    }
    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
