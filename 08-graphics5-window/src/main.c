#include <gb/gb.h>

#include "tileset.h"
#include "window_tilemap.h"

void main(void) {
    UINT8 background_tilemap[32*32];
    UINT16 i;

    // Copy the tileset in the video memory
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);

    // Generates a tilemap for the Background layer
    // and copy it in the video memory
    for (i = 0 ; i < 32*32 ; i++) {
        background_tilemap[i] = 0;  // tile #0 (background pattern)
    }
    set_bkg_tiles(0, 0, 32, 32, background_tilemap);

    // Copy the tilemap in the Window layer
    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);

    // Moves the Window layer to display it at the
    // bottom of the screen
    move_win(7, 128);

    // Display the Background and Window layers
    SHOW_BKG;
    SHOW_WIN;

    while (1) {
        // Sroll the Background layer to show that the
        // Window layer is static
        scroll_bkg(-1, -1);

        // Wait until the screen was redrawn
        wait_vbl_done();
    }
}

