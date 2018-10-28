#include <stdio.h>
#include "title_screen.h"
#include "game.h"

// Entry point of the program, loop between title screen and new games
void main(void) {
    printf(" ");  // First gotoxy() call does not works else...

    while (TRUE) {
        title_screen();
        game();
    }
}

