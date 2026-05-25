#ifndef GIANT_SWORD_ATTACK_H
#define GIANT_SWORD_ATTACK_H

#include <graphics.h>
#include <math.h>
#include "../algorithms/index.cpp"
#include "../logic/GameplayTypes.cpp"

void drawGiantSword(int x, int y, float scale, float angle, float opacityRatio) {
    float cosA = (float)cos(angle);
    float sinA = (float)sin(angle);

    int armorDark = COLOR(45, 50, 70);
    int goldMain = COLOR(240, 180, 40);
    int outlineColor = BLACK;

    Vec2 h0 = {-60.0f, 0.0f};
    Vec2 h1 = {0.0f, 0.0f};
    Vec2 g0 = {0.0f, -40.0f};
    Vec2 g1 = {0.0f, 40.0f};

    Vec2 b0 = {0.0f, -14.0f};
    Vec2 b1 = {160.0f, -14.0f};
    Vec2 b2 = {190.0f, 0.0f};
    Vec2 b3 = {160.0f, 14.0f};
    Vec2 b4 = {0.0f, 14.0f};

    Vec2 c0 = {2.0f, -7.0f};
    Vec2 c1 = {150.0f, -7.0f};
    Vec2 c2 = {175.0f, 0.0f};
    Vec2 c3 = {150.0f, 7.0f};
    Vec2 c4 = {2.0f, 7.0f};

    Vec2 h0r = applyAffine(h0, cosA, sinA, scale, scale, x, y);
    Vec2 h1r = applyAffine(h1, cosA, sinA, scale, scale, x, y);
    Vec2 g0r = applyAffine(g0, cosA, sinA, scale, scale, x, y);
    Vec2 g1r = applyAffine(g1, cosA, sinA, scale, scale, x, y);

    Vec2 b0r = applyAffine(b0, cosA, sinA, scale, scale, x, y);
    Vec2 b1r = applyAffine(b1, cosA, sinA, scale, scale, x, y);
    Vec2 b2r = applyAffine(b2, cosA, sinA, scale, scale, x, y);
    Vec2 b3r = applyAffine(b3, cosA, sinA, scale, scale, x, y);
    Vec2 b4r = applyAffine(b4, cosA, sinA, scale, scale, x, y);

    Vec2 c0r = applyAffine(c0, cosA, sinA, scale, scale, x, y);
    Vec2 c1r = applyAffine(c1, cosA, sinA, scale, scale, x, y);
    Vec2 c2r = applyAffine(c2, cosA, sinA, scale, scale, x, y);
    Vec2 c3r = applyAffine(c3, cosA, sinA, scale, scale, x, y);
    Vec2 c4r = applyAffine(c4, cosA, sinA, scale, scale, x, y);

    setlinestyle(SOLID_LINE, 0, (int)(4.0f * scale));
    setcolor(armorDark);
    line((int)h0r.x, (int)h0r.y, (int)h1r.x, (int)h1r.y);

    setlinestyle(SOLID_LINE, 0, (int)(5.0f * scale));
    setcolor(goldMain);
    line((int)g0r.x, (int)g0r.y, (int)g1r.x, (int)g1r.y);

    int bladePts[] = {
        (int)b0r.x, (int)b0r.y,
        (int)b1r.x, (int)b1r.y,
        (int)b2r.x, (int)b2r.y,
        (int)b3r.x, (int)b3r.y,
        (int)b4r.x, (int)b4r.y
    };
    setfillstyle(SOLID_FILL, COLOR(0, 220, 255));
    fillpoly(5, bladePts);
    setcolor(COLOR(120, 245, 255));
    setlinestyle(SOLID_LINE, 0, 1);
    drawpoly(5, bladePts);

    int corePts[] = {
        (int)c0r.x, (int)c0r.y,
        (int)c1r.x, (int)c1r.y,
        (int)c2r.x, (int)c2r.y,
        (int)c3r.x, (int)c3r.y,
        (int)c4r.x, (int)c4r.y
    };
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(5, corePts);

    setlinestyle(SOLID_LINE, 0, 1);
    setcolor(outlineColor);
}

void drawGiantSwordAttack(float strikeX, float groundY, float lifeRatio, int dir) {
    float t = 0.0f;
    float currentY = 0.0f;
    float angle = 0.0f;
    float scale = 3.5f;

    if (lifeRatio > 0.4f) {
        t = (1.0f - lifeRatio) / 0.6f;
        if (t < 0.0f) t = 0.0f;
        if (t > 1.0f) t = 1.0f;
        
        currentY = -300.0f + t * (groundY + 300.0f);
        angle = (dir > 0) ? (-1.5f + t * 2.2f) : (3.14159f + 1.5f - t * 2.2f);
        
        drawGiantSword((int)strikeX, (int)currentY, scale, angle, 1.0f);
    } else {
        t = (0.4f - lifeRatio) / 0.4f;
        currentY = groundY;
        angle = (dir > 0) ? 0.7f : (3.14159f - 0.7f);
        
        drawGiantSword((int)strikeX, (int)currentY, scale, angle, 1.0f);

        int rInner = (int)(t * 220.0f);

        setlinestyle(SOLID_LINE, 0, 8);
        setcolor(COLOR(0, 180, 255));
        ellipse((int)strikeX, (int)groundY, 0, 360, rInner, (int)(rInner * 0.28f));

        setlinestyle(SOLID_LINE, 0, 4);
        setcolor(COLOR(100, 230, 255));
        ellipse((int)strikeX, (int)groundY, 0, 360, (int)(rInner * 0.8f), (int)(rInner * 0.8f * 0.28f));

        setlinestyle(SOLID_LINE, 0, 1);
        setcolor(WHITE);
        ellipse((int)strikeX, (int)groundY, 0, 360, (int)(rInner * 0.5f), (int)(rInner * 0.5f * 0.28f));

        setcolor(COLOR(255, 120, 30));
        setlinestyle(SOLID_LINE, 0, 2);
        for (int a = 0; a < 360; a += 45) {
            float rad = a * 3.14159f / 180.0f;
            float cosR = (float)cos(rad);
            float sinR = (float)sin(rad);
            int x1 = (int)(strikeX + rInner * 0.3f * cosR);
            int y1 = (int)(groundY + rInner * 0.3f * sinR * 0.28f);
            int x2 = (int)(strikeX + rInner * 0.9f * cosR);
            int y2 = (int)(groundY + rInner * 0.9f * sinR * 0.28f);
            line(x1, y1, x2, y2);
        }

        setcolor(COLOR(100, 240, 255));
        setlinestyle(SOLID_LINE, 0, 3);
        int sparkHeight = (int)(150 * (1.0f - t));
        if (sparkHeight > 0) {
            line((int)strikeX, (int)groundY, (int)strikeX, (int)groundY - sparkHeight);
            line((int)strikeX - 50, (int)groundY, (int)strikeX - 50, (int)groundY - (int)(sparkHeight * 0.6f));
            line((int)strikeX + 50, (int)groundY, (int)strikeX + 50, (int)groundY - (int)(sparkHeight * 0.6f));
        }

        setlinestyle(SOLID_LINE, 0, 1);
    }
}

#endif
