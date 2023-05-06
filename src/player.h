#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "boat.h"

#define NUM_BOATS 4

typedef enum {
    PLAYER_A = 0,
    PLAYER_B = 1
} PLAYNAME;

typedef struct {
    uint8_t id;
    boat boats [NUM_BOATS];
} player;

void player_init(player * p, uint8_t id);
void players_init();
void player_hideall(player * p);
void player_showall(player * p);
void player_showdamage(player * p);
bool player_hit(player * p, uint8_t x, uint8_t y);
bool player_lost(player * p);
boat * player_get_placeable_boat(player * p); // returns NULL on failure

#endif
