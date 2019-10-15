#include <gb/gb.h>

#include "./levels.tileset.h"
#include "./level01.tilemap.h"

#define TRUE   1
#define FALSE  0

#define TILE_WIDTH         8
#define SCREEN_WIDTH_TILE  20
#define SCREEN_WIDTH_PX    SCREEN_WIDTH_TILE * TILE_WIDTH
#define SCREEN_HEIGH_TILE  18
#define SCREEN_HEIGH_PX    SCREEN_HEIGH_TILE * TILE_WIDTH

#define SPRITE_OFFSET_X  8
#define SPRITE_OFFSET_Y  16

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

#define PADDLE_Y         SPRITE_OFFSET_Y + (SCREEN_HEIGH_TILE - 1) * TILE_WIDTH
#define PADDLE_WIDTH     3 * TILE_WIDTH
#define PADDLE_ORIG_X    SPRITE_OFFSET_X + (SCREEN_WIDTH_PX - PADDLE_WIDTH) / 2

#define BALL_WIDTH  6

#define LEVEL01_BRICK_COUNT 39

UINT8 PADDLE_X;

UINT8 BALL_X = 50;
UINT8 BALL_Y = 120;
INT8 BALL_DELTA_X = 1;
INT8 BALL_DELTA_Y = -1;

UINT8 REMAINING_BRICKS = LEVEL01_BRICK_COUNT;


void move_paddle(INT8 delta) {
    // Update paddle's position
    if (delta == 0) {
        PADDLE_X = PADDLE_ORIG_X;
    } else {
        PADDLE_X += delta;
    }

    // Check that the paddle stay in the screen
    if (PADDLE_X < SPRITE_OFFSET_X) {
        PADDLE_X = SPRITE_OFFSET_X;
    } else if (PADDLE_X > SPRITE_OFFSET_X + SCREEN_WIDTH_PX - PADDLE_WIDTH) {
        PADDLE_X = SPRITE_OFFSET_X + SCREEN_WIDTH_PX - PADDLE_WIDTH;
    }

    // Move paddle's sprites
    move_sprite(SPRITE_PADDLE_L, PADDLE_X, PADDLE_Y);
    move_sprite(SPRITE_PADDLE_C, PADDLE_X + TILE_WIDTH, PADDLE_Y);
    move_sprite(SPRITE_PADDLE_R, PADDLE_X + 2 * TILE_WIDTH, PADDLE_Y);
}

void remove_brick(UINT8 x, UINT8 y) {
    UINT8 cells[2] = {TILE_EMPTY, TILE_EMPTY};
    set_bkg_tiles(x, y, 2, 1, cells);
    REMAINING_BRICKS -= 1;
}

UINT8 check_ball_collide(INT8 delta_x, INT8 delta_y) {
    UINT8 ball_x = BALL_X + delta_x;
    UINT8 ball_y = BALL_Y + delta_y;

    // Paddle
    if (ball_y + BALL_WIDTH - 1 >= PADDLE_Y) {
        if (ball_x >= PADDLE_X && ball_x <= PADDLE_X + PADDLE_WIDTH) {
            return TRUE;
        }
        if (ball_x + BALL_WIDTH - 1 >= PADDLE_X && ball_x + BALL_WIDTH <= PADDLE_X + PADDLE_WIDTH) {
            return TRUE;
        }
    }

    // Environment

    // Change considered ball collision point depending on direction
    if (BALL_DELTA_X > 0) {
        ball_x += BALL_WIDTH - 1;
    }
    if (BALL_DELTA_Y > 0) {
        ball_y += BALL_WIDTH - 1;
    }

    UINT8 ball_next_cell_x = (ball_x - SPRITE_OFFSET_X) / TILE_WIDTH;
    UINT8 ball_next_cell_y = (ball_y - SPRITE_OFFSET_Y) / TILE_WIDTH;
    UINT8 next_cell[1];

    get_bkg_tiles(ball_next_cell_x, ball_next_cell_y, 1, 1, next_cell);

    // remove bricks
    switch (next_cell[0]) {
        case TILE_BRICK_L:
            remove_brick(ball_next_cell_x, ball_next_cell_y);
            break;
        case TILE_BRICK_R:
            remove_brick(ball_next_cell_x - 1, ball_next_cell_y);
            break;
    }

    // return collision with env
    return next_cell[0] != TILE_EMPTY;
}

UINT8 check_gameover() {
    return BALL_Y + BALL_WIDTH >= SCREEN_HEIGH_PX + SPRITE_OFFSET_Y;
}

void main(void) {
    set_bkg_data(TILE_OFFSET, LEVELS_TILESET_TILE_COUNT, LEVELS_TILESET);
    set_bkg_tiles(0, 0, LEVEL01_TILEMAP_WIDTH, LEVEL01_TILEMAP_HEIGHT, LEVEL01_TILEMAP);
    SHOW_BKG;

    set_sprite_tile(SPRITE_BALL, TILE_BALL);
    set_sprite_tile(SPRITE_PADDLE_L, TILE_PADDLE_L);
    set_sprite_tile(SPRITE_PADDLE_C, TILE_PADDLE_C);
    set_sprite_tile(SPRITE_PADDLE_R, TILE_PADDLE_R);
    move_paddle(0);
    move_sprite(SPRITE_BALL, BALL_X, BALL_Y);
    SHOW_SPRITES;

    while (REMAINING_BRICKS) {
        // Player's moves
        UINT8 keys = joypad();
        if (keys & J_LEFT) {
            move_paddle(-2);
        } else if (keys & J_RIGHT) {
            move_paddle(+2);
        }

        // Check for Game Over
        if (check_gameover()) {
            break;
        }

        // Move the ball
        if (check_ball_collide(BALL_DELTA_X, 0)) {
            BALL_DELTA_X = -BALL_DELTA_X;
        }
        if (check_ball_collide(0, BALL_DELTA_Y)) {
            BALL_DELTA_Y = -BALL_DELTA_Y;
        }
        BALL_X += BALL_DELTA_X;
        BALL_Y += BALL_DELTA_Y;
        move_sprite(SPRITE_BALL, BALL_X, BALL_Y);

        wait_vbl_done();
    }
}
