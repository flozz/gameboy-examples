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
    // Here, if you press "A" one time, you will pass through the two
    // waitpad() calls
    printf("Press A!\n");
    waitpad(J_A);
    printf("> 1st\n");
    waitpad(J_A);
    printf("> 2nd\n");

    // Wait that all buttons are released
    waitpadup();

    printf("Press A one more time!\n");
    waitpad(J_A);
    printf("> 3rd");
}

// ==== joypad() ==========================================

void demo_joypad(void) {
    UINT8 prev_keys = 0;
    UINT8 keys = 0;

    printf("Press what you want\n\n");

    // Infinit loop to read keys
    while (1) {
        // Read currently pressed keys
        keys = joypad();

        // If nothing changed from previous iteration, we continue to next
        // iteration (to avoid displaying the same message again and again, we
        // print a new message only when something changed)
        if (keys == prev_keys) {
            continue;
        }

        // We display the pressed keys...
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

            // ... or "-" if no key is pressed.
        } else {
            printf("-\n");
        }

        // We keep the pressed keys
        prev_keys = keys;
    }
}

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

