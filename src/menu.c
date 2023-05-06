#include <gb/gb.h>

#include "../res/font.h"
#include "../res/chars.h"
#include "../res/titleship.h"

#include "game_states.h"
#include "menu.h"

extern GAMESTATES NXT_GAMESTATE;

static const uint8_t txt_battleships[] = {LETTER_B, LETTER_A, LETTER_T, LETTER_T, LETTER_L, LETTER_E, LETTER_S, LETTER_H, LETTER_I, LETTER_P, LETTER_S};
static const uint8_t txt_press_start[] = {LETTER_P, LETTER_r, LETTER_e, LETTER_s, LETTER_s, 0, LETTER_S, LETTER_t, LETTER_a, LETTER_r, LETTER_t};

void render_ship()
{
    for (uint8_t x=0; x<20; x++) {
        for (uint8_t y=0; y<6; y++) {
            set_bkg_tile_xy(x,6+y,y*20+x);
        }
    }
}

void render_text(uint8_t x, uint8_t y, uint8_t n_sprites, const uint8_t * tiles)
{
    static uint8_t cur_sprite = 0;
    for (uint8_t i=0; i<n_sprites; i++) {
        set_sprite_tile(cur_sprite, tiles[i]);
        move_sprite(cur_sprite, 8+8*(x+i), 8+8*y);
        cur_sprite++;
    }
}

void init_menu()
{
    SHOW_SPRITES;
    SHOW_BKG;
    HIDE_WIN;
    
    set_bkg_data(0, 20*7, titleship_tiles);
    render_ship();
    set_sprite_data(0, 64u, font_tiles);
    set_sprite_tile(0, 1);
    move_sprite(0, 50, 50);
    render_text(4,4,6,txt_battleships);
    render_text(10,5,5,txt_battleships+6);
    render_text(4,14,5,txt_press_start);
    render_text(10,14,5,txt_press_start+6);
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
