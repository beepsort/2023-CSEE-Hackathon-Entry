#include <gb/gb.h>

#include "../res/font.h"
#include "../res/chars.h"

#include "game_states.h"
#include "draw_playfield.h"

void show_instructions()
{
    static const uint8_t win_txt[] = {0};
    SHOW_WIN;
    set_win_tiles(8,8,6,6,win_txt);
}

void init_setup()
{
    SHOW_BKG;
    HIDE_WIN;
    HIDE_SPRITES;
    set_win_data(0, 64u, font_tiles);
    //set_bkg_tiles(0,0,20,18,PLAYBG_TILEMAP);
    draw_playfield();
}

void update_setup()
{
    // display instructions in window
    // when a button pressed then hide window
    // allow movement/rotation of boats
    // setup for next player
}

void draw_setup()
{
    // handle show/hide of window?
    // display boats being placed
}
