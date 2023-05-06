#ifndef __SPRITE_ALLOC_H__
#define __SPRITE_ALLOC_H__

#include <stdint.h>

#define BADSPRALLOC 255

/*
 * SPRALLOC returns the ID of an available sprite id
 * on failure, returns BADSPRALLOC (255)
 */
uint8_t SPRALLOC();
/*
 * SPRFREE marks a sprite as free for allocation
 */
void SPRFREE(uint8_t id);

void SPRFREEALL();

#endif
