#include "misc.h"
#include "levels.h"
#include "stdbool.h"

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


/**
 * Moves the cursor to the specified position. Checks for obstacles.
 * 
 * @param currentLevel The current level info. Used to check if there is an UNFIL where the cursor should be moved.
 * @param cursorY Cursor Y
 * @param cursorX Cursor X
 * @param input The input that was received
 * @return true If the move was successful.
 * @return false If the move could not be done.
 */
bool updateCursor(LevelInfo* currentLevel, uint8* cursorY, uint8* cursorX, Input input) {
    uint8 y = *cursorY;
    uint8 x = *cursorX;
    
    switch(input) {
        case UP:
            // If the cursor is not at the top of the screen AND the block above is not UNFIL, move
            if (y != 0 && currentLevel->bg[y - 1][x] != UNFIL) {
                (*cursorY)--;
            }
            return true;
        case DOWN:
            if (y != MAX_Y_SPRITES - 1 && currentLevel->bg[y + 1][x] != UNFIL) {
                (*cursorY)++;
            }
            return true;
        case LEFT:
            if (x != 0 && currentLevel->bg[y][x - 1] != UNFIL) {
                (*cursorX)--;
            }
            return true;
        case RIGHT:
            if (x != MAX_Y_SPRITES - 1 && currentLevel->bg[y][x + 1] != UNFIL) {
                (*cursorX)++;
            }
            return true;
        default:
            // Error, do nothing
            break;
    }
    return false;
}