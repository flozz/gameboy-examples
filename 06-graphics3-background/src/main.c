#include <gb/gb.h>

#include "tileset.h"

void main(void) {
    UINT8 keys;

    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILESET_MAP_WIDTH, TILESET_MAP_HEIGHT, TILESET_MAP);
    SHOW_BKG;

    while (TRUE) {
        keys = joypad();
        if (keys & J_UP) scroll_bkg(0, -1);
        if (keys & J_DOWN) scroll_bkg(0, 1);
        if (keys & J_LEFT) scroll_bkg(-1, 0);
        if (keys & J_RIGHT) scroll_bkg(1, 0);
        wait_vbl_done();
    }
}

