#include <gb/gb.h>

#include "../res/playbg.h"
#include "../res/font.h"

#include "game_states.h"
#include "play.h"
#include "draw_playfield.h"
#include "sprite_alloc.h"

extern GAMESTATES NXT_GAMESTATE;
extern player PLAYERS [2];
static PLAYNAME cur_player = PLAYER_A;
static uint8_t cursor_x = 8;
static uint8_t cursor_y = 8;
static uint8_t cursor_spr;

void init_play()
{
    HIDE_BKG;
    HIDE_SPRITES;
    HIDE_WIN;
    //set_win_data(0, 64u, font_tiles);
    draw_playfield();
    cursor_spr = SPRALLOC();
    set_sprite_tile(cursor_spr, 13);
    move_sprite(cursor_spr, 4*8+cursor_x*8, 4*8+cursor_y*8);
    if (cursor_spr == 0) {
        // cursor is higher priority than all other sprites
        // if cannot be allocated for, then delete something
        SPRFREE(0);
        cursor_spr = SPRALLOC();
    }
    SHOW_BKG;
    SHOW_SPRITES;
}

void update_play()
{
}

void draw_play()
{
    draw_boats(&(PLAYERS[PLAYER_A]));
    draw_boats(&(PLAYERS[PLAYER_B]));
}
