//AUTOGENERATED FILE FROM png2asset
#ifndef METASPRITE_playsprites_H
#define METASPRITE_playsprites_H

#include <stdint.h>
#include <gbdk/platform.h>
#include <gbdk/metasprites.h>

#define playsprites_TILE_ORIGIN 0
#define playsprites_TILE_W 8
#define playsprites_TILE_H 8
#define playsprites_WIDTH 32
#define playsprites_HEIGHT 32
#define playsprites_TILE_COUNT 16
#define playsprites_PALETTE_COUNT 1
#define playsprites_COLORS_PER_PALETTE 4
#define playsprites_TOTAL_COLORS 4
#define playsprites_MAP_ATTRIBUTES 0

BANKREF_EXTERN(playsprites)

extern const palette_color_t playsprites_palettes[4];
extern const uint8_t playsprites_tiles[256];

extern const unsigned char playsprites_map[16];

#endif