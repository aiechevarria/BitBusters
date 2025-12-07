/**
 * Miscelaneous functions.
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#ifndef MISC_H
#define MISC_H

#include "types.h"
#include "levels.h"

#define SEED 1234

#define true 1
#define false 0

typedef enum {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    SELECT,
    NONE,
    NUM_INPUTS
} Input;


unsigned char pseudoRNG(void);
void updateCursor(LevelInfo* currentLevel, uint8* cursorY, uint8* cursorX, Input input);

#endif