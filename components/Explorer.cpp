#ifndef EXPLORER_H
#define EXPLORER_H

#include <graphics.h>

#define S(val) ((int)((val) * scale)) // macro scale tọa độ

void drawExplorer(int x, int y, float scale = 1.0f) {
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
    
    // quầng sáng dưới chân
    setcolor(goldDark);
    setlinestyle(SOLID_LINE, 0, thickBold);
    ellipse(x, y, 0, 360, S(48), S(14));
    setcolor(goldMain);
    setlinestyle(SOLID_LINE, 0, thickNormal);
    ellipse(x, y, 0, 360, S(56), S(18));
    setcolor(glowColor);
    ellipse(x, y, 0, 360, S(40), S(10));

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
    line(quiverX+S(2), quiverY-S(12), quiverX-S(8), quiverY-S(30));
    line(quiverX+S(6), quiverY-S(9), quiverX-S(2), quiverY-S(32));
    line(quiverX+S(10), quiverY-S(6), quiverX+S(4), quiverY-S(28));
    
    // lông tên đỏ
    setcolor(gemColor);
    line(quiverX-S(8), quiverY-S(30), quiverX-S(12), quiverY-S(27));
    line(quiverX-S(2), quiverY-S(32), quiverX-S(6), quiverY-S(29));
    line(quiverX+S(4), quiverY-S(28), quiverX, quiverY-S(25));
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
    fillellipse(x - S(24), y - S(12), S(6), S(6));
    circle(x - S(24), y - S(12), S(6));

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
    line(x+S(3), y-S(28), x+S(22), y-S(28));
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
    
    // viền vàng chữ v trên ngực
    setcolor(goldMain);
    setlinestyle(SOLID_LINE, 0, thickBold);
    line(x-S(18), y-S(40), x+S(4), y-S(25));
    line(x+S(18), y-S(40), x+S(4), y-S(25));
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // đai lưng
    setfillstyle(SOLID_FILL, goldDark);
    bar(x-S(18), y-S(25), x+S(18), y-S(15));
    rectangle(x-S(18), y-S(25), x+S(18), y-S(15));

    // ngọc đỏ trên đai
    setcolor(outlineColor);
    setfillstyle(SOLID_FILL, goldMain);
    fillellipse(x+S(4), y-S(20), S(8), S(8)); 
    circle(x+S(4), y-S(20), S(8));
    setfillstyle(SOLID_FILL, gemColor);
    fillellipse(x+S(4), y-S(20), S(5), S(5));

    // giáp háng
    setfillstyle(SOLID_FILL, armorMain);
    int groin[] = {x-S(10), y-S(15), x+S(14), y-S(15), x+S(10), y-S(5), x-S(2), y-S(5)};
    fillpoly(4, groin); drawpoly(4, groin);
    setcolor(goldMain);
    line(x-S(10), y-S(15), x-S(2), y-S(5));
    line(x+S(14), y-S(15), x+S(10), y-S(5));
    setcolor(outlineColor);

    // tay phải cầm cung
    setfillstyle(SOLID_FILL, armorMain);
    int armR[] = {x+S(15), y-S(40), x+S(30), y-S(40), x+S(40), y-S(30), x+S(25), y-S(30)};
    fillpoly(4, armR); drawpoly(4, armR);

    // nắm tay phải
    setfillstyle(SOLID_FILL, armorDark);
    fillellipse(x+S(40), y-S(30), S(7), S(7));
    circle(x+S(40), y-S(30), S(7));

    // cung tên
    int bowX = x + S(40);
    int bowY = y - S(30);
    setlinestyle(SOLID_LINE, 0, thickBold);
    
    setcolor(goldMain);
    arc(bowX - S(10), bowY, 280, 80, S(25));
    setcolor(armorDark);
    arc(bowX - S(12), bowY, 285, 75, S(23));
    
    // tay cầm cung
    setfillstyle(SOLID_FILL, armorDark);
    bar(bowX-S(2), bowY-S(6), bowX+S(5), bowY+S(6));
    setcolor(outlineColor);
    rectangle(bowX-S(2), bowY-S(6), bowX+S(5), bowY+S(6));
    setfillstyle(SOLID_FILL, gemColor);
    fillellipse(bowX+S(1), bowY, S(2), S(2));

    // dây cung
    setcolor(glowColor);
    setlinestyle(SOLID_LINE, 0, thickNormal); 
    line(bowX - S(4), bowY - S(24), bowX - S(14), bowY);
    line(bowX - S(4), bowY + S(24), bowX - S(14), bowY);
    
    // mũi tên năng lượng
    setcolor(goldLight);
    setlinestyle(SOLID_LINE, 0, thickBold);
    line(bowX - S(14), bowY, bowX + S(16), bowY);
    
    // đầu mũi tên
    setfillstyle(SOLID_FILL, eyeColor);
    int arrowHead[] = {bowX+S(16), bowY, bowX+S(10), bowY-S(4), bowX+S(13), bowY, bowX+S(10), bowY+S(4)};
    fillpoly(4, arrowHead);
    setcolor(glowColor);
    drawpoly(4, arrowHead);

    setlinestyle(SOLID_LINE, 0, thickNormal); 
    setcolor(outlineColor);

    // đầu và mũ
    int headX = x;
    int headY = y - S(65);

    // giáp vai
    setfillstyle(SOLID_FILL, armorDark);
    int shoulderL[] = {x-S(16), y-S(50), x-S(28), y-S(45), x-S(34), y-S(30), x-S(18), y-S(35)};
    fillpoly(4, shoulderL); drawpoly(4, shoulderL);
    setcolor(goldMain);
    line(x-S(28), y-S(45), x-S(34), y-S(30)); 
    setcolor(outlineColor);

    setfillstyle(SOLID_FILL, armorDark);
    int shoulderR[] = {x+S(16), y-S(50), x+S(28), y-S(45), x+S(34), y-S(30), x+S(18), y-S(35)};
    fillpoly(4, shoulderR); drawpoly(4, shoulderR);
    setcolor(goldMain);
    line(x+S(28), y-S(45), x+S(34), y-S(30));
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
    fillpoly(8, helmet); drawpoly(8, helmet);

    // giáp cằm
    int helmetBottom[] = {
        headX - S(22), headY + S(15),
        headX - S(15), headY + S(30),
        headX + S(15), headY + S(30),
        headX + S(22), headY + S(15),
        headX + S(10), headY + S(25),
        headX - S(10), headY + S(25)
    };
    fillpoly(6, helmetBottom); drawpoly(6, helmetBottom);

    // cặp sừng
    setfillstyle(SOLID_FILL, armorDark);
    int hornL[] = {headX-S(22), headY-S(5), headX-S(38), headY-S(35), headX-S(15), headY-S(22)};
    fillpoly(3, hornL); drawpoly(3, hornL);
    setcolor(armorMain);
    line(headX-S(22), headY-S(5), headX-S(29), headY-S(22)); 
    setcolor(outlineColor);

    int hornR[] = {headX+S(22), headY-S(5), headX+S(38), headY-S(35), headX+S(15), headY-S(22)};
    fillpoly(3, hornR); drawpoly(3, hornR);
    setcolor(armorMain);
    line(headX+S(22), headY-S(5), headX+S(29), headY-S(22));
    setcolor(outlineColor);

    // chóp mũ có ngọc
    int crest[] = {headX-S(2), headY-S(23), headX+S(10), headY-S(42), headX+S(14), headY-S(23)};
    setfillstyle(SOLID_FILL, armorMain);
    fillpoly(3, crest); drawpoly(3, crest);

    setfillstyle(SOLID_FILL, goldDark);
    fillellipse(headX+S(6), headY - S(18), S(6), S(8));
    setfillstyle(SOLID_FILL, gemColor);
    fillellipse(headX+S(6), headY - S(18), S(4), S(6));

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
    fillpoly(7, visor);
    
    // viền khe nhìn
    setcolor(armorMain);
    setlinestyle(SOLID_LINE, 0, thickBold);
    for(int i=0; i<6; i++) {
        line(visor[i*2], visor[i*2+1], visor[i*2+2], visor[i*2+3]);
    }
    line(visor[12], visor[13], visor[0], visor[1]);
    
    // đôi mắt phát sáng
    setcolor(outlineColor);
    setlinestyle(SOLID_LINE, 0, thickNormal);
    setfillstyle(SOLID_FILL, eyeColor);
    
    int eyeL[] = {headX - S(5), headY + S(6), headX + S(4), headY + S(8), headX, headY + S(12)};
    fillpoly(3, eyeL);
    
    int eyeR[] = {headX + S(23), headY + S(6), headX + S(15), headY + S(8), headX + S(19), headY + S(11)};
    fillpoly(3, eyeR);

    setcolor(glowColor);
    drawpoly(3, eyeL);
    drawpoly(3, eyeR);

    setlinestyle(SOLID_LINE, 0, 1);
}

#endif
