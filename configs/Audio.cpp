#ifndef AUDIO_CPP
#define AUDIO_CPP

#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "winmm.lib")

static const char* kAliasLoading = "bg_loading";
static const char* kAliasBackground = "bg_menu";
static const char* kAliasPlay = "bg_play";
static const char* kAliasClick = "sfx_click";
static const char* kAliasDamage = "sfx_damage";
static const char* kAliasExplorerDamage = "sfx_explorer_damage";
static const char* kAliasDeath = "sfx_death";
static const char* kAliasFire = "sfx_fire";
static const char* kAliasPowerFirer = "sfx_power_firer";
static const char* kAliasGameOver = "sfx_gameover";
static const char* kAliasGetScore = "sfx_getscore";
static const char* kAliasJump = "sfx_jump";
static const char* kAliasRun = "sfx_run";

static const char* kPathLoading = "sound-effects\\sound-loading.mp3";
static const char* kPathBackground = "sound-effects\\sound-background.mp3";
static const char* kPathPlay = "sound-effects\\sound-play.mp3";
static const char* kPathClick = "sound-effects\\sound-clicked.mp3";
static const char* kPathDamage = "sound-effects\\sound-damage.mp3";
static const char* kPathExplorerDamage = "sound-effects\\sound-explore-damage.mp3";
static const char* kPathDeath = "sound-effects\\sound-death.mp3";
static const char* kPathFire = "sound-effects\\sound-fire.mp3";
static const char* kPathPowerFirer = "sound-effects\\power-firer.mp3";
static const char* kPathGameOver = "sound-effects\\sound-gameover.mp3";
static const char* kPathGetScore = "sound-effects\\sound-getscore.mp3";
static const char* kPathJump = "sound-effects\\sound-jump.mp3";
static const char* kPathRun = "sound-effects\\sound-run.mp3";

static int gAudioInitialized = 0;
static const char* gCurrentMusic = NULL;
static int gRunLooping = 0;

static MCIERROR mciCommand(const char* cmd) {
    return mciSendStringA(cmd, NULL, 0, NULL);
}

static void openAlias(const char* alias, const char* path) {
    char cmd[256];
    snprintf(cmd, sizeof(cmd), "open \"%s\" type mpegvideo alias %s", path, alias);
    if (mciCommand(cmd) == 0) return;

    snprintf(cmd, sizeof(cmd), "open \"%s\" type waveaudio alias %s", path, alias);
    mciCommand(cmd);
}

static void closeAlias(const char* alias) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "close %s", alias);
    mciCommand(cmd);
}

static void stopAlias(const char* alias) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "stop %s", alias);
    mciCommand(cmd);
}

static void seekAliasStart(const char* alias) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "seek %s to start", alias);
    mciCommand(cmd);
}

static void setAliasVolume(const char* alias, int volume) {
    if (volume < 0) volume = 0;
    if (volume > 1000) volume = 1000;
    char cmd[80];
    snprintf(cmd, sizeof(cmd), "setaudio %s volume to %d", alias, volume);
    mciCommand(cmd);
}

static void playAliasOnce(const char* alias) {
    stopAlias(alias);
    seekAliasStart(alias);
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "play %s", alias);
    mciCommand(cmd);
}

static void playAliasLoop(const char* alias) {
    char cmd[64];
    snprintf(cmd, sizeof(cmd), "play %s repeat", alias);
    mciCommand(cmd);
}

static void playMusicAlias(const char* alias) {
    if (!gAudioInitialized) return;
    if (gCurrentMusic && strcmp(gCurrentMusic, alias) == 0) return;
    if (gCurrentMusic) {
        stopAlias(gCurrentMusic);
    }
    gCurrentMusic = alias;
    playAliasLoop(alias);
}

void initAudio() {
    if (gAudioInitialized) return;
    openAlias(kAliasLoading, kPathLoading);
    openAlias(kAliasBackground, kPathBackground);
    openAlias(kAliasPlay, kPathPlay);
    openAlias(kAliasClick, kPathClick);
    openAlias(kAliasDamage, kPathDamage);
    openAlias(kAliasExplorerDamage, kPathExplorerDamage);
    openAlias(kAliasDeath, kPathDeath);
    openAlias(kAliasFire, kPathFire);
    openAlias(kAliasPowerFirer, kPathPowerFirer);
    openAlias(kAliasGameOver, kPathGameOver);
    openAlias(kAliasGetScore, kPathGetScore);
    openAlias(kAliasJump, kPathJump);
    openAlias(kAliasRun, kPathRun);

    setAliasVolume(kAliasBackground, 520);
    setAliasVolume(kAliasPlay, 650);
    setAliasVolume(kAliasLoading, 800);
    setAliasVolume(kAliasGameOver, 900);

    setAliasVolume(kAliasClick, 700);
    setAliasVolume(kAliasDamage, 780);
    setAliasVolume(kAliasExplorerDamage, 800);
    setAliasVolume(kAliasDeath, 850);
    setAliasVolume(kAliasFire, 760);
    setAliasVolume(kAliasPowerFirer, 820);
    setAliasVolume(kAliasGetScore, 820);
    setAliasVolume(kAliasJump, 720);
    setAliasVolume(kAliasRun, 600);
    gAudioInitialized = 1;
}

void shutdownAudio() {
    if (!gAudioInitialized) return;
    stopAlias(kAliasLoading);
    stopAlias(kAliasBackground);
    stopAlias(kAliasPlay);
    stopAlias(kAliasRun);
    closeAlias(kAliasLoading);
    closeAlias(kAliasBackground);
    closeAlias(kAliasPlay);
    closeAlias(kAliasClick);
    closeAlias(kAliasDamage);
    closeAlias(kAliasExplorerDamage);
    closeAlias(kAliasDeath);
    closeAlias(kAliasFire);
    closeAlias(kAliasPowerFirer);
    closeAlias(kAliasGameOver);
    closeAlias(kAliasGetScore);
    closeAlias(kAliasJump);
    closeAlias(kAliasRun);
    gAudioInitialized = 0;
    gCurrentMusic = NULL;
    gRunLooping = 0;
}

void playMusicLoading() {
    playMusicAlias(kAliasLoading);
}

void playMusicBackground() {
    playMusicAlias(kAliasBackground);
}

void playMusicPlay() {
    playMusicAlias(kAliasPlay);
}

void stopCurrentMusic() {
    if (!gAudioInitialized || !gCurrentMusic) return;
    stopAlias(gCurrentMusic);
    gCurrentMusic = NULL;
}

void playClick() { playAliasOnce(kAliasClick); }
void playDamage() { playAliasOnce(kAliasDamage); }
void playExplorerDamage() { playAliasOnce(kAliasExplorerDamage); }
void playDeath() { playAliasOnce(kAliasDeath); }
void playFire() { playAliasOnce(kAliasFire); }
void playPowerFirer() { playAliasOnce(kAliasPowerFirer); }
void playGameOver() { playAliasOnce(kAliasGameOver); }
void playGetScore() { playAliasOnce(kAliasGetScore); }
void playJump() { playAliasOnce(kAliasJump); }

void startRunLoop() {
    if (gRunLooping) return;
    gRunLooping = 1;
    playAliasLoop(kAliasRun);
}

void stopRunLoop() {
    if (!gRunLooping) return;
    gRunLooping = 0;
    stopAlias(kAliasRun);
}

#endif
