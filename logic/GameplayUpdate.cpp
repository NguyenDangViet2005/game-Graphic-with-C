#ifndef GAMEPLAY_UPDATE_CPP
#define GAMEPLAY_UPDATE_CPP

#include <graphics.h>
#include <math.h>
#include <windows.h>
#include <stdlib.h>
#include "../configs/Config.cpp"
#include "../configs/Audio.cpp"
#include "GameplayTypes.cpp"
#include "GameplayCollision.cpp"

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

    if (GetAsyncKeyState(0x43) & 0x0001) { // 'C' key
        if (!state.isSlashing) {
            state.currentWeapon = 1 - state.currentWeapon;
            playClick();
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
    int wantsShield = (ctrlDown && moveDir != 0) ? 1 : 0;
    if (wantsShield && !state.slowShieldWasActive) {
        if (state.mana > 0) {
            state.mana -= 1;
            if (state.mana < 0) state.mana = 0;
            state.skillReady = (state.mana >= state.manaMax) ? 1 : 0;
            state.slowShieldActive = 1;
        } else {
            state.slowShieldActive = 0;
        }
    } else if (wantsShield) {
        state.slowShieldActive = 1;
    } else {
        state.slowShieldActive = 0;
    }
    state.slowShieldWasActive = state.slowShieldActive;
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
    if (state.isSlashing) {
        state.swordSlashTime -= state.dt;
        if (state.swordSlashTime <= 0.0f) {
            state.isSlashing = 0;
            state.swordSlashTime = 0.0f;
        }
    }

    int shiftDown = (GetAsyncKeyState(VK_SHIFT) & 0x8000) != 0;
    int spacePressed = (GetAsyncKeyState(VK_SPACE) & 0x0001) != 0;
    int skillShot = 0;

    if (spacePressed) {
        float delta = state.timeSec - state.lastSpacePressTime;
        if (delta > 0.0f && delta < 0.25f) {
            state.rapidSpaceCount += 1;
        } else {
            state.rapidSpaceCount = 0;
        }
        state.lastSpacePressTime = state.timeSec;
        if (state.rapidSpaceCount >= 6) {
            state.spaceSpamStop = 1;
            return;
        }
    }

    if (state.skillReady && shiftDown && spacePressed) {
        int dir = state.facingRight ? 1 : -1;
        for (int i = 0; i < MAX_ENERGY_WAVES; i++) {
            if (!state.energyWaves[i].active) {
                state.energyWaves[i].active = 1;
                state.energyWaves[i].dir = dir;
                state.energyWaves[i].hitBoss = 0;
                state.energyWaves[i].type = state.currentWeapon;
                
                if (state.currentWeapon == 0) {
                    state.energyWaves[i].x = state.explorerX + (dir > 0 ? 40.0f : -40.0f);
                    state.energyWaves[i].y = state.explorerY - 30.0f;
                    state.energyWaves[i].life = 1.0f;
                } else {
                    state.energyWaves[i].x = state.explorerX + (dir > 0 ? 150.0f : -150.0f);
                    state.energyWaves[i].y = state.explorerY;
                    state.energyWaves[i].life = 0.6f;
                }
                
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
        if (state.currentWeapon == 0) {
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
        } else {
            // Sword melee attack
            state.isSlashing = 1;
            state.swordSlashTime = state.swordSlashDuration;
            state.shootCooldown = 0.35f;
            playFire(); // Play slash whoosh sound

            // Melee collision checks
            int ghostLimit = (state.bossState == 0) ? MAX_GHOSTS : 2;
            for (int g = 0; g < ghostLimit; g++) {
                if (!state.ghosts[g].active) continue;
                if (isSwordHitGhost(state.explorerX, state.explorerY, state.facingRight, (int)state.ghosts[g].x, (int)state.ghosts[g].y)) {
                    state.ghosts[g].hp -= 2;
                    playDamage();
                    if (state.ghosts[g].hp <= 0) {
                        state.ghosts[g].active = 0;
                        state.score += 100;
                        state.mana += 2;
                        if (state.mana > state.manaMax) state.mana = state.manaMax;
                        if (state.mana >= state.manaMax) state.skillReady = 1;
                        playGetScore();
                    }
                }
            }

            if (state.bossState == 3) {
                if (isSwordHitBoss(state.explorerX, state.explorerY, state.facingRight, (int)state.bossX, (int)state.bossY)) {
                    state.bossHp -= 3;
                    playDamage();
                }
            }

            for (int f = 0; f < MAX_FIREBALLS; f++) {
                if (!state.fireballs[f].active) continue;
                if (isSwordHitFireball(state.explorerX, state.explorerY, state.facingRight, state.fireballs[f].x, state.fireballs[f].y)) {
                    state.fireballs[f].active = 0; // deflect/destroy fireball
                    playDamage();
                }
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
            int canHit = (state.energyWaves[i].type == 0) || ((state.energyWaves[i].life / 0.6f) <= 0.4f);
            if (canHit && isEnergyWaveHitBoss(state.energyWaves[i], (int)state.bossX, (int)state.bossY)) {
                state.energyWaves[i].hitBoss = 1;
                state.bossHp -= (state.energyWaves[i].type == 1) ? 15 : 6;
                playDamage();
            }
        }

        int canHitGhosts = (state.energyWaves[i].type == 0) || ((state.energyWaves[i].life / 0.6f) <= 0.4f);
        if (canHitGhosts) {
            for (int g = 0; g < MAX_GHOSTS; g++) {
                if (!state.ghosts[g].active) continue;
                if (isEnergyWaveHitGhost(state.energyWaves[i], (int)state.ghosts[g].x, (int)state.ghosts[g].y)) {
                    state.ghosts[g].hp = 0;
                    state.ghosts[g].active = 0;
                    state.score += 100;
                    state.mana += 2;
                    if (state.mana > state.manaMax) state.mana = state.manaMax;
                    if (state.mana >= state.manaMax) state.skillReady = 1;
                    playGetScore();
                }
            }

            if (state.energyWaves[i].type == 0) {
                float waveLeft = (state.energyWaves[i].dir > 0) ? state.energyWaves[i].x : 0.0f;
                float waveRight = (state.energyWaves[i].dir > 0) ? (float)SCREEN_WIDTH : state.energyWaves[i].x;
                float waveTop = state.energyWaves[i].y - 35.0f;
                float waveBottom = state.energyWaves[i].y + 35.0f;
                for (int f = 0; f < MAX_FIREBALLS; f++) {
                    if (!state.fireballs[f].active) continue;
                    if (state.fireballs[f].x >= waveLeft && state.fireballs[f].x <= waveRight &&
                        state.fireballs[f].y >= waveTop && state.fireballs[f].y <= waveBottom) {
                        state.fireballs[f].active = 0;
                    }
                }
            }

            if (state.energyWaves[i].type == 1) {
                float waveLeft = (state.energyWaves[i].dir > 0) ? (state.energyWaves[i].x - 220.0f) : 0.0f;
                float waveRight = (state.energyWaves[i].dir > 0) ? (float)SCREEN_WIDTH : (state.energyWaves[i].x + 220.0f);
                for (int f = 0; f < MAX_FIREBALLS; f++) {
                    if (!state.fireballs[f].active) continue;
                    if (state.fireballs[f].x >= waveLeft && state.fireballs[f].x <= waveRight) {
                        state.fireballs[f].active = 0;
                    }
                }
            }
        }
    }
}

static void updateGhostsAndHazards(GameState& state) {
    int ghostLimit = (state.bossState == 0) ? MAX_GHOSTS : 2;
    state.ghostSpawnTimer -= state.dt;
    if (state.ghostSpawnTimer <= 0.0f) {
        for (int i = 0; i < ghostLimit; i++) {
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

    for (int i = 0; i < ghostLimit; i++) {
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
        for (int i = 0; i < ghostLimit; i++) {
            if (!state.ghosts[i].active) continue;
            if (isExplorerHitGhost(state.explorerX, state.explorerY, (int)state.ghosts[i].x, (int)state.ghosts[i].y)) {
                if (!state.slowShieldActive) {
                    state.hp -= 1;
                    state.hurtCooldown = 0.8f;
                    playExplorerDamage();
                }
                break;
            }
        }
    }

    if (state.hurtCooldown <= 0.0f) {
        for (int i = 0; i < MAX_FIREBALLS; i++) {
            if (!state.fireballs[i].active) continue;
            if (isExplorerHitFireball(state.explorerX, state.explorerY, state.fireballs[i].x, state.fireballs[i].y)) {
                state.fireballs[i].active = 0;
                if (!state.slowShieldActive) {
                    state.hp -= 1;
                    state.hurtCooldown = 0.8f;
                    playExplorerDamage();
                }
                break;
            }
        }
    }
}

static void updateBoss(GameState& state) {
    if (state.bossState == 0 && state.score >= state.nextBossScore) {
        state.bossState = 1;
        state.bossWarningTimer = 3.0f;
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
                state.nextBossScore = 6000;
                state.bossMaxHp = 50;  // demonBoss lần đầu xuất hiện
            } else if (state.bossLevel == 3) {
                state.nextBossScore = 10000;
                state.bossMaxHp = 70;  // reaperBoss lần 2 xuất hiện (nhiều máu hơn ban đầu 30)
            } else if (state.bossLevel == 4) {
                state.nextBossScore = 15000;
                state.bossMaxHp = 100; // demonBoss lần 2 xuất hiện (nhiều máu hơn ban đầu 50)
            } else {
                state.nextBossScore += 5000;
                state.bossMaxHp = 120;
            }
        }
    }
}

#endif
