#ifndef DEMON_BOSS_H
#define DEMON_BOSS_H

#include <graphics.h>
#include <math.h>
#include "../configs/Config.cpp"
#include "../algorithms/index.cpp"
#include "../logic/GameplayTypes.cpp"

// Macro scale tọa độ
#ifndef S
#define S(val) ((int)((val) * scale))
#endif

// Hàm hỗ trợ vẽ đa giác tô màu có viền khép kín
static void drawDemonFilledPoly(int numPoints, int* points, int fillColor, int outlineColor, int thickness = 1) {
    setfillstyle(SOLID_FILL, fillColor);
    fillpoly(numPoints, points);
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickness);
    drawpoly(numPoints, points);
    // Khép kín đa giác
    line(points[(numPoints - 1) * 2], points[(numPoints - 1) * 2 + 1], points[0], points[1]);
}

// Vẽ Boss Demon siêu chi tiết, sắc nét từng bộ phận và QUAY HẲN MẶT VỀ BÊN TRÁI
void drawDemonBoss(int x, int y, float scale, float timeSec) {
    // Tần số và biên độ lơ lửng nhẹ
    float floatVal = sin(timeSec * 2.2f);
    int floatY = (int)(floatVal * 6.0f * scale);
    
    // Tâm vẽ chính (bx, by)
    int bx = x;
    int by = y - S(110) + floatY;
    
    // Bảng màu chi tiết và độ tương phản cao
    int skinRed = COLOR(220, 20, 20);         // Đỏ da chính
    int skinShadow = COLOR(110, 5, 5);        // Đỏ tối (bóng cơ bắp)
    int skinHighlight = COLOR(255, 110, 110); // Đỏ sáng (highlight cơ bắp)
    
    int wingDark = COLOR(28, 28, 30);         // Cánh đen tối
    int wingShadow = COLOR(18, 18, 20);       // Bóng cánh tối hơn
    int wingLight = COLOR(65, 65, 70);        // Xương cánh sáng viền
    
    int hornDark = COLOR(18, 18, 20);         // Sừng đen
    int hornLight = COLOR(60, 60, 65);        // Vân sừng sáng
    
    int beardWhite = COLOR(235, 235, 240);    // Râu xám trắng sáng
    int beardDark = COLOR(125, 125, 130);     // Râu tối đổ bóng
    
    int beltBlue = COLOR(25, 35, 55);         // Thắt lưng xanh tối
    int beltBlueLight = COLOR(65, 85, 130);   // Viền thắt lưng sáng
    int loinclothDark = COLOR(20, 28, 45);     // Khố tối
    
    int skullWhite = COLOR(250, 250, 250);    // Sọ trắng sáng
    int eyeYellow = COLOR(255, 245, 0);       // Mắt vàng rực
    int eyeOrange = COLOR(255, 95, 0);        // Viền mắt cam
    int shadowGround = COLOR(5, 5, 8);        // Bóng dưới đất
    
    // Bảng màu Kiếm Lửa
    int swordGold = COLOR(255, 195, 18);      // Chuôi kiếm vàng sáng
    int swordGoldShadow = COLOR(150, 100, 5); // Chuôi kiếm tối
    int swordBlade = COLOR(255, 255, 215);     // Lõi kiếm vàng trắng phát quang
    int fireOrange = COLOR(255, 90, 0);       // Lửa cam
    int fireRed = COLOR(215, 15, 15);         // Lửa đỏ
    int fireYellow = COLOR(255, 230, 45);     // Lửa vàng sáng
    
    // --- 1. Bóng đen dưới đất ---
    int shadowR = S(75) - (int)(floatVal * S(4));
    setfillstyle(SOLID_FILL, shadowGround);
    fillellipse(x, y + S(5), shadowR, S(13));
    
    // Vòng lửa ma thuật chân
    setcolor(fireRed);
    setlinestyle(SOLID_LINE, 0, 2);
    ellipse(x, y + S(5), 0, 360, shadowR + S(8), S(10));

    // --- 2. Đôi Cánh Dơi Khổng Lồ Nhiều Gấp Khúc Sắc Nét ---
    float wingWiggle = sin(timeSec * 2.6f) * 0.04f;

    // Cánh bên phải (Background Wing - ở phía sau)
    int wingRPts[] = {
        bx + S(12), by - S(25),                      // Gốc vai sau
        bx + S(45), by - S(52) - (int)(wingWiggle * S(40)),   // Khúc gãy 1
        bx + S(70), by - S(82) - (int)(wingWiggle * S(70)),   // Khúc gãy 2 (Đỉnh)
        bx + S(100), by - S(68) - (int)(wingWiggle * S(90)),  // Khúc gãy 3
        bx + S(122), by - S(38) - (int)(wingWiggle * S(100)), // Chóp cánh nhọn
        bx + S(95), by - S(6),
        bx + S(80), by + S(15),
        bx + S(55), by - S(10),
        bx + S(28), by + S(5)
    };
    drawDemonFilledPoly(9, wingRPts, wingShadow, BLACK, 2);

    // Họa tiết đỏ rực rỡ bên trong màng cánh phải
    int wingRRedPts[] = {
        bx + S(45), by - S(47) - (int)(wingWiggle * S(40)),
        bx + S(68), by - S(75) - (int)(wingWiggle * S(70)),
        bx + S(95), by - S(62) - (int)(wingWiggle * S(90)),
        bx + S(115), by - S(36) - (int)(wingWiggle * S(100)),
        bx + S(90), by - S(8),
        bx + S(78), by + S(8),
        bx + S(55), by - S(15)
    };
    drawDemonFilledPoly(7, wingRRedPts, COLOR(160, 10, 10), BLACK, 1);
    
    // Xương cánh phải sắc nét
    setcolor(wingLight);
    setlinestyle(SOLID_LINE, 0, 3);
    line(bx + S(12), by - S(25), bx + S(45), by - S(52) - (int)(wingWiggle * S(40)));
    line(bx + S(45), by - S(52) - (int)(wingWiggle * S(40)), bx + S(70), by - S(82) - (int)(wingWiggle * S(70)));
    line(bx + S(70), by - S(82) - (int)(wingWiggle * S(70)), bx + S(100), by - S(68) - (int)(wingWiggle * S(90)));
    line(bx + S(100), by - S(68) - (int)(wingWiggle * S(90)), bx + S(122), by - S(38) - (int)(wingWiggle * S(100)));

    // Cánh bên trái (Foreground Wing - ở phía trước)
    int wingLPts[] = {
        bx - S(8), by - S(25),                       // Gốc vai trước
        bx - S(40), by - S(48) + (int)(wingWiggle * S(40)),
        bx - S(65), by - S(78) + (int)(wingWiggle * S(70)),
        bx - S(92), by - S(62) + (int)(wingWiggle * S(90)),
        bx - S(116), by - S(32) + (int)(wingWiggle * S(100)), // Chóp cánh nhọn
        bx - S(90), by - S(3),
        bx - S(75), by + S(18),
        bx - S(50), by - S(8),
        bx - S(22), by + S(5)
    };
    drawDemonFilledPoly(9, wingLPts, wingDark, BLACK, 2);

    // Họa tiết đỏ rực rỡ bên trong màng cánh trái
    int wingLRedPts[] = {
        bx - S(40), by - S(43) + (int)(wingWiggle * S(40)),
        bx - S(63), by - S(71) + (int)(wingWiggle * S(70)),
        bx - S(88), by - S(57) + (int)(wingWiggle * S(90)),
        bx - S(110), by - S(30) + (int)(wingWiggle * S(100)),
        bx - S(85), by - S(5),
        bx - S(73), by + S(10),
        bx - S(50), by - S(13)
    };
    drawDemonFilledPoly(7, wingLRedPts, COLOR(220, 15, 15), BLACK, 1);
    
    // Xương cánh trái sắc nét
    setcolor(wingLight);
    setlinestyle(SOLID_LINE, 0, 3);
    line(bx - S(8), by - S(25), bx - S(40), by - S(48) + (int)(wingWiggle * S(40)));
    line(bx - S(40), by - S(48) + (int)(wingWiggle * S(40)), bx - S(65), by - S(78) + (int)(wingWiggle * S(70)));
    line(bx - S(65), by - S(78) + (int)(wingWiggle * S(70)), bx - S(92), by - S(62) + (int)(wingWiggle * S(90)));
    line(bx - S(92), by - S(62) + (int)(wingWiggle * S(90)), bx - S(116), by - S(32) + (int)(wingWiggle * S(100)));

    // --- 3. Đuôi Ác Quỷ (Devil Tail) ---
    int tailWiggleX = (int)(sin(timeSec * 3.8f) * S(9));
    int tailWiggleY = (int)(cos(timeSec * 2.8f) * S(6));
    int tailPts[] = {
        bx + S(12), by + S(52), // Xuất phát từ hông phải (phía sau)
        bx + S(36), by + S(64),
        bx + S(64) + tailWiggleX, by + S(54) + tailWiggleY,
        bx + S(84) + tailWiggleX, by + S(34) + tailWiggleY
    };
    setcolor(skinRed);
    setlinestyle(SOLID_LINE, 0, 4);
    for(int i = 0; i < 3; ++i) {
        line(tailPts[i*2], tailPts[i*2+1], tailPts[(i+1)*2], tailPts[(i+1)*2+1]);
    }
    // Đuôi tam giác đen nhọn
    int tipX = tailPts[6];
    int tipY = tailPts[7];
    int tipPts[] = {
        tipX, tipY,
        tipX + S(12), tipY - S(10),
        tipX - S(4), tipY - S(14)
    };
    drawDemonFilledPoly(3, tipPts, hornDark, BLACK, 1);

    // --- 4. Chân Quỷ (Legs & Hooves) ---
    // Chân phải (Background leg - ở sau)
    int legRPts[] = {
        bx + S(6), by + S(48),
        bx + S(10), by + S(72),
        bx + S(8), by + S(96),
        bx + S(22), by + S(96),
        bx + S(14), by + S(90),
        bx + S(22), by + S(68),
        bx + S(16), by + S(48)
    };
    drawDemonFilledPoly(7, legRPts, skinShadow, BLACK, 2);
    int hoofRPts[] = {
        bx + S(8), by + S(96),
        bx + S(6), by + S(103),
        bx + S(24), by + S(103),
        bx + S(22), by + S(96)
    };
    drawDemonFilledPoly(4, hoofRPts, hornDark, BLACK, 1);

    // Chân trái (Foreground leg - ở trước, nghiêng trái rõ rệt)
    int legLPts[] = {
        bx - S(16), by + S(48),
        bx - S(24), by + S(68),
        bx - S(14), by + S(94),
        bx - S(23), by + S(98),
        bx - S(6), by + S(98),
        bx - S(8), by + S(73),
        bx - S(6), by + S(48)
    };
    drawDemonFilledPoly(7, legLPts, skinRed, BLACK, 2);
    // Guốc chân trái
    int hoofLPts[] = {
        bx - S(23), by + S(98),
        bx - S(25), by + S(105),
        bx - S(4), by + S(105),
        bx - S(6), by + S(98)
    };
    drawDemonFilledPoly(4, hoofLPts, hornDark, BLACK, 1);

    // --- 5. Thân Mình Cơ Bắp Nghiêng Trái Sắc Nét ---
    int torsoPts[] = {
        bx - S(26), by - S(10), // Vai trái (trước)
        bx - S(20), by + S(25), // Eo trái
        bx - S(15), by + S(48), // Hông trái
        bx + S(15), by + S(48), // Hông phải
        bx + S(20), by + S(25), // Eo phải
        bx + S(24), by - S(10), // Vai phải (sau)
        bx - S(6), by - S(16)   // Cổ
    };
    drawDemonFilledPoly(7, torsoPts, skinRed, BLACK, 2);

    // Vẽ khối cơ ngực 3D nghiêng trái cực kỳ rõ rệt
    setcolor(skinShadow);
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx - S(24), by - S(3), bx - S(8), by + S(3)); // Cơ ngực trái trước
    line(bx - S(8), by + S(3), bx + S(16), by - S(5));  // Cơ ngực phải sau
    line(bx - S(8), by + S(3), bx - S(10), by + S(45)); // Dọc bụng nghiêng trái
    // Múi bụng 3D sắc nét
    line(bx - S(15), by + S(13), bx + S(2), by + S(13));
    line(bx - S(16), by + S(24), bx + S(3), by + S(24));
    line(bx - S(14), by + S(35), bx + S(1), by + S(35));

    // Highlights cơ bụng sáng bóng màu hồng cam
    setcolor(skinHighlight);
    line(bx - S(22), by - S(5), bx - S(9), by - S(2));
    line(bx - S(13), by + S(10), bx - S(4), by + S(10));
    line(bx - S(14), by + S(20), bx - S(5), by + S(20));

    // --- 6. Thắt Lưng & Khố Quấn ---
    int beltPts[] = {
        bx - S(18), by + S(45),
        bx - S(20), by + S(53),
        bx + S(18), by + S(53),
        bx + S(16), by + S(45)
    };
    drawDemonFilledPoly(4, beltPts, beltBlue, BLACK, 2);

    int loinclothPts[] = {
        bx - S(11), by + S(53),
        bx - S(14), by + S(80),
        bx - S(7), by + S(100), // Rách khố đáy
        bx + S(5), by + S(83),
        bx + S(10), by + S(53)
    };
    drawDemonFilledPoly(5, loinclothPts, loinclothDark, BLACK, 2);
    setcolor(beltBlueLight);
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx - S(5), by + S(55), bx - S(7), by + S(85));

    // Khóa đai Đầu Lâu sắc nét
    int skX = bx - S(3);
    int skY = by + S(50);
    setfillstyle(SOLID_FILL, skullWhite);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    fillellipse(skX, skY, S(6), S(6));
    circle(skX, skY, S(6));
    bar(skX - S(3), skY + S(3), skX + S(3), skY + S(8));
    line(skX - S(3), skY + S(3), skX - S(3), skY + S(8));
    line(skX + S(3), skY + S(3), skX + S(3), skY + S(8));
    line(skX - S(3), skY + S(8), skX + S(3), skY + S(8));
    putpixel(skX - S(2), skY + S(1), RED);
    putpixel(skX + S(2), skY + S(1), RED);

    // --- 7. ĐẦU VÀ CỔ QUY (Quay về bên trái) ---
    // Vẽ phần cổ màu đỏ nối liền thân mình và đầu
    int neckPts[] = {
        bx - S(10), by - S(20), // Nối cổ sau đầu
        bx + S(2), by - S(20),  // Nối cổ trước đầu
        bx + S(8), by - S(10),  // Nối vai sau thân
        bx - S(14), by - S(12)  // Nối vai trước thân
    };
    drawDemonFilledPoly(4, neckPts, skinRed, BLACK, 2);

    // Khuôn mặt vẽ dạng profile nghiêng trái cực kỳ rõ ràng
    int headPts[] = {
        bx - S(12), by - S(20), // Cổ sau
        bx - S(20), by - S(28), // Cằm nhô về bên trái
        bx - S(22), by - S(36), // Mũi/Mồm ác quỷ nhô nhọn hẳn về phía bên trái
        bx - S(18), by - S(42), // Trán dốc
        bx - S(6), by - S(48),  // Đỉnh đầu trước
        bx + S(6), by - S(46),  // Đỉnh đầu sau
        bx + S(10), by - S(36), // Gáy sau
        bx + S(2), by - S(20)   // Cổ trước
    };
    drawDemonFilledPoly(8, headPts, skinRed, BLACK, 2);

    // Mắt ác quỷ thứ nhất (Mắt phải gần - lớn hơn, xếch ngược lên phía sau)
    int eye1Pts[] = {
        bx - S(16), by - S(33), // Khóe mắt trong (thấp, gần mũi)
        bx - S(9), by - S(39),  // Đuôi mắt ngoài (cao, xếch lên phía sau)
        bx - S(14), by - S(33)  // Đáy mắt
    };
    drawDemonFilledPoly(3, eye1Pts, eyeYellow, eyeOrange, 1);
    setcolor(COLOR(255, 0, 0));
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx - S(15), by - S(34), bx - S(10), by - S(38)); // Đồng tử xếch theo mắt

    // Lông mày xếch tà ác mắt 1 (dữ tợn hơn, ôm sát viền trên mắt)
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);
    line(bx - S(18), by - S(35), bx - S(8), by - S(41));

    // Tai nhọn ác quỷ chỉ vẽ ở phía sau chĩa về bên phải (do quay đầu sang trái)
    int earRPts[] = { bx + S(8), by - S(33), bx + S(19), by - S(31), bx + S(8), by - S(27) };
    drawDemonFilledPoly(3, earRPts, skinRed, BLACK, 1);

    // Râu xám dài chảy từ cằm nghiêng trái (bx - S(20)) đổ xuống phía dưới bên trái
    int beardPts[] = {
        bx - S(20), by - S(28), // Bắt đầu tại cằm nhô trái
        bx - S(22), by - S(12),
        bx - S(14), by + S(7),  // Đỉnh râu nhọn chảy chéo hẳn về bên trái
        bx - S(6), by - S(12),
        bx - S(8), by - S(25)
    };
    drawDemonFilledPoly(5, beardPts, beardWhite, beardDark, 2);

    // Cặp sừng Ác quỷ lớn được thiết kế CONG ĐẸP VÀ UỐN LƯỢN DỮ TỢN HƠN
    // Sừng trái (ở phía trước)
    int hornLPts[] = {
        bx - S(10), by - S(43), // Gốc sừng trước
        bx - S(22), by - S(54), // Cong lượn sang trái
        bx - S(20), by - S(70), // Cong vút lên trên
        bx - S(2), by - S(84),  // Uốn ngược sang phải
        bx + S(18), by - S(90), // Ngọn sừng nhọn hoắt
        bx + S(8), by - S(80),  // Viền dưới ngọn sừng
        bx - S(8), by - S(68),
        bx - S(10), by - S(54),
        bx - S(4), by - S(43)   // Gốc sừng sau
    };
    drawDemonFilledPoly(9, hornLPts, hornDark, BLACK, 2);

    // Sừng phải (ở phía sau)
    int hornRPts[] = {
        bx + S(4), by - S(43),  // Gốc sừng trước
        bx - S(6), by - S(52),  // Cong lượn sang trái
        bx - S(4), by - S(66),  // Cong vút lên
        bx + S(10), by - S(78), // Uốn sang phải
        bx + S(28), by - S(84), // Ngọn sừng nhọn hoắt
        bx + S(18), by - S(74), // Viền dưới
        bx + S(4), by - S(62),
        bx + S(2), by - S(50),
        bx + S(8), by - S(43)   // Gốc sừng sau
    };
    drawDemonFilledPoly(9, hornRPts, hornDark, BLACK, 2);

    // --- 8. Cánh tay trái (Background arm - ở phía sau) ---
    // Bắp tay sau (Background upper arm) - Làm to hơn
    int bicepLPts[] = {
        bx + S(22), by - S(10), // Vai sau
        bx + S(39), by + S(0),  // Bắp tay ngoài (phình to hơn)
        bx + S(41), by + S(14), // Khủy tay (nhô rộng hơn)
        bx + S(24), by + S(8),  // Khủy tay trong
        bx + S(15), by + S(8)   // Nách sau
    };
    drawDemonFilledPoly(5, bicepLPts, skinShadow, BLACK, 2);

    // Cẳng tay sau (Background forearm) - Làm to hơn
    int forearmLPts[] = {
        bx + S(41), by + S(14), // Khủy tay
        bx + S(44), by + S(20), // Cơ cánh tay dưới (to hơn)
        bx + S(30), by + S(26), // Cổ tay ngoài
        bx + S(20), by + S(22), // Cổ tay trong
        bx + S(24), by + S(8)   // Khớp trong
    };
    drawDemonFilledPoly(5, forearmLPts, skinShadow, BLACK, 2);
    
    // Bàn tay trái (Background hand) nắm đấm ở hông với các móng vuốt quỷ sắc lẹm màu đen
    int handLX = bx + S(26);
    int handLY = by + S(26);
    setfillstyle(SOLID_FILL, skinShadow);
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 1);
    fillellipse(handLX, handLY, S(6), S(6)); // Nắm đấm to hơn
    circle(handLX, handLY, S(6));

    // Vẽ móng vuốt quỷ sắc bén
    int lclaw1[] = { handLX + S(4), handLY + S(2), handLX + S(7), handLY + S(4), handLX + S(4), handLY + S(5) };
    drawDemonFilledPoly(3, lclaw1, hornDark, BLACK, 1);
    int lclaw2[] = { handLX, handLY + S(4), handLX + S(4), handLY + S(8), handLX - S(1), handLY + S(6) };
    drawDemonFilledPoly(3, lclaw2, hornDark, BLACK, 1);

    // --- 9. Cánh tay phải cầm Kiếm Lửa QUAY SANG TRÁI (Foreground arm - ở phía trước) ---
    // Bắp tay trước (Foreground upper arm) - Làm to hơn
    int bicepRPts[] = {
        bx - S(22), by - S(10), // Vai trước
        bx - S(39), by - S(4),  // Bắp tay ngoài (phình to hơn)
        bx - S(48), by + S(12), // Khủy tay ngoài (rộng hơn)
        bx - S(30), by + S(14), // Khớp trong
        bx - S(15), by + S(6)   // Nách trước
    };
    drawDemonFilledPoly(5, bicepRPts, skinRed, BLACK, 2);
    // Highlight bắp tay trước
    setcolor(skinHighlight);
    setlinestyle(SOLID_LINE, 0, 2);
    line(bx - S(24), by - S(5), bx - S(35), by + S(4));

    // Cẳng tay trước (Foreground forearm) - Làm to hơn
    int forearmRPts[] = {
        bx - S(48), by + S(12), // Khủy tay
        bx - S(53), by + S(18), // Cơ cánh tay dưới (to hơn)
        bx - S(48), by + S(23), // Cổ tay ngoài
        bx - S(38), by + S(24), // Cổ tay trong
        bx - S(30), by + S(14)  // Khớp trong
    };
    drawDemonFilledPoly(5, forearmRPts, skinRed, BLACK, 2);
    // Highlight cẳng tay trước
    setcolor(skinHighlight);
    line(bx - S(45), by + S(15), bx - S(39), by + S(22));

    // Bàn tay cầm kiếm (dịch chuyển khớp với cổ tay to hơn)
    int handX = bx - S(43);
    int handY = by + S(23);
    setfillstyle(SOLID_FILL, skinRed);
    fillellipse(handX, handY, S(7), S(7)); // Bàn tay to hơn một chút
    circle(handX, handY, S(7));

    // --- 10. Kiếm Lửa Khổng Lồ Sắc Nét Chĩa Sang Trái (Thiết kế tương tự kiếm của Hero) ---
    float angle = 2.30f; // Góc chéo hướng xuống bên trái
    float cosA = cos(angle);
    float sinA = sin(angle);
    float swScale = scale * 0.65f; // Scale kiếm vừa vặn với kích thước boss

    int fireHilt = COLOR(115, 10, 10);        // Chuôi kiếm đỏ tối
    int fireGuard = COLOR(245, 120, 20);      // Hộ thủ cam lửa

    // Tọa độ cấu trúc kiếm tương tự GiantSword của Hero
    Vec2 h0 = {-50.0f, 0.0f};
    Vec2 h1 = {0.0f, 0.0f};
    Vec2 g0 = {0.0f, -30.0f};
    Vec2 g1 = {0.0f, 30.0f};

    Vec2 b0 = {0.0f, -12.0f};
    Vec2 b1 = {130.0f, -12.0f};
    Vec2 b2 = {155.0f, 0.0f};
    Vec2 b3 = {130.0f, 12.0f};
    Vec2 b4 = {0.0f, 12.0f};

    Vec2 c0 = {2.0f, -6.0f};
    Vec2 c1 = {120.0f, -6.0f};
    Vec2 c2 = {140.0f, 0.0f};
    Vec2 c3 = {120.0f, 6.0f};
    Vec2 c4 = {2.0f, 6.0f};

    // Phép biến đổi xoay chéo và dịch chuyển kiếm đến tay boss
    Vec2 h0r = applyAffine(h0, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 h1r = applyAffine(h1, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 g0r = applyAffine(g0, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 g1r = applyAffine(g1, cosA, sinA, swScale, swScale, handX, handY);

    Vec2 b0r = applyAffine(b0, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 b1r = applyAffine(b1, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 b2r = applyAffine(b2, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 b3r = applyAffine(b3, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 b4r = applyAffine(b4, cosA, sinA, swScale, swScale, handX, handY);

    Vec2 c0r = applyAffine(c0, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 c1r = applyAffine(c1, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 c2r = applyAffine(c2, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 c3r = applyAffine(c3, cosA, sinA, swScale, swScale, handX, handY);
    Vec2 c4r = applyAffine(c4, cosA, sinA, swScale, swScale, handX, handY);

    // Vẽ chuôi kiếm
    setlinestyle(SOLID_LINE, 0, (int)(3.5f * swScale));
    setcolor(fireHilt);
    line((int)h0r.x, (int)h0r.y, (int)h1r.x, (int)h1r.y);

    // Vẽ hộ thủ bảo vệ tay
    setlinestyle(SOLID_LINE, 0, (int)(4.5f * swScale));
    setcolor(fireGuard);
    line((int)g0r.x, (int)g0r.y, (int)g1r.x, (int)g1r.y);

    // Vẽ lưỡi kiếm ngoài (đỏ cam rực lửa)
    int bladePts[] = {
        (int)b0r.x, (int)b0r.y,
        (int)b1r.x, (int)b1r.y,
        (int)b2r.x, (int)b2r.y,
        (int)b3r.x, (int)b3r.y,
        (int)b4r.x, (int)b4r.y
    };
    setfillstyle(SOLID_FILL, fireRed);
    fillpoly(5, bladePts);
    setcolor(fireOrange);
    setlinestyle(SOLID_LINE, 0, 1);
    drawpoly(5, bladePts);

    // Vẽ lõi phát quang bên trong (màu vàng lửa sáng)
    int corePts[] = {
        (int)c0r.x, (int)c0r.y,
        (int)c1r.x, (int)c1r.y,
        (int)c2r.x, (int)c2r.y,
        (int)c3r.x, (int)c3r.y,
        (int)c4r.x, (int)c4r.y
    };
    setfillstyle(SOLID_FILL, fireYellow);
    fillpoly(5, corePts);
    setcolor(WHITE);
    drawpoly(5, corePts);

    // --- 11. HIỆU ỨNG NĂNG LƯỢNG SÓNG LỬA CHẠY QUẤN QUANH KIẾM ---
    int numPts = 10;
    int energyLine1[20];
    int energyLine2[20];
    for (int i = 0; i < numPts; i++) {
        float t = (float)i / (float)(numPts - 1);
        float len = t * 140.0f; // Chạy dọc lưỡi kiếm
        
        // Sóng năng lượng vàng
        float wave1 = (float)sin(timeSec * 15.0f + t * 6.28f) * 11.0f;
        Vec2 ep1 = {len, wave1};
        Vec2 epr1 = applyAffine(ep1, cosA, sinA, swScale, swScale, handX, handY);
        energyLine1[i*2] = (int)epr1.x;
        energyLine1[i*2+1] = (int)epr1.y;

        // Sóng năng lượng cam (ngược pha)
        float wave2 = (float)cos(timeSec * 13.0f + t * 6.28f) * 11.0f;
        Vec2 ep2 = {len, wave2};
        Vec2 epr2 = applyAffine(ep2, cosA, sinA, swScale, swScale, handX, handY);
        energyLine2[i*2] = (int)epr2.x;
        energyLine2[i*2+1] = (int)epr2.y;
    }
    
    // Vẽ các dải năng lượng lửa xoắn ốc quấn quanh kiếm sinh động
    setlinestyle(SOLID_LINE, 0, 2);
    setcolor(fireYellow);
    for (int i = 0; i < numPts - 1; i++) {
        line(energyLine1[i*2], energyLine1[i*2+1], energyLine1[(i+1)*2], energyLine1[(i+1)*2+1]);
    }
    setcolor(fireOrange);
    for (int i = 0; i < numPts - 1; i++) {
        line(energyLine2[i*2], energyLine2[i*2+1], energyLine2[(i+1)*2], energyLine2[(i+1)*2+1]);
    }

    // Các tia chớp nhỏ phóng ra từ mũi kiếm rực rỡ
    for(int i = 0; i < 3; i++) {
        float sparkLen = 15.0f + (int)(sin(timeSec * 24.0f + i) * 6.0f);
        float sparkAng = angle + (i - 1) * 0.2f;
        Vec2 sparkTip = {150.0f + sparkLen, 0.0f};
        Vec2 sparkTipRot = applyAffine(sparkTip, cos(sparkAng), sin(sparkAng), swScale, swScale, handX, handY);
        setcolor(WHITE);
        setlinestyle(SOLID_LINE, 0, 1);
        line((int)b2r.x, (int)b2r.y, (int)sparkTipRot.x, (int)sparkTipRot.y);
    }

    setlinestyle(SOLID_LINE, 0, 1);
}

// Hiệu ứng chém kiếm lửa của Demon Boss
void drawBossSwordSlash(int bossX, int bossY, float scale, float progress) {
    int cx = bossX - S(50) - (int)(progress * (bossX + 120.0f));
    int cy = bossY - S(20);
    
    int size = S(90) + (int)(progress * S(40));
    int colors[] = { COLOR(180, 0, 0), COLOR(255, 100, 0), COLOR(255, 230, 80) };
    int thicknesses[] = { 10, 7, 4 };
    int radii[] = { size, size - 10, size - 20 };
    
    for (int i = 0; i < 3; i++) {
        if (radii[i] <= 0) continue;
        setcolor(colors[i]);
        setlinestyle(SOLID_LINE, 0, thicknesses[i]);
        // Vẽ vòng cung chém lửa quét sang trái
        arc(cx, cy, 90, 270, radii[i]);
        arc(cx - S(8), cy, 90, 270, radii[i]);
        
        if (i == 1) {
            // Vẽ các ngọn lửa nhỏ bắn ra từ vết chém
            setlinestyle(SOLID_LINE, 0, 3);
            for (int j = 0; j < 7; j++) {
                float angle = (100 + j * 24) * 3.1415926f / 180.0f;
                int sx = cx + (int)(cos(angle) * radii[i]);
                int sy = cy + (int)(sin(angle) * radii[i]);
                int ex = sx + (int)(cos(angle) * (22.0f * (1.0f + progress)));
                int ey = sy + (int)(sin(angle) * (22.0f * (1.0f + progress)));
                line(sx, sy, ex, ey);
            }
        }
    }
    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
