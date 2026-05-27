#ifndef LANGUAGE_VI_H
#define LANGUAGE_VI_H

#include "Language.h"

static const Language langVi = {
    // Main Menu
    "Choi game",                  // main_menu_play
    "Huong dan",                  // main_menu_instructions
    "Bang diem",                  // main_menu_scoreboard
    "Cai dat",                    // main_menu_settings
    "Thoat",                      // main_menu_exit

    // Common Buttons
    "Quay lai",                   // back_button
    "Nhan ESC de quay lai menu",  // esc_to_back

    // Settings Screen
    "CAI DAT",                    // settings_title
    "Am thanh",                   // settings_sound
    "BAT",                        // settings_sound_on
    "TAT",                        // settings_sound_off
    "Ngon ngu",                   // settings_language

    // Instructions Screen
    "HUONG DAN CHOI GAME",                        // instructions_title
    "- Phim MUI TEN: Di chuyen",                  // instructions_move
    "- Phim SPACE  : Tan cong",                   // instructions_attack
    "- Phim SHIFT + MUI TEN: Di chuyen nhanh",    // instructions_dash
    "- Phim CTRL + MUI TEN: Di chuyen cham + Khien",      // instructions_slow
    "- Phim SHIFT + SPACE : Power Attack",        // instructions_power'
    "- Phim C       : Doi vu khi (Cung / Kiem)", // instructions_weapon

    // Scoreboard Screen
    "BANG DIEM",                  // scoreboard_title
    "Chua co diem nao",           // scoreboard_empty

    // Pause Menu Overlay
    "TAM DUNG",                   // pause_title
    "Choi Tiep",                  // pause_resume
    "Thoat Ra Menu",              // pause_exit_to_menu

    // HUD and Stats
    "HP:",                        // hud_hp
    "Diem",                       // hud_score
    "Nang Luong:",                // hud_energy

    // Boss Info
    "REAPER BOSS",                             // boss_name
    "CANH BAO: REAPER BOSS SAP XUAT HIEN!",     // boss_warning
    "NE DON!",                                 // boss_dodge

    // Loading Screen
    "Vui long cho...",            // loading_wait
    "Dang tai...",                // loading_text
    "Dang tai khu rung...",       // loading_forest
    "Dang tai quai vat...",       // loading_monsters
    "Hoan thanh...",              // loading_complete
    "Bat dau!",                   // loading_start
    "Chuan bi vao cuoc phieu luu...", // loading_subtitle

    // Game Over Screen
    "GAME OVER",                  // game_over_title
    "Diem",                       // game_over_score
    "Ve menu",                    // game_over_to_menu

    // Spam Warning Screen
    "CANH BAO: NHAN SPACE QUA NHANH", // spam_title
    "Vui long nhan SPACE cham lai.",  // spam_message
    "Choi Tiep"                      // spam_button
};

#endif
