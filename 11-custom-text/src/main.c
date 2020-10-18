#include <gb/gb.h>
#include "./text.h"

void main(void) {
    SHOW_BKG;
    text_load_font();

    text_print_char_bkg(2, 2, 'A');
    text_print_char_bkg(3, 2, 'b');
    text_print_char_bkg(2, 3, '0');
    text_print_char_bkg(3, 3, '1');
    text_print_char_bkg(2, 4, ':');
    text_print_char_bkg(3, 4, ')');
    text_print_char_bkg(2, 5, '*');

    text_print_string_bkg(2, 7, "Hello\nWorld!");
}

