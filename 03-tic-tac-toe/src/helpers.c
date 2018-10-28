#include <gb/console.h>
#include "game.h"
#include "helpers.h"

void clear_screen(void) {
    UINT8 x;
    UINT8 y = ROWS;
    while (y) {
        y -= 1;
        x = COLS;
        while (x) {
            x -= 1;
            gotoxy(x, y);
            setchar(' ');
        }
    }
}

void clear_line(UINT8 y) {
    UINT8 x = COLS;
    while (x) {
        x -= 1;
        gotoxy(x, y);
        setchar(' ');
    }
}

UINT8 coord_2d_to_1d(UINT8 x, UINT8 y) {
    return y * GAME_BOARD_SIZE + x;
}
