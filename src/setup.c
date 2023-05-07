#include <gb/gb.h>
#include <stdbool.h>

#include "../res/font.h"
#include "../res/chars.h"
#include "../res/playsprites.h"

#include "game_states.h"
#include "draw_playfield.h"
#include "player.h"
#include "boat.h"
#include "sprite_alloc.h"
#include "input.h"

extern GAMESTATES NXT_GAMESTATE;
extern player PLAYERS [2];
extern PLAYNAME CUR_PLAYER;
static uint8_t player_name_spr;

void show_instructions()
{
    static const uint8_t win_txt[] = {0};
    SHOW_WIN;
    set_win_tiles(8,8,6,6,win_txt);
    move_win(0,0);
}

void init_setup()
{
    HIDE_BKG;
    HIDE_WIN;
    HIDE_SPRITES;

    SPRFREEALL();
    players_init();
    CUR_PLAYER = PLAYER_A;
    set_win_data(0, 64u, font_tiles);
    draw_playfield();
    set_sprite_data(0, 20, playsprites_tiles);
    player_name_spr = SPRALLOC();
    move_sprite(player_name_spr, 16, 16);
    set_sprite_tile(player_name_spr, 16+CUR_PLAYER);
    SHOW_BKG;
    SHOW_SPRITES;
}

void update_setup()
{
    // TODO: display instructions in window
    // when a button pressed then hide window
    // allow movement/rotation of boats
    // setup for next player
    boat * cur_boat = player_get_placeable_boat(&(PLAYERS[CUR_PLAYER]));
    if (cur_boat == 0) {
        // next player
        player_hideall(&(PLAYERS[CUR_PLAYER]));
        if (CUR_PLAYER == PLAYER_A) {
            CUR_PLAYER = PLAYER_B;
            return;
        }
        else { // move to the next game state
            NXT_GAMESTATE = PLAY;
            return;
        }
    }
    cur_boat->visible = VISIBLE;
    uint8_t jp = joypad_edge();
    if (jp & J_UP) {
        boat_mv_up(cur_boat);
    }
    if (jp & J_DOWN) {
        boat_mv_down(cur_boat);
    }
    if (jp & J_LEFT) {
        boat_mv_left(cur_boat);
    }
    if (jp & J_RIGHT) {
        boat_mv_right(cur_boat);
    }
    if (jp & J_B) {
        boat_rot(cur_boat);
    }
    if (jp & J_A) {
        if (player_can_place(&(PLAYERS[CUR_PLAYER]), cur_boat)) {
            // place down
            cur_boat->placed = true;
        }
    }
}

void draw_setup()
{
    // handle show/hide of window?
    // display boats being placed
    draw_boats(&(PLAYERS[PLAYER_A]));
    draw_boats(&(PLAYERS[PLAYER_B]));
    move_sprite(player_name_spr, 16, 16);
    set_sprite_tile(player_name_spr, 16+CUR_PLAYER);
}
