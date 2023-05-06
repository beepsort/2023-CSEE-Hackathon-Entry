#include <gb/gb.h>

#include "../res/playbg.h"
#include "draw_playfield.h"

void draw_playfield()
{
    set_bkg_data(0, 8u, playbg_tiles);
    fill_bkg_rect(0,0,20,18,0);
    fill_bkg_rect(3,2,14,14,1);
}
