#include <gb/gb.h>
#include <stdbool.h>

#include "../res/playbg.h"
#include "draw_playfield.h"
#include "game_definitions.h"

void draw_playfield()
{
    set_bkg_data(0, 8u, playbg_tiles);
    fill_bkg_rect(0,0,20,18,0);
    fill_bkg_rect(GAME_BOARD_BEGIN_X,GAME_BOARD_BEGIN_Y,GAME_SIZE_X,GAME_SIZE_Y,1);
}

void draw_boat(boat * b)
{
    if (b->visible == false && b->placed == false) return;
    else if (b->visible == false && b->placed == true) {
        for (uint8_t i=0; i<(b->size); i++) {
            hide_sprite(b->owned_sprite_ids[i]);
        }
        return;
    }
    uint8_t sprite_base = b->rotation==VERTICAL ? 1 : 7;
    if (b->placed == false) sprite_base += 3;
    uint8_t boat_x = b->x;
    uint8_t boat_y = b->y;
    
    uint8_t * boat_pos_iter = b->rotation==VERTICAL ? &boat_y : &boat_x;
    uint8_t isprite;
    for (uint8_t i=0; i<(b->size); i++) {
        if (i==0) {
            isprite = sprite_base;
        }
        else if (i==b->size-1) {
            isprite = sprite_base + 2;
        }
        else {
            isprite = sprite_base + 1;
        }
        // 8 and 16 offsets are a hack, there was a positioning bug but i dont have time to fix it
        uint8_t x = 8 + 8 * (GAME_BOARD_BEGIN_X + boat_x);
        uint8_t y = 16 + 8 * (GAME_BOARD_BEGIN_Y + boat_y);
        set_sprite_tile(b->owned_sprite_ids[i], isprite);
        move_sprite(b->owned_sprite_ids[i],x,y);
        (*boat_pos_iter)++;
    }
}

void draw_boats(player * p)
{
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        draw_boat(&(p->boats[i]));
    }
}
