#include <gb/gb.h>

#include "tileset.h"

void main(void) {
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILESET_MAP_WIDTH, TILESET_MAP_HEIGHT, TILESET_MAP);
    SHOW_BKG;
}

