#include <gb/gb.h>

#include "player.sprites.h"

// Id ("nb") of the two sprites used to represent the player
#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1

// Animations data for the players sprites
UINT8 PLAYER_SPRITE_ANIM_L[] = {
// LEN | FLIP | TILES ID        | DIRECTION
   4,    0,      0 , 4,  0,  8,   // Down
   4,    0,     12, 16, 12, 20,   // Up
   4,    0,     24, 28, 24, 32,   // Right
   4,    1,     26, 30, 26, 34,   // Left
};
UINT8 PLAYER_SPRITE_ANIM_R[] = {
// LEN | FLIP | TILES           | DIRECTION
   4,    0,      2,  6,  2, 10,   // Down
   4,    0,     14, 18, 14, 22,   // Up
   4,    0,     26, 30, 26, 34,   // Right
   4,    1,     24, 28, 24, 32,   // Left
};

// Offset of the animation of each direction in the global animation data
#define PLAYER_DIRECTION_DOWN  0
#define PLAYER_DIRECTION_UP    6
#define PLAYER_DIRECTION_RIGHT 12
#define PLAYER_DIRECTION_LEFT  18

// Variables containing player state
UINT8 player_x;
UINT8 player_y;
UINT8 player_direction;
UINT8 player_animation_frame;
UINT8 is_player_walking;

// Flip the given sprite on X axis.
//
// sprite_id: the id ("nb") of the sprite to update.
void flip_sprite_horiz(UINT8 sprite_id) {
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) | S_FLIPX);
}

// Remove the flip the given sprite on X axis.
//
// sprite_id: the id ("nb") of the sprite to update.
void unflip_sprite_horiz(UINT8 sprite_id) {
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) & ~S_FLIPX);
}

// Update the tiles of the sprite to animate it.
//
// sprite_id: the id ("nb") of the sprite to update
// anim:      pointer to the animation data
// direction: direction of the animation (= offset of the animation in the global animation data)
// frame:     the new frame of the animation that will be displayed
//
// Returns the next frame of the animation.
UINT8 update_sprite_animation(UINT8 sprite_id, UINT8 *anim, UINT8 direction, UINT8 frame) {
    UINT8 len = anim[direction];
    UINT8 flip = anim[direction + 1];
    UINT8 tile_id = anim[direction + 2 + frame];

    if (flip) {
        flip_sprite_horiz(sprite_id);
    } else {
        unflip_sprite_horiz(sprite_id);
    }

    set_sprite_tile(sprite_id, tile_id);

    return (frame + 1) % len;
}

void main(void) {
    UINT8 keys = 0;
    UINT8 frame_skip = 8;  // Update player's animation every 8 frame to
                           // slow down the animation (8 frames = ~133 ms
                           // between each animation frames)

    // Initialize player's state
    player_x = 80;
    player_y = 72;
    player_direction = PLAYER_DIRECTION_DOWN;
    player_animation_frame = 0;
    is_player_walking = 0;

    // Load sprites' tiles in video memory
    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);

    // Use 8x16 sprites
    SPRITES_8x16;

    // Makes sprites "layer" visible
    SHOW_SPRITES;

    // Init the two sprites used for the player
    move_sprite(PLAYER_SPRITE_L_ID, player_x, player_y);
    set_sprite_prop(PLAYER_SPRITE_L_ID, S_PALETTE);

    move_sprite(PLAYER_SPRITE_R_ID, player_x + 8, player_y);
    set_sprite_prop(PLAYER_SPRITE_R_ID, S_PALETTE);

    while (1) {
        // Wait for v-blank (screen refresh)
        wait_vbl_done();

        // Read joypad keys to know if the player is walking
        // and in which direction
        keys = joypad();
        if (keys & J_UP) {
            player_direction = PLAYER_DIRECTION_UP;
            is_player_walking = 1;
        } else if (keys & J_DOWN) {
            player_direction = PLAYER_DIRECTION_DOWN;
            is_player_walking = 1;
        } else if (keys & J_LEFT) {
            player_direction = PLAYER_DIRECTION_LEFT;
            is_player_walking = 1;
        } else if (keys & J_RIGHT) {
            player_direction = PLAYER_DIRECTION_RIGHT;
            is_player_walking = 1;
        } else {
            is_player_walking = 0;
            frame_skip = 1;  // Force refresh of the animation frame
        }

        // Update the player position if it is walking
        if (is_player_walking) {
            if (player_direction == PLAYER_DIRECTION_RIGHT) player_x += 1;
            else if (player_direction == PLAYER_DIRECTION_LEFT) player_x -= 1;
            else if (player_direction == PLAYER_DIRECTION_UP) player_y -= 1;
            else if (player_direction == PLAYER_DIRECTION_DOWN) player_y += 1;
            move_sprite(PLAYER_SPRITE_L_ID, player_x, player_y);
            move_sprite(PLAYER_SPRITE_R_ID, player_x + 8, player_y);

            // We do not update the animation on each frame: the animation
            // will be too quick. So we skip frames
            frame_skip -= 1;
            if (!frame_skip) {
                frame_skip = 8;
            } else {
                continue;
            }
        } else {
            player_animation_frame = 0;
        }

        // Update sprites' tiles
        update_sprite_animation(
                PLAYER_SPRITE_L_ID,
                PLAYER_SPRITE_ANIM_L,
                player_direction,
                player_animation_frame);
        player_animation_frame = update_sprite_animation(
                PLAYER_SPRITE_R_ID,
                PLAYER_SPRITE_ANIM_R,
                player_direction,
                player_animation_frame);
    }
}
