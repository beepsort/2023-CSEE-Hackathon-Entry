#include <gb/gb.h>

#include "../res/font.h"
#include "../res/chars.h"

#include "game_states.h"
#include "gameover.h"

extern GAMESTATES NXT_GAMESTATE;

static const uint8_t txt_wins [] = {LETTER_W, LETTER_I, LETTER_N, LETTER_S};

void init_gameover()
{
    HIDE_SPRITES;
    HIDE_BKG;
    HIDE_WIN;
    set_bkg_data(0,64,font_tiles);
    fill_bkg_rect(0,0,20,18,0);
    set_bkg_tiles(9,9,4,1,txt_wins);
    set_bkg_tile_xy(7,9,1); // A
    //set_bkg_tile_xy(7,9,2); // B
    SHOW_BKG;
}

void update_gameover()
{
    uint8_t btns = joypad();
    if (btns & J_A || btns & J_B) {
        NXT_GAMESTATE = MENU;
    }
}

void draw_gameover()
{
}
