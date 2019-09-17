#ifndef _GAME_H
#define _GAME_H

#include <types.h>

#define GAME_BOARD_X      4
#define GAME_BOARD_Y      4
#define GAME_BOARD_SIZE   3

#define GAME_STATUS_PLAYING   0
#define GAME_STATUS_WON       1
#define GAME_STATUS_LOST      2
#define GAME_STATUS_EQUALITY  3

#define GAME_BOARD_CELL_EMPTY     ' '
#define GAME_BOARD_CELL_PLAYER    'x'
#define GAME_BOARD_CELL_COMPUTER  'o'

// Displays the game board (parts that will not change during the game)
void game_draw_board(void);

// Displays the game state ("x" and "o" in the cells)
void game_draw_state(void);

// Displays the player's cursor in the selected cell
// NOTE: We take the char to display as parameter to allow us to use the same
// function to clear the cursor by writing spaces (see next function)
void game_draw_cursor(UINT8 cursor_char);

// Clears the player's cursor
void game_clear_cursor();

// Displays the game over screen
void game_draw_game_over(UINT8 status);

// Makes the player play (allow the player to move the cursor and select a
// cell)
void game_player_play(void);

// Makes the computer play
void game_computer_play(void);

// Check the status of the GAME:
//
// * Does the player won?
// * Does the computer won?
// * Is the game terminated (no more empty cell)?
UINT8 game_check_status(void);

// Initialize global game-state variables for a new game
void game_init(void);

// Main function of the game: Loops between player and computer turns and check
// the game status
void game(void);

#endif
