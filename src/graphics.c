#include "graphics.h"

const char itemSprites[NUM_ITEMS][SPRITE_SIZE][SPRITE_SIZE] = {
    { 
        {'0', '0', '0'},                // Normal item
        {'0', '1', '0'},
        {'0', '0', '0'}
    },
    { 
        {'0', '1', '0'},                // Column
        {'0', '1', '0'},
        {'0', '1', '0'}
    },
    { 
        {'0', '0', '0'},                // Row
        {'1', '1', '1'},
        {'0', '0', '0'}
    },
    { 
        {'1', '0', '1'},                // Spark
        {'0', '1', '0'},
        {'1', '0', '1'}
    },
    { 
        {'0', '1', '1'},                // Bomb
        {'1', '1', '1'},
        {'1', '1', '0'}
    }
};

const char tileSprites[NUM_TILES][SPRITE_SIZE][SPRITE_SIZE] = {
    // TODO THis should be drawn in the background
};
