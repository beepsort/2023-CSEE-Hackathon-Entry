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
static PLAYNAME cur_player = PLAYER_A;

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
    set_win_data(0, 64u, font_tiles);
    draw_playfield();
    set_sprite_data(0, 13, playsprites_tiles);
    SHOW_BKG;
    SHOW_SPRITES;
}

void update_setup()
{
    // TODO: display instructions in window
    // when a button pressed then hide window
    // allow movement/rotation of boats
    // setup for next player
    boat * cur_boat = player_get_placeable_boat(&(PLAYERS[cur_player]));
    if (cur_boat == 0) {
        // next player
        player_hideall(&(PLAYERS[cur_player]));
        if (cur_player == PLAYER_A) {
            cur_player = PLAYER_B;
            return;
        }
        else { // move to the next game state
            NXT_GAMESTATE = PLAY;
            return;
        }
    }
    cur_boat->visible = true;
    switch (joypad_edge()) {
    case J_UP:
        boat_mv_up(cur_boat);
        break;
    case J_DOWN:
        boat_mv_down(cur_boat);
        break;
    case J_LEFT:
        boat_mv_left(cur_boat);
        break;
    case J_RIGHT:
        boat_mv_right(cur_boat);
        break;
    case J_B:
        boat_rot(cur_boat);
        break;
    case J_A:
        // TODO: CHECK POSSIBLE TO PLACE
        // place down
        cur_boat->placed = true;
        break;
    default:
        break;
    }
}

void draw_setup()
{
    // handle show/hide of window?
    // display boats being placed
    draw_boats(&(PLAYERS[PLAYER_A]));
    draw_boats(&(PLAYERS[PLAYER_B]));
}
