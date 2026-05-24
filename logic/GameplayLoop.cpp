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

void playGame() {
    int hp = 3;
    int score = 0;
    int mana = 0;
    int manaMax = 10;
    int skillReady = 0;

    int gameRunning = 1;

    int pauseBtnX = SCREEN_WIDTH - 70;
    int pauseBtnY = 20;

    cleardevice();

    if (cachedGameBackground == NULL) {
        playMusicLoading();
        drawLoadingScreen(0, "Vui long cho...");
        delay(150);

        int oldPage = getactivepage();
        setactivepage(1);
        cleardevice();

        setactivepage(0);
        drawLoadingScreen(20, "Dang tai...");
        setactivepage(1);
        delay(80);

        drawBackground();

        setactivepage(0);
        drawLoadingScreen(55, "Dang tai khu rung...");
        setactivepage(1);
        delay(80);

        drawDarkForest();

        setactivepage(0);
        drawLoadingScreen(85, "Dang tai quai vat...");
        setactivepage(1);
        delay(80);

        unsigned int size = imagesize(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        cachedGameBackground = malloc(size);
        getimage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, cachedGameBackground);

        setactivepage(0);
        drawLoadingScreen(95, "Hoan thanh...");
        delay(100);

        drawLoadingScreen(100, "Bat dau!");
        delay(400);

        putimage(0, 0, cachedGameBackground, COPY_PUT);
        setactivepage(oldPage);
        playMusicPlay();
    } else {
        putimage(0, 0, cachedGameBackground, COPY_PUT);
        playMusicPlay();
    }

    float explorerX = 200.0f;
    float explorerY = (float)(GROUND_Y + 30);
    float explorerVy = 0.0f;
    float explorerSpeed = 280.0f;
    float explorerVx = 0.0f;
    float explorerAccel = 1600.0f;
    float explorerFriction = 1400.0f;
    float jumpSpeed = -620.0f;
    float gravity = 1400.0f;
    float groundY = (float)(GROUND_Y + 30);
    float explorerScale = 1.0f;
    float walkTime = 0.0f;
    float shootCooldown = 0.0f;
    float hurtCooldown = 0.0f;
    int facingRight = 1;

    float ghostBaseY = (float)(GROUND_Y + 30);
    float ghostSpawnTimer = 1.6f;
    float ghostSpawnMin = 1.6f;
    float ghostSpawnMax = 2.6f;

    Arrow arrows[MAX_ARROWS];
    for (int i = 0; i < MAX_ARROWS; i++) {
        arrows[i].active = 0;
    }

    GhostEnemy ghosts[MAX_GHOSTS];
    for (int i = 0; i < MAX_GHOSTS; i++) {
        ghosts[i].active = 0;
    }

    Fireball fireballs[MAX_FIREBALLS];
    for (int i = 0; i < MAX_FIREBALLS; i++) {
        fireballs[i].active = 0;
    }

    EnergyWave energyWaves[MAX_ENERGY_WAVES];
    for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
        energyWaves[i].active = 0;
    }

    // --- ReaperBoss variables ---
    int bossState = 0; // 0: None, 1: Warning, 2: Summoning, 3: Active
    float bossWarningTimer = 0.0f;
    float bossSummonTimer = 0.0f;
    float bossX = 0.0f;
    float bossY = 0.0f;
    int bossHp = 30;
    int bossMaxHp = 30;
    int nextBossScore = 3000;
    float bossAttackCooldown = 3.0f;
    float bossAttackChargeTimer = 0.0f;
    float bossAttackActiveTimer = 0.0f;

    int page = 0;
    setactivepage(page);
    setvisualpage(page);

    DWORD lastTick = GetTickCount();

    srand((unsigned int)GetTickCount());

    while (kbhit()) getch();
    while (ismouseclick(WM_LBUTTONDOWN)) clearmouseclick(WM_LBUTTONDOWN);

    while (gameRunning) {
        DWORD now = GetTickCount();
        float dt = (now - lastTick) / 1000.0f;
        if (dt > 0.05f) dt = 0.05f;
        lastTick = now;
        float timeSec = now * 0.001f;
        float arrowPulse = (float)sin(now * 0.008f);
        float wavePhase = now * 0.02f;

        if (ismouseclick(WM_LBUTTONDOWN)) {
            int mx, my;
            getmouseclick(WM_LBUTTONDOWN, mx, my);
            playClick();
            if (isClickOnPauseButton(mx, my, pauseBtnX, pauseBtnY)) {
                int choice = showPauseMenuOverlay();
                if (choice == 1) {
                    gameRunning = 0;
                }
            }
        }

        if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
            int choice = showPauseMenuOverlay();
            if (choice == 1) {
                gameRunning = 0;
            }
        }

        int onGround = (explorerY >= groundY - 0.5f);
        int shiftDown = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
        int ctrlDown = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;
        if ((GetAsyncKeyState(VK_UP) & 0x0001) && onGround && !ctrlDown) {
            float jumpMultiplier = shiftDown ? 1.5f : 1.0f;
            explorerVy = jumpSpeed * jumpMultiplier;
            playJump();
        }

        int moveDir = 0;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) moveDir -= 1;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) moveDir += 1;

        if (moveDir < 0) facingRight = 0;
        if (moveDir > 0) facingRight = 1;

        float speedMultiplier = 1.0f;
        if (ctrlDown) {
            speedMultiplier = 0.3f;
        } else if (shiftDown) {
            speedMultiplier = 2.0f;
        }
        float effectiveSpeed = explorerSpeed * speedMultiplier;
        float effectiveAccel = explorerAccel * speedMultiplier;
        float effectiveFriction = explorerFriction * speedMultiplier;

        if (moveDir != 0) {
            explorerVx += moveDir * effectiveAccel * dt;
            if (explorerVx > effectiveSpeed) explorerVx = effectiveSpeed;
            if (explorerVx < -effectiveSpeed) explorerVx = -effectiveSpeed;
        } else {
            if (explorerVx > 0.0f) {
                explorerVx -= effectiveFriction * dt;
                if (explorerVx < 0.0f) explorerVx = 0.0f;
            } else if (explorerVx < 0.0f) {
                explorerVx += effectiveFriction * dt;
                if (explorerVx > 0.0f) explorerVx = 0.0f;
            }
        }

        explorerX += explorerVx * dt;
        if (explorerX < 80.0f) explorerX = 80.0f;
        if (explorerX > SCREEN_WIDTH - 80.0f) explorerX = (float)SCREEN_WIDTH - 80.0f;

        explorerVy += gravity * dt;
        explorerY += explorerVy * dt;
        if (explorerY > groundY) {
            explorerY = groundY;
            explorerVy = 0.0f;
        }

        float absVx = (float)fabs(explorerVx);
        if (absVx > 5.0f && onGround) {
            startRunLoop();
        } else {
            stopRunLoop();
        }

        float armSwing = 0.0f;
        float headSway = 0.0f;
        if (absVx > 5.0f) {
            walkTime += dt;
            float bob = (float)sin(walkTime * 8.0f) * 0.08f;
            explorerScale = 1.0f + bob;
            armSwing = (float)sin(walkTime * 7.0f) * 0.25f;
            headSway = (float)sin(walkTime * 4.0f) * 0.12f;
        } else {
            explorerScale = 1.0f;
            armSwing = (float)sin(now * 0.003f) * 0.06f;
            headSway = (float)sin(now * 0.002f) * 0.05f;
        }
        if (!facingRight) {
            armSwing = -armSwing;
            headSway = -headSway;
        }

        int spacePressed = (GetAsyncKeyState(VK_SPACE) & 0x0001) != 0;
        int skillShot = 0;
        if (skillReady && shiftDown && spacePressed) {
            int dir = facingRight ? 1 : -1;
            for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
                if (!energyWaves[i].active) {
                    energyWaves[i].active = 1;
                    energyWaves[i].x = explorerX + (dir > 0 ? 40.0f : -40.0f);
                    energyWaves[i].y = explorerY - 30.0f;
                    energyWaves[i].dir = dir;
                    energyWaves[i].life = 1.0f;
                    energyWaves[i].hitBoss = 0;
                    mana = 0;
                    skillReady = 0;
                    playPowerFirer();
                    skillShot = 1;
                    break;
                }
            }
        }

        if (shootCooldown > 0.0f) shootCooldown -= dt;
        if (!skillShot && (GetAsyncKeyState(VK_SPACE) & 0x8000) && shootCooldown <= 0.0f) {
            for (int i = 0; i < MAX_ARROWS; i++) {
                if (!arrows[i].active) {
                    arrows[i].active = 1;
                    arrows[i].x = explorerX + (facingRight ? 52.0f : -52.0f);
                    arrows[i].y = explorerY - 30.0f;
                    arrows[i].vx = facingRight ? 620.0f : -620.0f;
                    arrows[i].vy = -30.0f;
                    arrows[i].angle = facingRight ? 0.0f : 3.1415926f;
                    arrows[i].scale = 1.0f;
                    shootCooldown = 0.35f;
                    playFire();
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_ARROWS; i++) {
            if (!arrows[i].active) continue;
            arrows[i].x += arrows[i].vx * dt;
            arrows[i].y += arrows[i].vy * dt;
            arrows[i].vy += 40.0f * dt;
            arrows[i].angle = (float)atan2(arrows[i].vy, arrows[i].vx);
            arrows[i].scale = 1.0f + arrowPulse * 0.08f;

            if (arrows[i].x > SCREEN_WIDTH + 50 || arrows[i].y < -50 || arrows[i].y > SCREEN_HEIGHT + 50) {
                arrows[i].active = 0;
                continue;
            }

            if (bossState == 3) {
                if (isArrowHitBoss(arrows[i], (int)bossX, (int)bossY)) {
                    arrows[i].active = 0;
                    bossHp -= 1;
                    playDamage();
                    continue;
                }
            }

            for (int g = 0; g < MAX_GHOSTS; g++) {
                if (!ghosts[g].active) continue;
                if (isArrowHitGhost(arrows[i], (int)ghosts[g].x, (int)ghosts[g].y)) {
                    arrows[i].active = 0;
                    ghosts[g].hp -= 1;
                    playDamage();
                    if (ghosts[g].hp <= 0) {
                        ghosts[g].active = 0;
                        score += 100;
                        mana += 1;
                        if (mana > manaMax) mana = manaMax;
                        if (mana >= manaMax) skillReady = 1;
                        playGetScore();
                    }
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
            if (!energyWaves[i].active) continue;
            energyWaves[i].life -= dt;
            if (energyWaves[i].life <= 0.0f) {
                energyWaves[i].active = 0;
                continue;
            }

            if (bossState == 3 && !energyWaves[i].hitBoss) {
                if (isEnergyWaveHitBoss(energyWaves[i], (int)bossX, (int)bossY)) {
                    energyWaves[i].hitBoss = 1;
                    bossHp -= 6;
                    playDamage();
                }
            }

            for (int g = 0; g < MAX_GHOSTS; g++) {
                if (!ghosts[g].active) continue;
                if (isEnergyWaveHitGhost(energyWaves[i], (int)ghosts[g].x, (int)ghosts[g].y)) {
                    ghosts[g].hp = 0;
                    ghosts[g].active = 0;
                    score += 100;
                    mana += 1;
                    if (mana > manaMax) mana = manaMax;
                    if (mana >= manaMax) skillReady = 1;
                    playGetScore();
                }
            }
        }

        ghostSpawnTimer -= dt;
        if (ghostSpawnTimer <= 0.0f) {
            for (int i = 0; i < MAX_GHOSTS; i++) {
                if (!ghosts[i].active) {
                    ghosts[i].active = 1;
                    ghosts[i].x = (float)SCREEN_WIDTH + 120.0f;
                    ghosts[i].y = ghostBaseY;
                    ghosts[i].vx = -90.0f - (float)(rand() % 40);
                    ghosts[i].shootTimer = 4.0f;
                    ghosts[i].hp = 2;
                    ghostSpawnTimer = ghostSpawnMin + ((float)rand() / (float)RAND_MAX) * (ghostSpawnMax - ghostSpawnMin);
                    break;
                }
            }
        }

        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!ghosts[i].active) continue;
            ghosts[i].x += ghosts[i].vx * dt;
            ghosts[i].shootTimer -= dt;

            if (ghosts[i].shootTimer <= 0.0f) {
                for (int f = 0; f < MAX_FIREBALLS; f++) {
                    if (!fireballs[f].active) {
                        float dx = explorerX - ghosts[i].x;
                        float dy = (explorerY - 30.0f) - ghosts[i].y;
                        float len = (float)sqrt(dx * dx + dy * dy);
                        if (len < 1.0f) len = 1.0f;
                        float speed = 240.0f;
                        fireballs[f].active = 1;
                        fireballs[f].x = ghosts[i].x - 20.0f;
                        fireballs[f].y = ghosts[i].y - 20.0f;
                        fireballs[f].vx = (dx / len) * speed;
                        fireballs[f].vy = (dy / len) * speed;
                        ghosts[i].shootTimer = 4.0f;
                        break;
                    }
                }
            }

            if (ghosts[i].x < -120.0f) {
                ghosts[i].active = 0;
            }
        }

        for (int i = 0; i < MAX_FIREBALLS; i++) {
            if (!fireballs[i].active) continue;
            fireballs[i].x += fireballs[i].vx * dt;
            fireballs[i].y += fireballs[i].vy * dt;
            if (fireballs[i].x < -50.0f || fireballs[i].x > SCREEN_WIDTH + 50.0f ||
                fireballs[i].y < -50.0f || fireballs[i].y > SCREEN_HEIGHT + 50.0f) {
                fireballs[i].active = 0;
            }
        }

        if (hurtCooldown > 0.0f) hurtCooldown -= dt;
        if (hurtCooldown <= 0.0f) {
            for (int i = 0; i < MAX_GHOSTS; i++) {
                if (!ghosts[i].active) continue;
                if (isExplorerHitGhost(explorerX, explorerY, (int)ghosts[i].x, (int)ghosts[i].y)) {
                    hp -= 1;
                    hurtCooldown = 0.8f;
                    playExplorerDamage();
                    break;
                }
            }
        }

        if (hurtCooldown <= 0.0f) {
            for (int i = 0; i < MAX_FIREBALLS; i++) {
                if (!fireballs[i].active) continue;
                if (isExplorerHitFireball(explorerX, explorerY, fireballs[i].x, fireballs[i].y)) {
                    fireballs[i].active = 0;
                    hp -= 1;
                    hurtCooldown = 0.8f;
                    playExplorerDamage();
                    break;
                }
            }
        }

        // --- ReaperBoss Update Logic ---
        if (bossState == 0 && score >= nextBossScore) {
            bossState = 1;
            bossWarningTimer = 3.0f;
        }

        if (bossState == 1) {
            bossWarningTimer -= dt;
            if (bossWarningTimer <= 0.0f) {
                bossState = 2;
                bossSummonTimer = 2.5f;
                bossX = SCREEN_WIDTH - 220.0f;
                bossY = GROUND_Y + 30.0f;
                bossHp = 30;
            }
        } else if (bossState == 2) {
            bossSummonTimer -= dt;
            if (bossSummonTimer <= 0.0f) {
                bossState = 3;
                bossAttackCooldown = 3.0f;
                bossAttackChargeTimer = 0.0f;
                bossAttackActiveTimer = 0.0f;
            }
        } else if (bossState == 3) {
            // Hover horizontally
            bossX = (SCREEN_WIDTH - 250.0f) + (float)sin(timeSec * 1.0f) * 80.0f;

            // Attack cycle
            if (bossAttackChargeTimer > 0.0f) {
                bossAttackChargeTimer -= dt;
                if (bossAttackChargeTimer <= 0.0f) {
                    bossAttackActiveTimer = 0.4f;
                    playPowerFirer();
                }
            } else if (bossAttackActiveTimer > 0.0f) {
                bossAttackActiveTimer -= dt;
                if (isExplorerHitBossAttack(explorerX, explorerY, bossX, bossY)) {
                    hp = 0; // Instant defeat
                }
            } else {
                bossAttackCooldown -= dt;
                if (bossAttackCooldown <= 0.0f) {
                    bossAttackChargeTimer = 1.2f;
                    bossAttackCooldown = 5.0f;
                }
            }

            // Defeat check
            if (bossHp <= 0) {
                bossState = 0;
                score += 1000;
                playDeath();
                if (nextBossScore == 3000) {
                    nextBossScore = 10000;
                } else {
                    nextBossScore = nextBossScore + 10000;
                }
            }
        }

        if (hp <= 0) {
            appendScoreToFile(score);
            stopRunLoop();
            stopCurrentMusic();
            playDeath();
            showGameOverScreen(score);
            break;
        }

        setactivepage(page);
        putimage(0, 0, cachedGameBackground, COPY_PUT);
        drawForestSway(timeSec);
        drawFirefliesAnimated(timeSec);
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!ghosts[i].active) continue;
            drawGhost((int)ghosts[i].x, (int)ghosts[i].y);
        }
        if (skillReady) {
            drawFootGlow((int)explorerX, (int)explorerY, explorerScale);
        }
        if (facingRight) {
            drawExplorer((int)explorerX, (int)explorerY, explorerScale, armSwing, headSway);
        } else {
            drawExplorerMirrored((int)explorerX, (int)explorerY, explorerScale, armSwing, headSway);
        }
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (!arrows[i].active) continue;
            drawArrowAffine(arrows[i].x, arrows[i].y, arrows[i].angle, arrows[i].scale);
        }
        for (int i = 0; i < MAX_FIREBALLS; i++) {
            if (!fireballs[i].active) continue;
            drawFireball(fireballs[i].x, fireballs[i].y);
        }
        for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
            if (!energyWaves[i].active) continue;
            int left = (energyWaves[i].dir > 0) ? (int)energyWaves[i].x : 0;
            int right = (energyWaves[i].dir > 0) ? SCREEN_WIDTH : (int)energyWaves[i].x;
            drawPowerAttack(left, right, (int)energyWaves[i].y, wavePhase);
        }

        // --- ReaperBoss Render Logic ---
        if (bossState == 1) { // Warning State
            if (((int)(timeSec * 4.0f)) % 2 == 0) {
                setcolor(COLOR(255, 30, 30));
                settextstyle(BOLD_FONT, HORIZ_DIR, 4);
                char warnText[] = "CANH BAO: REAPER BOSS SAP XUAT HIEN!";
                int wText = textwidth(warnText);
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
                outtextxy((SCREEN_WIDTH - wText) / 2, SCREEN_HEIGHT / 2 - 45, warnText);
                setbkcolor(BLACK); // Restore bkcolor
            }
        } else if (bossState == 2) { // Summoning State
            drawSummonSigil((int)bossX, (int)(GROUND_Y - 80), 2.2f);
            float ratio = 1.0f - (bossSummonTimer / 2.5f);
            if (ratio < 0.0f) ratio = 0.0f;
            if (ratio > 1.0f) ratio = 1.0f;
            drawReaperBoss((int)bossX, (int)(GROUND_Y + 30), ratio, timeSec);
        } else if (bossState == 3) { // Active State
            drawReaperBoss((int)bossX, (int)bossY, 1.0f, timeSec);
            drawBossHealthBar(bossHp, bossMaxHp);

            // Warning indicators for active attack charge
            if (bossAttackChargeTimer > 0.0f) {
                setcolor(COLOR(255, 0, 0));
                setlinestyle(DOTTED_LINE, 0, 2);
                int rx1 = 0;
                int rx2 = (int)(bossX - 40);
                int ry1 = (int)(GROUND_Y - 90);
                int ry2 = (int)(GROUND_Y + 30);
                rectangle(rx1, ry1, rx2, ry2);
                line(rx1, ry1, rx2, ry2);
                line(rx1, ry2, rx2, ry1);
                setlinestyle(SOLID_LINE, 0, 1);
                
                if (((int)(timeSec * 5.0f)) % 2 == 0) {
                    setcolor(COLOR(255, 80, 80));
                    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
                    setbkcolor(COLOR(20, 5, 5));
                    char chargeText[] = "NE DON!";
                    outtextxy((int)(explorerX - 30), (int)(explorerY - 130), chargeText);
                    setbkcolor(BLACK); // Restore bkcolor
                }
            }

            // Draw active attack slash
            if (bossAttackActiveTimer > 0.0f) {
                float progress = (0.4f - bossAttackActiveTimer) / 0.4f;
                drawBossScytheSlash((int)bossX, (int)bossY, progress);
            }
        }

        drawGameStats(hp, score, mana, manaMax, skillReady);
        drawPauseButton(pauseBtnX, pauseBtnY);

        setvisualpage(page);
        page = 1 - page;
        delay(10);
    }
}

#endif
