#include <gb/gb.h>

#include "../res/playbg.h"
#include "../res/playsprites.h"
#include "../res/font.h"
#include "../res/chars.h"
#include "../res/messages.h"

#include "game_states.h"
#include "play.h"
#include "draw_playfield.h"
#include "game_definitions.h"
#include "sprite_alloc.h"
#include "input.h"

extern GAMESTATES NXT_GAMESTATE;
extern player PLAYERS [2];
extern PLAYNAME CUR_PLAYER;
static uint8_t cursor_x = 8;
static uint8_t cursor_y = 8;
static uint8_t cursor_spr;
static bool has_shot = false;
static bool has_disp_shots = true;
static bool shot_record [2][GAME_SIZE_X][GAME_SIZE_Y];
static uint8_t player_name_spr;

void init_play()
{
    HIDE_BKG;
    HIDE_SPRITES;
    HIDE_WIN;
    set_win_data(8, 64u, font_tiles);
    SPRFREEALL();
    set_sprite_data(0, 20, playsprites_tiles);
    draw_playfield();
    set_win_tiles(0,0,20,1,messages_play_help1);
    move_win(7,132);
    cursor_spr = SPRALLOC();
    if (cursor_spr == 0) {
        // cursor is higher priority than all other sprites
        // if cannot be allocated for, then delete something
        SPRFREE(0);
        cursor_spr = SPRALLOC();
    }
    player_name_spr = SPRALLOC();
    set_sprite_tile(player_name_spr, 16);
    move_sprite(player_name_spr, 16, 16);
    CUR_PLAYER = PLAYER_A;
    SHOW_BKG;
    SHOW_SPRITES;
    SHOW_WIN;
}

void disp_turn_end(bool hit)
{
    const uint8_t txt_player [] = {LETTER_P, LETTER_L, LETTER_A, LETTER_Y, LETTER_E, LETTER_R};
    set_bkg_tiles(0, 9, 6, 1, txt_player);
    set_bkg_tile_xy(6+1, 0, PLAYERS[CUR_PLAYER].id);
}

void draw_shots()
{
    draw_playfield();
    for (uint8_t y=0; y<GAME_SIZE_Y; y++) {
        for (uint8_t x=0; x<GAME_SIZE_X; x++) {
            if (shot_record[CUR_PLAYER][x][y]) {
                set_bkg_tile_xy(GAME_BOARD_BEGIN_X+x, GAME_BOARD_BEGIN_Y+y, 2);
            }
        }
    }
}

void update_play()
{
    PLAYNAME enemy_player = CUR_PLAYER==PLAYER_A ? PLAYER_B : PLAYER_A;
    player_showdamage(&(PLAYERS[enemy_player]));
    player_hideall(&(PLAYERS[CUR_PLAYER]));
    uint8_t jp = joypad_edge();
    if (jp & J_UP && cursor_y > 0) {
        cursor_y--;
    }
    if (jp & J_DOWN && cursor_y < GAME_SIZE_Y - 1) {
        cursor_y++;
    }
    if (jp & J_LEFT && cursor_x > 0) {
        cursor_x--;
    }
    if (jp & J_RIGHT && cursor_x < GAME_SIZE_X - 1) {
        cursor_x++;
    }
    if (jp & J_A) {
        if (has_shot == false) {
            bool * tile_shot_record = &(shot_record[CUR_PLAYER][cursor_x][cursor_y]);
            if (*tile_shot_record == false) {
                // shoot!
                bool hit = player_hit(&(PLAYERS[enemy_player]), cursor_x, cursor_y);
                *tile_shot_record = true;
                has_shot = true;
                has_disp_shots = false;
                // TODO: CHECK IF PLAYER HAS WON, IF SO MOVE TO FINAL WIN SCREEN
                if (player_lost(&(PLAYERS[enemy_player]))) {
                    NXT_GAMESTATE = GAMEOVER;
                    return;
                }
            }
        }
        else {
            CUR_PLAYER = enemy_player;
            has_shot = false;
            has_disp_shots = false;
        }
    }
}

void draw_play()
{
    if (has_disp_shots == false) {
        draw_shots();
        has_disp_shots = true;
    }
    draw_boats(&(PLAYERS[PLAYER_A]));
    draw_boats(&(PLAYERS[PLAYER_B]));
    move_sprite(player_name_spr, 16, 16);
    set_sprite_tile(player_name_spr, 16+CUR_PLAYER);
    if (has_shot == false) {
        set_sprite_tile(cursor_spr, 13);
        set_win_tiles(0,0,20,1,messages_play_help1);
    }
    else {
        set_sprite_tile(cursor_spr, 0);
        set_win_tiles(0,0,20,1,messages_play_help2);
    }
    uint8_t x = 8 + 8 * (GAME_BOARD_BEGIN_X + cursor_x);
    uint8_t y = 16 + 8 * (GAME_BOARD_BEGIN_Y + cursor_y);
    move_sprite(cursor_spr, x, y);
}
