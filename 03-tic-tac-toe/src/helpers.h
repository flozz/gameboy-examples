#ifndef _HELPERS_H
#define _HELPERS_H

#define COLS 20  // Console width
#define ROWS 18  // Console height

// Helper function to clear the entire screen
void clear_screen(void);

// Helper function that clears the given line
void clear_line(UINT8 y);

// Convers coordinate between 2D (x, y) to 1D (index in an one-dimensional
// array)
UINT8 coord_2d_to_1d(UINT8 x, UINT8 y);

#endif
