#include <gb/gb.h>
#include <types.h>

#include "tileset.h"
#include "tilemap.h"

#define WHITE  0
#define SILVER 1
#define GRAY   2
#define BLACK  3
#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

void wait_frames(INT8 count) {
    while (count) {
        count -= 1;
        wait_vbl_done();
    }
}

void main(void) {
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);
    set_bkg_tiles(0, 0, TILEMAP_WIDTH, TILEMAP_HEIGHT, TILEMAP);
    SHOW_BKG;

    // Black screen (initial state)
    BGP_REG = PALETTE(BLACK, BLACK, BLACK, BLACK);
    wait_frames(60);  // ~ 1s

    while (1) {
        // Fade-in
        BGP_REG = PALETTE(BLACK, BLACK, BLACK, BLACK);
        wait_frames(5);   // ~ 0.08s
        BGP_REG = PALETTE(GRAY, BLACK, BLACK, BLACK);
        wait_frames(5);   // ~ 0.08s
        BGP_REG = PALETTE(SILVER, GRAY, BLACK, BLACK);
        wait_frames(5);   // ~ 0.08s
        BGP_REG = PALETTE(WHITE, SILVER, GRAY, BLACK);

        wait_frames(60);  // ~ 1s

        // Invert colors
        BGP_REG = PALETTE(BLACK, GRAY, SILVER, WHITE);

        wait_frames(60);  // ~ 1s

        // Fade-out (inverted color)
        BGP_REG = PALETTE(BLACK, GRAY, SILVER, WHITE);
        wait_frames(5);   // ~ 0.08s
        BGP_REG = PALETTE(BLACK, BLACK, GRAY, SILVER);
        wait_frames(5);   // ~ 0.08s
        BGP_REG = PALETTE(BLACK, BLACK, BLACK, GRAY);
        wait_frames(5);   // ~ 0.08s
        BGP_REG = PALETTE(BLACK, BLACK, BLACK, BLACK);
        wait_frames(5);   // ~ 0.08s

        wait_frames(60);  // ~ 1s
    }
}

