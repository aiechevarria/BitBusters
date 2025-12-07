#include "misc.h"
#include "levels.h"

unsigned int rngState = SEED;

/**
 * Returns a pseudorandom number.
 * 
 * @return The pseudorandom number in range [0..255] 
 */
unsigned char pseudoRNG(void) {
    rngState = (1664525 * rngState + 1013904223);

    // Return the high 8 bits (better than low bits)
    return (rngState >> 24) & 0xFF;
}


void updateCursor(LevelInfo* currentLevel, uint8* cursorY, uint8* cursorX, Input input) {
    uint8 y = *cursorY;
    uint8 x = *cursorX;
    
    switch(input) {
        case UP:
            // If the cursor is not at the top of the screen AND the block above is not UNFIL, move
            if (y != 0 && currentLevel->bg[y - 1][x] != UNFIL) {
                (*cursorY)--;
            }
            break;
        case DOWN:
            if (y != MAX_Y_SPRITES - 1 && currentLevel->bg[y + 1][x] != UNFIL) {
                (*cursorY)++;
            }
            break;
        case LEFT:
            if (x != 0 && currentLevel->bg[y][x - 1] != UNFIL) {
                (*cursorX)--;
            }
            break;
        case RIGHT:
            if (x != MAX_Y_SPRITES - 1 && currentLevel->bg[y][x + 1] != UNFIL) {
                (*cursorX)++;
            }
            break;
        default:
            // Error, do nothing
            break;
    }
}