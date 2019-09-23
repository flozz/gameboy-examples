#include <gb/gb.h>

#include "./levels.tileset.h"
#include "./level01.tilemap.h"

void main(void) {
    set_bkg_data(128, LEVELS_TILESET_TILE_COUNT, LEVELS_TILESET);
    set_bkg_tiles(0, 0, LEVEL01_TILEMAP_WIDTH, LEVEL01_TILEMAP_HEIGHT, LEVEL01_TILEMAP);
    SHOW_BKG;
}
