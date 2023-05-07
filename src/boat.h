#ifndef __BOAT_H__
#define __BOAT_H__

#include <stdint.h>
#include <stdbool.h>

#define MAX_BOAT_SIZE 5

typedef enum {
    VISIBLE,
    DAMAGEONLY,
    NONE
} BOAT_VISIBILITY;

typedef enum {
    VERTICAL,
    HORIZONTAL
} BOAT_ROTATION;

typedef enum {
    GOOD,
    DAMAGE
} BOAT_DAMAGE;

typedef struct {
    // whether the boat is displayed
    BOAT_VISIBILITY visible;
    // true when placed
    bool placed;
    // length of the boat
    uint8_t size;
    // positions within virtual board tiles
    // position begins from top left most possible tile for the boat
    uint8_t x;
    uint8_t y;
    BOAT_ROTATION rotation;
    // owned sprite numbers
    uint8_t owned_sprite_ids [MAX_BOAT_SIZE];
    // damage track
    BOAT_DAMAGE hits [MAX_BOAT_SIZE];
    bool destroyed;
} boat;

void boat_init(boat * b, uint8_t size);
void boat_mv_up(boat * b);
void boat_mv_down(boat * b);
void boat_mv_left(boat * b);
void boat_mv_right(boat * b);
void boat_rot(boat * b);
bool boat_hit(boat * b, uint8_t x, uint8_t y);
bool boat_is_collide(boat * b1, boat * b2);

#endif
