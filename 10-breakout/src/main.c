#include <gb/gb.h>

#include "./levels.tileset.h"
#include "./level01.tilemap.h"

#define TILE_OFFSET    128
#define TILE_EMPTY     TILE_OFFSET + 0
#define TILE_BRICK_L   TILE_OFFSET + 8
#define TILE_BRICK_R   TILE_OFFSET + 9
#define TILE_PADDLE_L  TILE_OFFSET + 12
#define TILE_PADDLE_C  TILE_OFFSET + 13
#define TILE_PADDLE_R  TILE_OFFSET + 14
#define TILE_BALL      TILE_OFFSET + 15

#define SPRITE_BALL      0
#define SPRITE_PADDLE_L  1
#define SPRITE_PADDLE_C  2
#define SPRITE_PADDLE_R  3

#define PADDLE_Y         16 + 17 * 8

void main(void) {
    set_bkg_data(TILE_OFFSET, LEVELS_TILESET_TILE_COUNT, LEVELS_TILESET);
    set_bkg_tiles(0, 0, LEVEL01_TILEMAP_WIDTH, LEVEL01_TILEMAP_HEIGHT, LEVEL01_TILEMAP);
    SHOW_BKG;

    set_sprite_tile(SPRITE_BALL, TILE_BALL);
    move_sprite(SPRITE_BALL, 50, 120);
    set_sprite_tile(SPRITE_PADDLE_L, TILE_PADDLE_L);
    move_sprite(SPRITE_PADDLE_L, 50, PADDLE_Y);
    set_sprite_tile(SPRITE_PADDLE_C, TILE_PADDLE_C);
    move_sprite(SPRITE_PADDLE_C, 58, PADDLE_Y);
    set_sprite_tile(SPRITE_PADDLE_R, TILE_PADDLE_R);
    move_sprite(SPRITE_PADDLE_R, 66, PADDLE_Y);
    SHOW_SPRITES;
}
