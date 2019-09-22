#include <stdio.h>
#include <gb/console.h>
#include <gb/gb.h>
#include "helpers.h"
#include "game.h"

// Game state variables
UINT8 GAME_BOARD[GAME_BOARD_SIZE * GAME_BOARD_SIZE];
UINT8 GAME_CURSOR_X;
UINT8 GAME_CURSOR_Y;

void game_draw_board(void) {
    clear_screen();
    gotoxy(4, 1);
    printf("Tic Tac Toe");
    gotoxy(1, 17);
    printf("X You - O Computer");
    gotoxy(0, 4);
    printf("       |   |   \n");
    printf("       |   |   \n");
    printf("       |   |   \n");
    printf("    ---+---+---\n");
    printf("       |   |   \n");
    printf("       |   |   \n");
    printf("       |   |   \n");
    printf("    ---+---+---\n");
    printf("       |   |   \n");
    printf("       |   |   \n");
    printf("       |   |   \n");
}

void game_draw_state(void) {
    UINT8 x;
    UINT8 y;
    UINT8 graph_x;
    UINT8 graph_y;
    UINT8 cell;

    for (cell = 0 ; cell < GAME_BOARD_SIZE * GAME_BOARD_SIZE ; cell += 1) {
        x = cell % GAME_BOARD_SIZE;
        y = cell / GAME_BOARD_SIZE;
        graph_x = GAME_BOARD_X + x * 3 + x + 1;
        graph_y = GAME_BOARD_Y + y * 3 + y + 1;
        gotoxy(graph_x, graph_y);
        setchar(GAME_BOARD[cell]);
    }
}

void game_draw_cursor(UINT8 cursor_char) {
    UINT8 graph_x = GAME_BOARD_X + GAME_CURSOR_X * 4 + 1;
    UINT8 graph_y = GAME_BOARD_Y + GAME_CURSOR_Y * 4 + 1;
    UINT8 cx;
    UINT8 cy;
    for (cy = graph_y - 1 ; cy <= graph_y + 1 ; cy += 1) {
        for (cx = graph_x - 1 ; cx <= graph_x + 1 ; cx += 1) {
            if (cx == graph_x && cy == graph_y) {
                continue;
            }
            gotoxy(cx, cy);
            setchar(cursor_char);
        }
    }
}

void game_clear_cursor() {
    game_draw_cursor(' ');
}

void game_draw_game_over(UINT8 status) {
    clear_line(1);
    switch (status) {
        case GAME_STATUS_WON:
            gotoxy(4, 1);
            printf("YOU WON! :)");
            break;
        case GAME_STATUS_LOST:
            gotoxy(4, 1);
            printf("YOU LOST! :(");
            break;
        case GAME_STATUS_EQUALITY:
            gotoxy(5, 1);
            printf("EQUALITY!");
            break;
    }
    clear_line(17);
    gotoxy(2, 17);
    printf("- Press START -");
    waitpad(J_START);
    waitpadup();
}

void game_player_play(void) {
    UINT8 key;
    UINT8 cell;

    while (1) {
        game_draw_cursor('/');
        waitpadup();  // Avoids keys to be read twice
        key = waitpad(J_UP | J_DOWN | J_LEFT | J_RIGHT | J_A);
        game_clear_cursor();
        if (key & J_UP && GAME_CURSOR_Y != 0) {
            GAME_CURSOR_Y -= 1;
        }
        if (key & J_DOWN && GAME_CURSOR_Y != GAME_BOARD_SIZE - 1) {
            GAME_CURSOR_Y += 1;
        }
        if (key & J_LEFT && GAME_CURSOR_X != 0) {
            GAME_CURSOR_X -= 1;
        }
        if (key & J_RIGHT && GAME_CURSOR_X != GAME_BOARD_SIZE - 1) {
            GAME_CURSOR_X += 1;
        }
        if (key & J_A) {
            cell = coord_2d_to_1d(GAME_CURSOR_X, GAME_CURSOR_Y);
            if (GAME_BOARD[cell] == GAME_BOARD_CELL_EMPTY) {
                GAME_BOARD[cell] = GAME_BOARD_CELL_PLAYER;
                break;
            }
        }
    }
}

void game_computer_play(void) {
    UINT8 x;
    UINT8 y;
    UINT8 cell;
    UINT8 player_score;
    UINT8 computer_score;
    INT8 lose_cell = -1;
    INT8 last_empty_cell = -1;

    // Check lines
    for (y = 0 ; y < GAME_BOARD_SIZE ; y += 1) {
        computer_score = 0;
        player_score = 0;
        for (x = 0 ; x < GAME_BOARD_SIZE ; x +=1) {
            cell = coord_2d_to_1d(x, y);
            switch (GAME_BOARD[cell]) {
                case GAME_BOARD_CELL_COMPUTER:
                    computer_score += 1;
                    break;
                case GAME_BOARD_CELL_PLAYER:
                    player_score += 1;
                    break;
                case GAME_BOARD_CELL_EMPTY:
                    last_empty_cell = cell;
                    break;
            }
        }
        // Direct win
        if (computer_score == 2 && player_score == 0) {
            GAME_BOARD[last_empty_cell] = GAME_BOARD_CELL_COMPUTER;
            return;
        }
        // Lose
        if (player_score == 2 && computer_score == 0) {
            lose_cell = last_empty_cell;
        }
    }

    // Check columns
    for (x = 0 ; x < GAME_BOARD_SIZE ; x += 1) {
        computer_score = 0;
        player_score = 0;
        for (y = 0 ; y < GAME_BOARD_SIZE ; y += 1) {
            cell = coord_2d_to_1d(x, y);
            switch (GAME_BOARD[cell]) {
                case GAME_BOARD_CELL_COMPUTER:
                    computer_score += 1;
                    break;
                case GAME_BOARD_CELL_PLAYER:
                    player_score += 1;
                    break;
                case GAME_BOARD_CELL_EMPTY:
                    last_empty_cell = cell;
                    break;
            }
        }
        // Direct win
        if (computer_score == 2 && player_score == 0) {
            GAME_BOARD[last_empty_cell] = GAME_BOARD_CELL_COMPUTER;
            return;
        }
        // Lose
        if (player_score == 2 && computer_score == 0) {
            lose_cell = last_empty_cell;
        }
    }

    // Check diagonal 1
    computer_score = 0;
    player_score = 0;
    for (x = 0 ; x < GAME_BOARD_SIZE ; x += 1) {
        cell = coord_2d_to_1d(x, x);
        switch (GAME_BOARD[cell]) {
            case GAME_BOARD_CELL_COMPUTER:
                computer_score += 1;
                break;
            case GAME_BOARD_CELL_PLAYER:
                player_score += 1;
                break;
            case GAME_BOARD_CELL_EMPTY:
                last_empty_cell = cell;
                break;
        }
    }

    // Direct win
    if (computer_score == 2 && player_score == 0) {
        GAME_BOARD[last_empty_cell] = GAME_BOARD_CELL_COMPUTER;
        return;
    }
    // Lose
    if (player_score == 2 && computer_score == 0) {
        lose_cell = last_empty_cell;
    }

    // Check diagonal 2
    computer_score = 0;
    player_score = 0;
    for (x = 0 ; x < GAME_BOARD_SIZE ; x += 1) {
        cell = coord_2d_to_1d(GAME_BOARD_SIZE - 1 - x, x);
        switch (GAME_BOARD[cell]) {
            case GAME_BOARD_CELL_COMPUTER:
                computer_score += 1;
                break;
            case GAME_BOARD_CELL_PLAYER:
                player_score += 1;
                break;
            case GAME_BOARD_CELL_EMPTY:
                last_empty_cell = cell;
                break;
        }
    }

    // Direct win
    if (computer_score == 2 && player_score == 0) {
        GAME_BOARD[last_empty_cell] = GAME_BOARD_CELL_COMPUTER;
        return;
    }
    // Lose
    if (player_score == 2 && computer_score == 0) {
        lose_cell = last_empty_cell;
    }

    cell = coord_2d_to_1d(1, 1);  // Middle cell
    if (lose_cell != -1) {
        GAME_BOARD[lose_cell] = GAME_BOARD_CELL_COMPUTER;
    } else if (GAME_BOARD[cell] == GAME_BOARD_CELL_EMPTY) {
        GAME_BOARD[cell] = GAME_BOARD_CELL_COMPUTER;
    } else {
        GAME_BOARD[last_empty_cell] = GAME_BOARD_CELL_COMPUTER;
    }
}

UINT8 game_check_status(void) {
    UINT8 x;
    UINT8 y;
    UINT8 cell;
    UINT8 player_score_h;
    UINT8 player_score_v;
    UINT8 computer_score_h;
    UINT8 computer_score_v;
    UINT8 has_empty_cells = 0;

    // Check lines and columns
    for (y = 0 ; y < GAME_BOARD_SIZE ; y += 1) {
        player_score_h = 0;
        player_score_v = 0;
        computer_score_h = 0;
        computer_score_v = 0;
        for (x = 0 ; x < GAME_BOARD_SIZE ; x += 1) {
            // Lines
            cell = coord_2d_to_1d(x, y);
            switch (GAME_BOARD[cell]) {
                case GAME_BOARD_CELL_EMPTY:
                    has_empty_cells = 1;
                    break;
                case GAME_BOARD_CELL_PLAYER:
                    player_score_h += 1;
                    break;
                case GAME_BOARD_CELL_COMPUTER:
                    computer_score_h += 1;
                    break;
            }
            // Swap x, y to check column in the same loop
            cell = coord_2d_to_1d(y, x);
            switch (GAME_BOARD[cell]) {
                // NOTE: no need to check again for empty cells...
                case GAME_BOARD_CELL_PLAYER:
                    player_score_v += 1;
                    break;
                case GAME_BOARD_CELL_COMPUTER:
                    computer_score_v += 1;
                    break;
            }
        }

        if (player_score_h == GAME_BOARD_SIZE || player_score_v == GAME_BOARD_SIZE) {
            return GAME_STATUS_WON;
        }
        if (computer_score_h == GAME_BOARD_SIZE || computer_score_v == GAME_BOARD_SIZE) {
            return GAME_STATUS_LOST;
        }
    }

    // Check diagonal
    player_score_h = 0;
    player_score_v = 0;
    computer_score_h = 0;
    computer_score_v = 0;
    for (x = 0 ; x < GAME_BOARD_SIZE ; x += 1) {
        // Diagonal 1 (top-left to bottom-right)
        cell = coord_2d_to_1d(x, x);
        switch (GAME_BOARD[cell]) {
            case GAME_BOARD_CELL_PLAYER:
                player_score_h += 1;
                break;
            case GAME_BOARD_CELL_COMPUTER:
                computer_score_h += 1;
                break;
        }
        // Diagonal 2 (top-right to bottom-left)
        cell = coord_2d_to_1d(GAME_BOARD_SIZE - 1 - x, x);
        switch (GAME_BOARD[cell]) {
            case GAME_BOARD_CELL_PLAYER:
                player_score_v += 1;
                break;
            case GAME_BOARD_CELL_COMPUTER:
                computer_score_v += 1;
                break;
        }
    }

    if (player_score_h == GAME_BOARD_SIZE || player_score_v == GAME_BOARD_SIZE) {
        return GAME_STATUS_WON;
    }
    if (computer_score_h == GAME_BOARD_SIZE || computer_score_v == GAME_BOARD_SIZE) {
        return GAME_STATUS_LOST;
    }

    // Nobody won, let's see if we can continue to play
    if (has_empty_cells) {
        return GAME_STATUS_PLAYING;
    } else {
        return GAME_STATUS_EQUALITY;
    }
}

void game_init(void) {
    UINT8 i = GAME_BOARD_SIZE * GAME_BOARD_SIZE;

    // Clear board state
    while (i) {
        i -= 1;
        GAME_BOARD[i] = GAME_BOARD_CELL_EMPTY;
    }

    // Reset cursor position to center of the board
    GAME_CURSOR_X = GAME_BOARD_SIZE / 2;
    GAME_CURSOR_Y = GAME_BOARD_SIZE / 2;
}

void game(void) {
    UINT8 status;

    game_init();
    game_draw_board();

    while (1) {
        // Player turn
        game_player_play();
        game_draw_state();
        status = game_check_status();
        if (status != GAME_STATUS_PLAYING) {
            break;
        }
        // Computer turn
        game_computer_play();
        game_draw_state();
        status = game_check_status();
        if (status != GAME_STATUS_PLAYING) {
            break;
        }
    }

    game_draw_game_over(status);
}
