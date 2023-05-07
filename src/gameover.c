#include <gb/gb.h>

#include "../res/font.h"
#include "../res/chars.h"

#include "game_states.h"
#include "gameover.h"
#include "player.h"
#include "input.h"

extern GAMESTATES NXT_GAMESTATE;
extern PLAYNAME CUR_PLAYER;

static const uint8_t txt_wins [] = {LETTER_W, LETTER_I, LETTER_N, LETTER_S};
static const uint8_t txt_press_start[] = {LETTER_P, LETTER_r, LETTER_e, LETTER_s, LETTER_s, 0, LETTER_S, LETTER_t, LETTER_a, LETTER_r, LETTER_t};

void init_gameover()
{
    HIDE_SPRITES;
    HIDE_BKG;
    HIDE_WIN;
    set_bkg_data(0,64,font_tiles);
    fill_bkg_rect(0,0,20,18,0);
    set_bkg_tiles(8,9,4,1,txt_wins);
    if (CUR_PLAYER == PLAYER_A) {
        set_bkg_tile_xy(6,9,1);
    }
    else {
        set_bkg_tile_xy(6,9,2);
    }
    set_bkg_tiles(4,14,5,1,txt_press_start);
    set_bkg_tiles(10,14,5,1,txt_press_start+6);
    players_init();
    SHOW_BKG;
}

void update_gameover()
{
    uint8_t btns = joypad_edge();
    if (btns & J_START) {
        NXT_GAMESTATE = MENU;
    }
}

void draw_gameover()
{
}
