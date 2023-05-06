#include <gb/gb.h>

#include "sprite_alloc.h"

#define MAX_SPRITES 40

typedef enum {
    FREE = 0,
    ALLOCATED = 1
} spralloc_status;

static spralloc_status allocations [MAX_SPRITES] = {FREE};

uint8_t SPRALLOC()
{
    for (uint8_t i=0; i<MAX_SPRITES; i++) {
        if (allocations[i] == FREE) {
            allocations[i] = ALLOCATED;
            return i;
        }
    }
    return BADSPRALLOC;
}

void SPRFREE(uint8_t id)
{
    if (id >= MAX_SPRITES) return;
    if (allocations[id] == ALLOCATED) {
        allocations[id] = FREE;
        hide_sprite(id);
        set_sprite_tile(id, 0);
    }
}

void SPRFREEALL()
{
    for (uint8_t i=0; i<MAX_SPRITES; i++) {
        SPRFREE(i);
    }
}
