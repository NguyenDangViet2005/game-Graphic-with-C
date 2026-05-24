#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 700
#define GROUND_Y 550

// Macro để tạo màu RGB
#define COLOR(r, g, b) ((r) | ((g) << 8) | ((b) << 16))

#include "../languages/Language.h"
#include "../languages/LanguageVi.h"
#include "../languages/LanguageEn.h"

// Game Settings
extern int gSoundEnabled; // 1: Bật, 0: Tắt
extern int gLanguage;     // 0: Tiếng Việt, 1: English
extern const Language* gCurrentLanguage;

inline void setLanguage(int langId) {
    gLanguage = langId;
    if (langId == 0) {
        gCurrentLanguage = &langVi;
    } else {
        gCurrentLanguage = &langEn;
    }
}

#endif
