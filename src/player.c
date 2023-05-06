#include "player.h"
#include "boat.h"
#include "../res/chars.h"

#define EMPTY_PLAYER = {0, {0}};
player PLAYERS [2];
PLAYNAME CUR_PLAYER = PLAYER_A;

void player_init(player * p, uint8_t id)
{
    p->id = id;
    boat * boats = p->boats;
    boat_init(&boats[0], 3);
    boat_init(&boats[1], 4);
    boat_init(&boats[2], 4);
    boat_init(&boats[3], 5);
}

void players_init()
{
    player_init(&(PLAYERS[PLAYER_A]), LETTER_A);
    player_init(&(PLAYERS[PLAYER_B]), LETTER_B);
}

void player_hideall(player * p)
{
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        p->boats[i].visible = NONE;
    }
}

void player_showall(player * p)
{
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        p->boats[i].visible = VISIBLE;
    }
}

void player_showdamage(player * p)
{
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        p->boats[i].visible = DAMAGEONLY;
    }
}

bool player_hit(player * p, uint8_t x, uint8_t y)
{
    bool hit = false;
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        if (boat_hit(&(p->boats[i]), x, y)) {
            hit = true;
        }
    }
    return hit;
}

bool player_lost(player * p)
{
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        if ((p->boats)[i].destroyed == false) return false;
    }
    return true;
}

boat * player_get_placeable_boat(player * p)
{
    for (uint8_t i=0; i<NUM_BOATS; i++) {
        if (p->boats[i].placed == false) return &(p->boats[i]);
    }
    return 0;
}

