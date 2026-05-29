#ifndef LANGUAGE_H
#define LANGUAGE_H

struct Language {
    // Main Menu
    const char* main_menu_play;
    const char* main_menu_instructions;
    const char* main_menu_scoreboard;
    const char* main_menu_settings;
    const char* main_menu_exit;

    // Common Buttons
    const char* back_button;
    const char* esc_to_back;

    // Settings Screen
    const char* settings_title;
    const char* settings_sound;
    const char* settings_sound_on;
    const char* settings_sound_off;
    const char* settings_language;

    // Instructions Screen
    const char* instructions_title;
    const char* instructions_move;
    const char* instructions_attack;
    const char* instructions_dash;
    const char* instructions_slow;
    const char* instructions_power;
    const char* instructions_weapon;

    // Scoreboard Screen
    const char* scoreboard_title;
    const char* scoreboard_empty;

    // Pause Menu Overlay
    const char* pause_title;
    const char* pause_resume;
    const char* pause_exit_to_menu;
    // HUD and Stats
    const char* hud_hp;
    const char* hud_score;
    const char* hud_energy;

    // Boss Info
    const char* boss_name_reaper;
    const char* boss_name_demon;
    const char* boss_warning_reaper;
    const char* boss_warning_demon;
    const char* boss_dodge;

    // Loading Screen
    const char* loading_wait;
    const char* loading_text;
    const char* loading_forest;
    const char* loading_monsters;
    const char* loading_complete;
    const char* loading_start;
    const char* loading_subtitle;

    // Game Over Screen
    const char* game_over_title;
    const char* game_over_score;
    const char* game_over_to_menu;

    // Spam Warning Screen
    const char* spam_title;
    const char* spam_message;
    const char* spam_button;
};

#endif
