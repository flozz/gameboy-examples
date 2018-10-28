#include <stdio.h>
#include <gb/console.h>
#include <gb/gb.h>
#include "helpers.h"

void title_screen(void) {
    clear_screen();
    gotoxy(4, 5);
    printf("Tic Tac Toe");
    gotoxy(3, 15);
    printf("- Press START -");
    waitpad(J_START);
    waitpadup();
}
