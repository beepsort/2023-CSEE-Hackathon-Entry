#include <gb/gb.h>
#include <gb/metasprites.h>
#include <stdint.h>

#include "game_states.h"
#include "menu.h"
#include "setup.h"
#include "play.h"
#include "gameover.h"

extern GAMESTATES CUR_GAMESTATE;
extern GAMESTATES NXT_GAMESTATE;

void init_gfx() {
    SPRITES_8x8;
    DISPLAY_ON;
}


void main(void)
{
	init_gfx();
    init_menu();
    
    // Loop forever
    while(1) {
        switch (CUR_GAMESTATE) {
        case MENU:
            update_menu();
            draw_menu();
            break;
        case SETUP:
            update_setup();
            draw_setup();
        case PLAY:
            update_play();
            draw_play();
            break;
        case GAMEOVER:
            update_gameover();
            draw_gameover();
            break;
        }

        if (CUR_GAMESTATE != NXT_GAMESTATE) {
            switch (NXT_GAMESTATE) {
            case MENU:
                init_menu();
                break;
            case SETUP:
                init_setup();
                break;
            case PLAY:
                init_play();
                break;
            case GAMEOVER:
                init_gameover();
                break;
            }
            CUR_GAMESTATE = NXT_GAMESTATE;
        }

		// Done processing, yield CPU and wait for start of next frame
        wait_vbl_done();
    }
}
