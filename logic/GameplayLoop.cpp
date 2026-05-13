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
        float arrowPulse = (float)sin(now * 0.008f);

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
        if ((GetAsyncKeyState(VK_UP) & 0x0001) && onGround) {
            explorerVy = jumpSpeed;
            playJump();
        }

        int moveDir = 0;
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) moveDir -= 1;
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) moveDir += 1;

        if (moveDir < 0) facingRight = 0;
        if (moveDir > 0) facingRight = 1;

        if (moveDir != 0) {
            explorerVx += moveDir * explorerAccel * dt;
            if (explorerVx > explorerSpeed) explorerVx = explorerSpeed;
            if (explorerVx < -explorerSpeed) explorerVx = -explorerSpeed;
        } else {
            if (explorerVx > 0.0f) {
                explorerVx -= explorerFriction * dt;
                if (explorerVx < 0.0f) explorerVx = 0.0f;
            } else if (explorerVx < 0.0f) {
                explorerVx += explorerFriction * dt;
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

        if (absVx > 5.0f) {
            walkTime += dt;
            float bob = (float)sin(walkTime * 8.0f) * 0.03f;
            explorerScale = 1.0f + bob;
        } else {
            explorerScale = 1.0f;
        }

        if (shootCooldown > 0.0f) shootCooldown -= dt;
        if ((GetAsyncKeyState(VK_SPACE) & 0x8000) && shootCooldown <= 0.0f) {
            for (int i = 0; i < MAX_ARROWS; i++) {
                if (!arrows[i].active) {
                    arrows[i].active = 1;
                    arrows[i].x = explorerX + (facingRight ? 52.0f : -52.0f);
                    arrows[i].y = explorerY - 30.0f;
                    arrows[i].vx = facingRight ? 620.0f : -620.0f;
                    arrows[i].vy = -30.0f;
                    arrows[i].angle = facingRight ? 0.0f : 3.1415926f;
                    arrows[i].scale = 1.0f;
                    shootCooldown = 0.2f;
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

            for (int g = 0; g < MAX_GHOSTS; g++) {
                if (!ghosts[g].active) continue;
                if (isArrowHitGhost(arrows[i], (int)ghosts[g].x, (int)ghosts[g].y)) {
                    arrows[i].active = 0;
                    ghosts[g].hp -= 1;
                    playDamage();
                    if (ghosts[g].hp <= 0) {
                        ghosts[g].active = 0;
                        score += 100;
                        playGetScore();
                    }
                    break;
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
        for (int i = 0; i < MAX_GHOSTS; i++) {
            if (!ghosts[i].active) continue;
            drawGhost((int)ghosts[i].x, (int)ghosts[i].y);
        }
        if (facingRight) {
            drawExplorer((int)explorerX, (int)explorerY, explorerScale);
        } else {
            drawExplorerMirrored((int)explorerX, (int)explorerY, explorerScale);
        }
        for (int i = 0; i < MAX_ARROWS; i++) {
            if (!arrows[i].active) continue;
            drawArrowAffine(arrows[i].x, arrows[i].y, arrows[i].angle, arrows[i].scale);
        }
        for (int i = 0; i < MAX_FIREBALLS; i++) {
            if (!fireballs[i].active) continue;
            drawFireball(fireballs[i].x, fireballs[i].y);
        }
        drawGameStats(hp, score);
        drawPauseButton(pauseBtnX, pauseBtnY);

        setvisualpage(page);
        page = 1 - page;
        delay(10);
    }
}

#endif
