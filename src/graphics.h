/**
 * All graphic sprites
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#include "items.h"
#include "levels.h"

#define SPRITE_SIZE 3

// Item Sprites
const char itemSprites[NUM_ITEM_GRADES][SPRITE_SIZE][SPRITE_SIZE] = {
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

const char tileSprites[NUM_TILES][TILE_SIZE][TILE_SIZE] = {
    // TODO THis should be drawn in the background
};
