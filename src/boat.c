#include <stdbool.h>

#include "boat.h"
#include "game_definitions.h"
#include "sprite_alloc.h"

void boat_init(boat * b, uint8_t size)
{
    b->placed = false;
    b->visible = NONE;
    b->x = GAME_SIZE_X/2 - 1;
    b->y = GAME_SIZE_Y/2 - 1;
    b->size = size;
    b->rotation = HORIZONTAL;
    b->destroyed = false;
    for (uint8_t i=0; i<size; i++) {
        (b->owned_sprite_ids)[i] = SPRALLOC();
        (b->hits)[i] = GOOD;
    }
}

void boat_mv_up(boat * b)
{
    if (b->y > 0) {
        (b->y)--;
    }
}

void boat_mv_down(boat * b)
{
    uint8_t lowest_tile;
    switch (b->rotation) {
    case HORIZONTAL:
        lowest_tile = b->y;
        break;
    case VERTICAL:
        lowest_tile = b->y + b->size - 1;
        break;
    }
    if (lowest_tile < GAME_SIZE_Y-1) {
        (b->y)++;
    }
}

void boat_mv_left(boat * b)
{
    if (b->x > 0) {
        (b->x)--;
    }
}

void boat_mv_right(boat * b)
{
    uint8_t furthest_tile;
    switch (b->rotation) {
    case HORIZONTAL:
        furthest_tile = b->x + b->size - 1;
        break;
    case VERTICAL:
        furthest_tile = b->x;
        break;
    }
    if (furthest_tile < GAME_SIZE_X-1) {
        (b->x)++;
    }
}

void boat_rot(boat * b)
{
    uint8_t furthest_tile;
    switch (b->rotation) {
    case HORIZONTAL:
        b->rotation = VERTICAL;
        furthest_tile = b->y + b->size;
        if (furthest_tile >= GAME_SIZE_Y) {
            b->y -= furthest_tile - GAME_SIZE_Y;
        }
        break;
    case VERTICAL:
        b->rotation = HORIZONTAL;
        furthest_tile = b->x + b->size;
        if (furthest_tile >= GAME_SIZE_X) {
            b->x -= furthest_tile - GAME_SIZE_X;
        }
        break;
    }
}

void boat_destroyed(boat * b)
{
    for (uint8_t i=0; i<b->size; i++) {
        if ((b->hits)[i] == GOOD) return;
    }
    b->destroyed = true;
    return;
}

bool boat_hit(boat * b, uint8_t x, uint8_t y)
{
    bool hit = false;
    uint8_t boat_x = b->x;
    uint8_t boat_y = b->y;
    uint8_t * boat_pos_iter = b->rotation==VERTICAL ? &boat_y : &boat_x;
    for (uint8_t i=0; i<b->size; i++) {
        if (boat_x == x && boat_y == y) {
            // FOUND A HIT
            hit = true;
            b->hits[i] = DAMAGE;
            break;
        }
        (*boat_pos_iter)++;
    }
    boat_destroyed(b);
    return hit;
}
