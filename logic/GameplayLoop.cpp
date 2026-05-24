#ifndef GAMEPLAY_LOOP_CPP
#define GAMEPLAY_LOOP_CPP

#include <graphics.h>
#include <conio.h>
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "../components/index.cpp"
#include "../components/LoadingScreen.cpp"
#include "GameplayTypes.cpp"
#include "GameplayCollision.cpp"
#include "GameplayRender.cpp"

extern void* cachedGameBackground;

static void appendScoreToFile(int score) {
    FILE* fp = fopen("scores.txt", "a");
    if (!fp) {
        return;
    }
    fprintf(fp, "%d\n", score);
    fclose(fp);
}

static void initGameState(GameState& state) {
    state.hp = 3;
    state.score = 0;
    state.mana = 0;
    state.manaMax = 10;
    state.skillReady = 0;
    state.gameRunning = 1;
    state.pauseBtnX = SCREEN_WIDTH - 70;
    state.pauseBtnY = 20;

    state.explorerX = 200.0f;
    state.explorerY = (float)(GROUND_Y + 30);
    state.explorerVy = 0.0f;
    state.explorerSpeed = 280.0f;
    state.explorerVx = 0.0f;
    state.explorerAccel = 1600.0f;
    state.explorerFriction = 1400.0f;
    state.jumpSpeed = -620.0f;
    state.gravity = 1400.0f;
    state.groundY = (float)(GROUND_Y + 30);
    state.explorerScale = 1.0f;
    state.walkTime = 0.0f;
    state.armSwing = 0.0f;
    state.headSway = 0.0f;
    state.shootCooldown = 0.0f;
    state.hurtCooldown = 0.0f;
    state.facingRight = 1;

    state.ghostBaseY = (float)(GROUND_Y + 30);
    state.ghostSpawnTimer = 1.6f;
    state.ghostSpawnMin = 1.6f;
    state.ghostSpawnMax = 2.6f;

    for (int i = 0; i < MAX_ARROWS; i++) {
        state.arrows[i].active = 0;
    }
    for (int i = 0; i < MAX_GHOSTS; i++) {
        state.ghosts[i].active = 0;
    }
    for (int i = 0; i < MAX_FIREBALLS; i++) {
        state.fireballs[i].active = 0;
    }
    for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
        state.energyWaves[i].active = 0;
    }

    state.bossState = 0;
    state.bossWarningTimer = 0.0f;
    state.bossSummonTimer = 0.0f;
    state.bossX = 0.0f;
    state.bossY = 0.0f;
    state.bossLevel = 1;
    state.bossHp = 30;
    state.bossMaxHp = 30;
    state.nextBossScore = 3000;
    state.bossAttackCooldown = 3.0f;
    state.bossAttackChargeTimer = 0.0f;
    state.bossAttackActiveTimer = 0.0f;

    state.dt = 0.0f;
    state.timeSec = 0.0f;
    state.arrowPulse = 0.0f;
    state.wavePhase = 0.0f;
    state.page = 0;
}

static void initGameBackground() {
    if (cachedGameBackground == NULL) {
        playMusicLoading();
        drawLoadingScreen(0, gCurrentLanguage->loading_wait);
        delay(150);

        int oldPage = getactivepage();
        setactivepage(1);
        cleardevice();

        setactivepage(0);
        drawLoadingScreen(20, gCurrentLanguage->loading_text);
        setactivepage(1);
        delay(80);

        drawBackground();

        setactivepage(0);
        drawLoadingScreen(55, gCurrentLanguage->loading_forest);
        setactivepage(1);
        delay(80);

        drawDarkForest();

        setactivepage(0);
        drawLoadingScreen(85, gCurrentLanguage->loading_monsters);
        setactivepage(1);
        delay(80);

        unsigned int size = imagesize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        cachedGameBackground = malloc(size);
        getimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cachedGameBackground);

        setactivepage(0);
        drawLoadingScreen(95, gCurrentLanguage->loading_complete);
        delay(100);

        drawLoadingScreen(100, gCurrentLanguage->loading_start);
        delay(400);

        putimage(0, 0, cachedGameBackground, COPY_PUT);
        setactivepage(oldPage);
        playMusicPlay();
    } else {
        putimage(0, 0, cachedGameBackground, COPY_PUT);
        playMusicPlay();
    }
}

static void handleGameEvents(GameState& state) {
    if (ismouseclick(WM_LBUTTONDOWN)) {
        int mx, my;
        getmouseclick(WM_LBUTTONDOWN, mx, my);
        playClick();
        if (isClickOnPauseButton(mx, my, state.pauseBtnX, state.pauseBtnY)) {
            int choice = showPauseMenuOverlay();
            if (choice == 1) {
                state.gameRunning = 0;
            }
        }
    }

    if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
        int choice = showPauseMenuOverlay();
        if (choice == 1) {
            state.gameRunning = 0;
        }
    }
}

static void updateExplorer(GameState& state) {
    int onGround = (state.explorerY >= state.groundY - 0.5f);
    int shiftDown = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    int ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
    if ((GetAsyncKeyState(VK_UP) & 0x0001) && onGround && !ctrlDown) {
        float jumpMultiplier = shiftDown ? 1.5f : 1.0f;
        state.explorerVy = state.jumpSpeed * jumpMultiplier;
        playJump();
    }

    int moveDir = 0;
    if (GetAsyncKeyState(VK_LEFT) & 0x8000) moveDir -= 1;
    if (GetAsyncKeyState(VK_RIGHT) & 0x8000) moveDir += 1;

    if (moveDir < 0) state.facingRight = 0;
    if (moveDir > 0) state.facingRight = 1;

    float speedMultiplier = 1.0f;
    if (ctrlDown) {
        speedMultiplier = 0.3f;
    } else if (shiftDown) {
        speedMultiplier = 2.0f;
    }
    float effectiveSpeed = state.explorerSpeed * speedMultiplier;
    float effectiveAccel = state.explorerAccel * speedMultiplier;
    float effectiveFriction = state.explorerFriction * speedMultiplier;

    if (moveDir != 0) {
        state.explorerVx += moveDir * effectiveAccel * state.dt;
        if (state.explorerVx > effectiveSpeed) state.explorerVx = effectiveSpeed;
        if (state.explorerVx < -effectiveSpeed) state.explorerVx = -effectiveSpeed;
    } else {
        if (state.explorerVx > 0.0f) {
            state.explorerVx -= effectiveFriction * state.dt;
            if (state.explorerVx < 0.0f) state.explorerVx = 0.0f;
        } else if (state.explorerVx < 0.0f) {
            state.explorerVx += effectiveFriction * state.dt;
            if (state.explorerVx > 0.0f) state.explorerVx = 0.0f;
        }
    }

    state.explorerX += state.explorerVx * state.dt;
    if (state.explorerX < 80.0f) state.explorerX = 80.0f;
    if (state.explorerX > SCREEN_WIDTH - 80.0f) state.explorerX = (float)SCREEN_WIDTH - 80.0f;

    state.explorerVy += state.gravity * state.dt;
    state.explorerY += state.explorerVy * state.dt;
    if (state.explorerY > state.groundY) {
        state.explorerY = state.groundY;
        state.explorerVy = 0.0f;
    }

    float absVx = (float)fabs(state.explorerVx);
    if (absVx > 5.0f && onGround) {
        startRunLoop();
    } else {
        stopRunLoop();
    }

    state.armSwing = 0.0f;
    state.headSway = 0.0f;
    if (absVx > 5.0f) {
        state.walkTime += state.dt;
        float bob = (float)sin(state.walkTime * 8.0f) * 0.08f;
        state.explorerScale = 1.0f + bob;
        state.armSwing = (float)sin(state.walkTime * 7.0f) * 0.25f;
        state.headSway = (float)sin(state.walkTime * 4.0f) * 0.12f;
    } else {
        state.explorerScale = 1.0f;
        DWORD now = GetTickCount();
        state.armSwing = (float)sin(now * 0.003f) * 0.06f;
        state.headSway = (float)sin(now * 0.002f) * 0.05f;
    }
    if (!state.facingRight) {
        state.armSwing = -state.armSwing;
        state.headSway = -state.headSway;
    }
}

static void updateProjectiles(GameState& state) {
    int shiftDown = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    int spacePressed = (GetAsyncKeyState(VK_SPACE) & 0x0001) != 0;
    int skillShot = 0;

    if (state.skillReady && shiftDown && spacePressed) {
        int dir = state.facingRight ? 1 : -1;
        for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
            if (!state.energyWaves[i].active) {
                state.energyWaves[i].active = 1;
                state.energyWaves[i].x = state.explorerX + (dir > 0 ? 40.0f : -40.0f);
                state.energyWaves[i].y = state.explorerY - 30.0f;
                state.energyWaves[i].dir = dir;
                state.energyWaves[i].life = 1.0f;
                state.energyWaves[i].hitBoss = 0;
                state.mana = 0;
                state.skillReady = 0;
                playPowerFirer();
                skillShot = 1;
                break;
            }
        }
    }

    if (state.shootCooldown > 0.0f) state.shootCooldown -= state.dt;
    if (!skillShot && (GetAsyncKeyState(VK_SPACE) & 0x8000) && state.shootCooldown <= 0.0f) {
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (!state.arrows[i].active) {
                state.arrows[i].active = 1;
                state.arrows[i].x = state.explorerX + (state.facingRight ? 52.0f : -52.0f);
                state.arrows[i].y = state.explorerY - 30.0f;
                state.arrows[i].vx = state.facingRight ? 620.0f : -620.0f;
                state.arrows[i].vy = -30.0f;
                state.arrows[i].angle = state.facingRight ? 0.0f : 3.1415926f;
                state.arrows[i].scale = 1.0f;
                state.shootCooldown = 0.35f;
                playFire();
                break;
            }
        }
    }

    for (int i = 0; i < MAX_ARROWS; i++) {
        if (!state.arrows[i].active) continue;
        state.arrows[i].x += state.arrows[i].vx * state.dt;
        state.arrows[i].y += state.arrows[i].vy * state.dt;
        state.arrows[i].vy += 40.0f * state.dt;
        state.arrows[i].angle = (float)atan2(state.arrows[i].vy, state.arrows[i].vx);
        state.arrows[i].scale = 1.0f + state.arrowPulse * 0.08f;

        if (state.arrows[i].x > SCREEN_WIDTH + 50 || state.arrows[i].y < -50 || state.arrows[i].y > SCREEN_HEIGHT + 50) {
            state.arrows[i].active = 0;
            continue;
        }

        if (state.bossState == 3) {
            if (isArrowHitBoss(state.arrows[i], (int)state.bossX, (int)state.bossY)) {
                state.arrows[i].active = 0;
                state.bossHp -= 1;
                playDamage();
                continue;
            }
        }

        for (int g = 0; g < MAX_GHOSTS; g++) {
            if (!state.ghosts[g].active) continue;
            if (isArrowHitGhost(state.arrows[i], (int)state.ghosts[g].x, (int)state.ghosts[g].y)) {
                state.arrows[i].active = 0;
                state.ghosts[g].hp -= 1;
                playDamage();
                if (state.ghosts[g].hp <= 0) {
                    state.ghosts[g].active = 0;
                    state.score += 100;
                    state.mana += 1;
                    if (state.mana > state.manaMax) state.mana = state.manaMax;
                    if (state.mana >= state.manaMax) state.skillReady = 1;
                    playGetScore();
                }
                break;
            }
        }
    }

    for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
        if (!state.energyWaves[i].active) continue;
        state.energyWaves[i].life -= state.dt;
        if (state.energyWaves[i].life <= 0.0f) {
            state.energyWaves[i].active = 0;
            continue;
        }

        if (state.bossState == 3 && !state.energyWaves[i].hitBoss) {
            if (isEnergyWaveHitBoss(state.energyWaves[i], (int)state.bossX, (int)state.bossY)) {
                state.energyWaves[i].hitBoss = 1;
                state.bossHp -= 6;
                playDamage();
            }
        }

        for (int g = 0; g < MAX_GHOSTS; g++) {
            if (!state.ghosts[g].active) continue;
            if (isEnergyWaveHitGhost(state.energyWaves[i], (int)state.ghosts[g].x, (int)state.ghosts[g].y)) {
                state.ghosts[g].hp = 0;
                state.ghosts[g].active = 0;
                state.score += 100;
                state.mana += 1;
                if (state.mana > state.manaMax) state.mana = state.manaMax;
                if (state.mana >= state.manaMax) state.skillReady = 1;
                playGetScore();
            }
        }
    }
}

static void updateGhostsAndHazards(GameState& state) {
    state.ghostSpawnTimer -= state.dt;
    if (state.ghostSpawnTimer <= 0.0f) {
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!state.ghosts[i].active) {
                state.ghosts[i].active = 1;
                state.ghosts[i].x = (float)SCREEN_WIDTH + 120.0f;
                state.ghosts[i].y = state.ghostBaseY;
                state.ghosts[i].vx = -90.0f - (float)(rand() % 40);
                state.ghosts[i].shootTimer = 4.0f;
                state.ghosts[i].hp = 2;
                state.ghostSpawnTimer = state.ghostSpawnMin + ((float)rand() / (float)RAND_MAX) * (state.ghostSpawnMax - state.ghostSpawnMin);
                break;
            }
        }
    }

    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (!state.ghosts[i].active) continue;
        state.ghosts[i].x += state.ghosts[i].vx * state.dt;
        state.ghosts[i].shootTimer -= state.dt;

        if (state.ghosts[i].shootTimer <= 0.0f) {
            for (int f = 0; f < MAX_FIREBALLS; f++) {
                if (!state.fireballs[f].active) {
                    float dx = state.explorerX - state.ghosts[i].x;
                    float dy = (state.explorerY - 30.0f) - state.ghosts[i].y;
                    float len = (float)sqrt(dx * dx + dy * dy);
                    if (len < 1.0f) len = 1.0f;
                    float speed = 240.0f;
                    state.fireballs[f].active = 1;
                    state.fireballs[f].x = state.ghosts[i].x - 20.0f;
                    state.fireballs[f].y = state.ghosts[i].y - 20.0f;
                    state.fireballs[f].vx = (dx / len) * speed;
                    state.fireballs[f].vy = (dy / len) * speed;
                    state.ghosts[i].shootTimer = 4.0f;
                    break;
                }
            }
        }

        if (state.ghosts[i].x < -120.0f) {
            state.ghosts[i].active = 0;
        }
    }

    for (int i = 0; i < MAX_FIREBALLS; i++) {
        if (!state.fireballs[i].active) continue;
        state.fireballs[i].x += state.fireballs[i].vx * state.dt;
        state.fireballs[i].y += state.fireballs[i].vy * state.dt;
        if (state.fireballs[i].x < -50.0f || state.fireballs[i].x > SCREEN_WIDTH + 50.0f ||
            state.fireballs[i].y < -50.0f || state.fireballs[i].y > SCREEN_HEIGHT + 50.0f) {
            state.fireballs[i].active = 0;
        }
    }

    if (state.hurtCooldown > 0.0f) state.hurtCooldown -= state.dt;
    if (state.hurtCooldown <= 0.0f) {
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!state.ghosts[i].active) continue;
            if (isExplorerHitGhost(state.explorerX, state.explorerY, (int)state.ghosts[i].x, (int)state.ghosts[i].y)) {
                state.hp -= 1;
                state.hurtCooldown = 0.8f;
                playExplorerDamage();
                break;
            }
        }
    }

    if (state.hurtCooldown <= 0.0f) {
        for (int i = 0; i < MAX_FIREBALLS; i++) {
            if (!state.fireballs[i].active) continue;
            if (isExplorerHitFireball(state.explorerX, state.explorerY, state.fireballs[i].x, state.fireballs[i].y)) {
                state.fireballs[i].active = 0;
                state.hp -= 1;
                state.hurtCooldown = 0.8f;
                playExplorerDamage();
                break;
            }
        }
    }
}

static void updateBoss(GameState& state) {
    if (state.bossState == 0 && state.score >= state.nextBossScore) {
        state.bossState = 1;
        state.bossWarningTimer = 3.0f;
        state.explorerVx = 0.0f;
        state.explorerVy = 0.0f;
        stopRunLoop();
    }

    if (state.bossState == 1) {
        state.bossWarningTimer -= state.dt;
        if (state.bossWarningTimer <= 0.0f) {
            state.bossState = 2;
            state.bossSummonTimer = 2.5f;
            state.bossX = SCREEN_WIDTH - 220.0f;
            state.bossY = GROUND_Y + 30.0f;
            state.bossHp = state.bossMaxHp;
        }
    } else if (state.bossState == 2) {
        state.bossSummonTimer -= state.dt;
        if (state.bossSummonTimer <= 0.0f) {
            state.bossState = 3;
            state.bossAttackCooldown = 3.0f;
            state.bossAttackChargeTimer = 0.0f;
            state.bossAttackActiveTimer = 0.0f;
        }
    } else if (state.bossState == 3) {
        state.bossX = (SCREEN_WIDTH - 250.0f) + (float)sin(state.timeSec * 1.0f) * 80.0f;

        if (state.bossAttackChargeTimer > 0.0f) {
            state.bossAttackChargeTimer -= state.dt;
            if (state.bossAttackChargeTimer <= 0.0f) {
                state.bossAttackActiveTimer = 0.4f;
                playPowerFirer();
            }
        } else if (state.bossAttackActiveTimer > 0.0f) {
            state.bossAttackActiveTimer -= state.dt;
            float progress = (0.4f - state.bossAttackActiveTimer) / 0.4f;
            if (isExplorerHitBossAttack(state.explorerX, state.explorerY, state.bossX, state.bossY, progress)) {
                state.hp = 0;
            }
        } else {
            state.bossAttackCooldown -= state.dt;
            if (state.bossAttackCooldown <= 0.0f) {
                state.bossAttackChargeTimer = 1.2f;
                state.bossAttackCooldown = 5.0f;
            }
        }

        if (state.bossHp <= 0) {
            state.bossState = 0;
            state.score += 1000;
            playDeath();
            state.bossLevel++;
            if (state.bossLevel == 2) {
                state.nextBossScore = 10000;
                state.bossMaxHp = 50;
            } else if (state.bossLevel == 3) {
                state.nextBossScore = 15000;
                state.bossMaxHp = 60;
            } else if (state.bossLevel == 4) {
                state.nextBossScore = 20000;
                state.bossMaxHp = 100;
            } else {
                state.nextBossScore += 10000;
                state.bossMaxHp = 100;
            }
        }
    }
}

static void drawGameplay(const GameState& state) {
    setactivepage(state.page);
    putimage(0, 0, cachedGameBackground, COPY_PUT);
    drawForestSway(state.timeSec);
    drawFirefliesAnimated(state.timeSec);
    for (int i = 0; i < MAX_GHOSTS; i++) {
        if (!state.ghosts[i].active) continue;
        drawGhost((int)state.ghosts[i].x, (int)state.ghosts[i].y);
    }
    if (state.skillReady) {
        drawFootGlow((int)state.explorerX, (int)state.explorerY, state.explorerScale);
    }
    if (state.facingRight) {
        drawExplorer((int)state.explorerX, (int)state.explorerY, state.explorerScale, state.armSwing, state.headSway);
    } else {
        drawExplorerMirrored((int)state.explorerX, (int)state.explorerY, state.explorerScale, state.armSwing, state.headSway);
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
        int left = (state.energyWaves[i].dir > 0) ? (int)state.energyWaves[i].x : 0;
        int right = (state.energyWaves[i].dir > 0) ? SCREEN_WIDTH : (int)state.energyWaves[i].x;
        drawPowerAttack(left, right, (int)state.energyWaves[i].y, state.wavePhase);
    }

    if (state.bossState == 1 || state.bossState == 2) {
        char ditherPattern[] = { (char)0x55, (char)0xAA, (char)0x55, (char)0xAA, (char)0x55, (char)0xAA, (char)0x55, (char)0xAA };
        setfillpattern(ditherPattern, BLACK);
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
        drawReaperBoss((int)state.bossX, (int)(GROUND_Y + 30), ratio, state.timeSec);
    } else if (state.bossState == 3) {
        drawReaperBoss((int)state.bossX, (int)state.bossY, 1.0f, state.timeSec);
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
            drawBossScytheSlash((int)state.bossX, (int)state.bossY, progress);
        }
    }

    drawGameStats(state.hp, state.score, state.mana, state.manaMax, state.skillReady);
    drawPauseButton(state.pauseBtnX, state.pauseBtnY);

    setvisualpage(state.page);
}

void playGame() {
    cleardevice();

    initGameBackground();

    GameState state;
    initGameState(state);

    setactivepage(state.page);
    setvisualpage(state.page);

    DWORD lastTick = GetTickCount();

    srand((unsigned int)GetTickCount());

    while (kbhit()) getch();
    while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);

    while (state.gameRunning) {
        DWORD now = GetTickCount();
        float dt = (now - lastTick) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        lastTick = now;

        state.dt = dt;
        state.timeSec = now * 0.001f;
        state.arrowPulse = (float)sin(now * 0.008f);
        state.wavePhase = now * 0.02f;

        handleGameEvents(state);

        int isBossSpawning = (state.bossState == 1 || state.bossState == 2);
        if (!isBossSpawning) {
            updateExplorer(state);
            updateProjectiles(state);
            updateGhostsAndHazards(state);
        }

        updateBoss(state);

        if (state.hp <= 0) {
            appendScoreToFile(state.score);
            stopRunLoop();
            stopCurrentMusic();
            playDeath();
            showGameOverScreen(state.score);
            break;
        }

        drawGameplay(state);
        state.page = 1 - state.page;
        delay(10);
    }
}

#endif
