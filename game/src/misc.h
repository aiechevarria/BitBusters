#ifndef MISC_H
#define MISC_H

#include "types.h"
#include "levels.h"

/**
 * Miscelaneous functions.
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#define SEED 1234

#define false 0
#define true 1

typedef unsigned char   uint8;
typedef char            int8;
typedef unsigned short  uint16;
typedef unsigned int    uint32;
typedef unsigned char   bool;

unsigned char pseudoRNG(void);

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
bool updateCursor(LevelInfo* currentLevel, uint8* cursorY, uint8* cursorX, Input input);
Input listenForButtons();
void printLevelToConsole(LevelInfo* level);

#endif