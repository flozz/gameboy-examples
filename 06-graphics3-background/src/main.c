#include <gb/gb.h>

#include "tileset.h"
#include "tilemap.h"

void main(void) {
    UINT8 keys;

    // Copy the tileset in the video memory
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);

    // Copy the tilemap in the video memory
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);

    // Display the background layer
    SHOW_BKG;

    while (1) {
        keys = joypad();

        // Scroll to the corresponding direction when a button
        // of the D-Pad is pressed
        if (keys & J_UP) scroll_bkg(0, -1);
        if (keys & J_DOWN) scroll_bkg(0, 1);
        if (keys & J_LEFT) scroll_bkg(-1, 0);
        if (keys & J_RIGHT) scroll_bkg(1, 0);

        // Reset background position when START is pressed
        if (keys & J_START) move_bkg(0, 0);

        // Wait until the screen was redrawn
        wait_vbl_done();
    }
}

