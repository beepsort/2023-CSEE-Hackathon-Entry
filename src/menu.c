#include <gb/gb.h>

#include "../res/font.h"
#include "../res/chars.h"

#include "game_states.h"
#include "menu.h"

extern GAMESTATES NXT_GAMESTATE;

static const uint8_t txt_battleships[] = {LETTER_B, LETTER_A, LETTER_T, LETTER_T, LETTER_L, LETTER_E, LETTER_S, LETTER_H, LETTER_I, LETTER_P, LETTER_S};
static const uint8_t txt_press_start[] = {LETTER_P, LETTER_r, LETTER_e, LETTER_s, LETTER_s, 0, LETTER_S, LETTER_t, LETTER_a, LETTER_r, LETTER_t};

void init_menu()
{
    SHOW_SPRITES;
    SHOW_BKG;
    HIDE_WIN;
    set_bkg_data(0, 64u, font_tiles);
    set_bkg_tiles(4,4,6,1,txt_battleships);
    set_bkg_tiles(10,5,5,1,txt_battleships+6);
    set_bkg_tiles(4,14,11,1,txt_press_start);
}

void update_menu()
{
    if (joypad() & J_START) {
        NXT_GAMESTATE = SETUP;
    }
}

void draw_menu()
{
    
}
