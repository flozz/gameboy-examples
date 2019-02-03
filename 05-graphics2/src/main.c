#include <gb/gb.h>

#include "tileset.h"
#include "tilemap.h"

void main(void) {
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
    SHOW_BKG;
}

