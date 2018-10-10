#include <stdio.h>
#include <gb/gb.h>

// ==== waitpad() =========================================

void demo_waitpad_1(void) {
    printf("Press START!\n");
    waitpad(J_START);
    printf("> Good!");
}

void demo_waitpad_2(void) {
    printf("Press A or B!\n");
    waitpad(J_A | J_B);
    printf("> Good!");
}

void demo_waitpad_3(void) {
    UINT8 key;
    printf("Press LEFT or RIGHT!\n");
    key = waitpad(J_LEFT | J_RIGHT);
    if (key & J_LEFT) {
        printf("> You pressed LEFT");
    } else if (key & J_RIGHT) {
        printf("> You pressed RIGHT");
    }
}

// === waitpadup() ========================================

void demo_waitpadup(void) {
    printf("Press A!\n");
    waitpad(J_A);
    printf("> 1st\n");
    printf("Press A again!\n");
    waitpad(J_A);
    printf("> 2nd\n");

    waitpadup();  // Wait that all buttons are released

    printf("Press A one more time!\n");
    waitpad(J_A);
    printf("> 3rd");
}

// ==== joypad() ==========================================

void demo_joypad(void) {
    UINT8 prev_keys = 0;
    UINT8 keys = 0;

    printf("Press what you want\n\n");
    while (TRUE) {
        keys = joypad();
        if (keys == prev_keys) {
            continue;
        }
        if (keys > 0) {
            if (keys & J_UP) printf("UP ");
            if (keys & J_DOWN) printf("DOWN ");
            if (keys & J_LEFT) printf("LEFT ");
            if (keys & J_RIGHT) printf("RIGHT ");
            if (keys & J_SELECT) printf("SELECT ");
            if (keys & J_START) printf("START ");
            if (keys & J_A) printf("A ");
            if (keys & J_B) printf("B ");
            printf("\n");
        } else {
            printf("-\n");
        }
        prev_keys = keys;
    }}

// ========================================================

void main(void) {
    printf("==== waitpad() ====\n\n");

    demo_waitpad_1();
    printf("\n\n");
    demo_waitpad_2();
    printf("\n\n");
    demo_waitpad_3();

    printf("\n\n=== waitpadup() ===\n\n");

    demo_waitpadup();

    printf("\n\n==== joypad() =====\n\n");

    demo_joypad();
}

