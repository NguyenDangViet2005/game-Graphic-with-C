#ifndef GAMEPLAY_RENDER_MAIN_CPP
#define GAMEPLAY_RENDER_MAIN_CPP

#include <graphics.h>
#include <math.h>
#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "../components/index.cpp"
#include "GameplayTypes.cpp"
#include "GameplayRender.cpp"

extern void* cachedGameBackground;

static void drawSwordSlashTrail(int cx, int cy, float scale, int facingRight, float progress) {
    if (progress <= 0.0f || progress >= 1.0f) return;
    
    // Sweep range in degrees
    float startAngle, endAngle;
    if (facingRight) {
        // Sweep from -80 to 80 degrees (counter-clockwise)
        startAngle = -80.0f;
        endAngle = 80.0f;
    } else {
        // Sweep from 260 to 100 degrees (clockwise)
        startAngle = 260.0f;
        endAngle = 100.0f;
    }

    float currentAngle = startAngle + progress * (endAngle - startAngle);
    float trailSize = 65.0f; // degrees of trail length

    // Calculate start and end of trail arc for BGI
    float arcStart, arcEnd;
    if (facingRight) {
        arcStart = currentAngle - trailSize;
        arcEnd = currentAngle;
        if (arcStart < startAngle) arcStart = startAngle;
    } else {
        // For facing left (clockwise sweep: 260 -> 100)
        // BGI draws counter-clockwise, so we draw from currentAngle to currentAngle + trailSize
        arcStart = currentAngle;
        arcEnd = currentAngle + trailSize;
        if (arcEnd > startAngle) arcEnd = startAngle;
    }

    // Scale the radii
    int rOuter = (int)(95 * scale);
    int rMid = (int)(88 * scale);
    int rInner = (int)(82 * scale);

    // Set line style for thick outer trail
    setlinestyle(SOLID_LINE, 0, 7);
    setcolor(COLOR(0, 180, 255)); // Blue outer glow
    arc(cx, cy, (int)arcStart, (int)arcEnd, rOuter);

    setlinestyle(SOLID_LINE, 0, 4);
    setcolor(COLOR(100, 230, 255)); // Cyan inner glow
    arc(cx, cy, (int)arcStart, (int)arcEnd, rMid);

    setlinestyle(SOLID_LINE, 0, 2);
    setcolor(COLOR(255, 255, 255)); // White core
    arc(cx, cy, (int)arcStart, (int)arcEnd, rInner);
    
    // Restore default linestyle
    setlinestyle(SOLID_LINE, 0, 1);
}

static void drawGameplay(const GameState& state) {
    setactivepage(state.page);
    putimage(0, 0, cachedGameBackground, COPY_PUT);
    drawForestSway(state.timeSec);
    drawFirefliesAnimated(state.timeSec);
    int ghostLimit = (state.bossState == 0) ? MAX_GHOSTS : 2;
    for (int i = 0; i < ghostLimit; i++) {
        if (!state.ghosts[i].active) continue;
        drawGhost((int)state.ghosts[i].x, (int)state.ghosts[i].y);
    }
    if (state.skillReady) {
        drawFootGlow((int)state.explorerX, (int)state.explorerY, state.explorerScale);
    }

    float slashProgress = 0.0f;
    if (state.isSlashing && state.swordSlashDuration > 0.0f) {
        slashProgress = (state.swordSlashDuration - state.swordSlashTime) / state.swordSlashDuration;
        if (slashProgress < 0.0f) slashProgress = 0.0f;
        if (slashProgress > 1.0f) slashProgress = 1.0f;
    }

    if (state.facingRight) {
        drawExplorer((int)state.explorerX, (int)state.explorerY, state.explorerScale, state.armSwing, state.headSway, state.currentWeapon, slashProgress);
    } else {
        drawExplorerMirrored((int)state.explorerX, (int)state.explorerY, state.explorerScale, state.armSwing, state.headSway, state.currentWeapon, slashProgress);
    }

    if (state.isSlashing) {
        float cx = state.explorerX + (state.facingRight ? 25.0f : -25.0f) * state.explorerScale;
        float cy = state.explorerY - 35.0f * state.explorerScale;
        drawSwordSlashTrail((int)cx, (int)cy, state.explorerScale, state.facingRight, slashProgress);
    }

    if (state.slowShieldActive) {
        drawSlowShield(state.explorerX, state.explorerY, state.timeSec);
    }
    for (int i = 0; i < MAX_ARROWS; i++) {
        if (!state.arrows[i].active) continue;
        drawArrowAffine(state.arrows[i].x, state.arrows[i].y, state.arrows[i].angle, state.arrows[i].scale);
    }
    for (int i = 0; i < MAX_FIREBALLS; i++) {
        if (!state.fireballs[i].active) continue;
        drawFireball(state.fireballs[i].x, state.fireballs[i].y);
    }
    for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
        if (!state.energyWaves[i].active) continue;
        if (state.energyWaves[i].type == 0) {
            int left = (state.energyWaves[i].dir > 0) ? (int)state.energyWaves[i].x : 0;
            int right = (state.energyWaves[i].dir > 0) ? SCREEN_WIDTH : (int)state.energyWaves[i].x;
            drawPowerAttack(left, right, (int)state.energyWaves[i].y, state.wavePhase);
        } else {
            float lifeRatio = state.energyWaves[i].life / 0.6f;
            if (lifeRatio < 0.0f) lifeRatio = 0.0f;
            if (lifeRatio > 1.0f) lifeRatio = 1.0f;
            drawGiantSwordAttack(state.energyWaves[i].x, state.energyWaves[i].y, lifeRatio, state.energyWaves[i].dir);
        }
    }

    if (state.bossState == 2) {
        char ditherPattern[] = { (char)0x11, (char)0x00, (char)0x44, (char)0x00, (char)0x11, (char)0x00, (char)0x44, (char)0x00 };
        int bossDimColor = COLOR(20, 20, 28);
        setfillpattern(ditherPattern, bossDimColor);
        bar(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    if (state.bossState == 1) {
        if (((int)(state.timeSec * 4.0f)) % 2 == 0) {
            setcolor(COLOR(255, 30, 30));
            settextstyle(BOLD_FONT, HORIZ_DIR, 4);
            const char* warnText = gCurrentLanguage->boss_warning;
            int wText = textwidth((char*)warnText);
            int bx1 = (SCREEN_WIDTH - wText) / 2 - 20;
            int by1 = SCREEN_HEIGHT / 2 - 60;
            int bx2 = (SCREEN_WIDTH + wText) / 2 + 20;
            int by2 = SCREEN_HEIGHT / 2 + 10;
            setfillstyle(SOLID_FILL, COLOR(20, 5, 5));
            bar(bx1, by1, bx2, by2);
            setcolor(COLOR(200, 20, 20));
            rectangle(bx1, by1, bx2, by2);
            setcolor(COLOR(255, 50, 50));
            setbkcolor(COLOR(20, 5, 5));
            outtextxy((SCREEN_WIDTH - wText) / 2, SCREEN_HEIGHT / 2 - 45, (char*)warnText);
            setbkcolor(BLACK);
        }
    } else if (state.bossState == 2) {
        drawSummonSigil((int)state.bossX, (int)(GROUND_Y - 80), 2.2f);
        float ratio = 1.0f - (state.bossSummonTimer / 2.5f);
        if (ratio < 0.0f) ratio = 0.0f;
        if (ratio > 1.0f) ratio = 1.0f;
        if (state.bossLevel % 2 == 0) {
            drawDemonBoss((int)state.bossX, (int)(GROUND_Y + 30), ratio, state.timeSec);
        } else {
            drawReaperBoss((int)state.bossX, (int)(GROUND_Y + 30), ratio, state.timeSec);
        }
    } else if (state.bossState == 3) {
        if (state.bossLevel % 2 == 0) {
            drawDemonBoss((int)state.bossX, (int)state.bossY, 1.0f, state.timeSec);
        } else {
            drawReaperBoss((int)state.bossX, (int)state.bossY, 1.0f, state.timeSec);
        }
        drawBossHealthBar(state.bossHp, state.bossMaxHp);

        if (state.bossAttackChargeTimer > 0.0f) {
            setcolor(COLOR(255, 0, 0));
            setlinestyle(DOTTED_LINE, 0, 2);
            int rx1 = 0;
            int rx2 = (int)(state.bossX - 40);
            int ry1 = (int)(GROUND_Y - 90);
            int ry2 = (int)(GROUND_Y + 30);
            rectangle(rx1, ry1, rx2, ry2);
            line(rx1, ry1, rx2, ry2);
            line(rx1, ry2, rx2, ry1);
            setlinestyle(SOLID_LINE, 0, 1);
            
            if (((int)(state.timeSec * 5.0f)) % 2 == 0) {
                setcolor(COLOR(255, 80, 80));
                settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                setbkcolor(COLOR(20, 5, 5));
                const char* chargeText = gCurrentLanguage->boss_dodge;
                outtextxy((int)(state.explorerX - 30), (int)(state.explorerY - 130), (char*)chargeText);
                setbkcolor(BLACK);
            }
        }

        if (state.bossAttackActiveTimer > 0.0f) {
            float progress = (0.4f - state.bossAttackActiveTimer) / 0.4f;
            if (state.bossLevel % 2 == 0) {
                drawBossSwordSlash((int)state.bossX, (int)state.bossY, 1.0f, progress);
            } else {
                drawBossScytheSlash((int)state.bossX, (int)state.bossY, progress);
            }
        }
    }

    drawGameStats(state.hp, state.score, state.mana, state.manaMax, state.skillReady, state.currentWeapon);
    drawPauseButton(state.pauseBtnX, state.pauseBtnY);

    setvisualpage(state.page);
}

#endif
