#include <gb/gb.h>

#include "../res/playbg.h"
#include "../res/font.h"

#include "game_states.h"
#include "play.h"
#include "draw_playfield.h"

const static uint8_t play_bg[20*18] = {0};

void init_play()
{
    SHOW_BKG;
    SHOW_SPRITES;
    HIDE_WIN;
    //set_win_data(0, 64u, font_tiles);
    draw_playfield();
}

void update_play()
{
}

void draw_play()
{
}
