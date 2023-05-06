#ifndef __BOAT_H__
#define __BOAT_H__

#include <stdint.h>
#include <stdbool.h>

#define MAX_BOAT_SIZE 5

typedef enum {
    VERTICAL,
    HORIZONTAL
} BOAT_ROTATION;

typedef struct {
    // whether the boat is displayed
    bool visible;
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
} boat;

void boat_init(boat * b, uint8_t size);
void boat_mv_up(boat * b);
void boat_mv_down(boat * b);
void boat_mv_left(boat * b);
void boat_mv_right(boat * b);
void boat_rot(boat * b);

#endif
