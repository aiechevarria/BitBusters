#include "misc.h"
#include "levels.h"
#include "stdbool.h"

// These are optional and used only for the debug functions without the basys
// Can be removed if listenForKeypress is commented
#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <fcntl.h>


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

Input listenForKeypress() {
    struct termios oldt, newt;
    char ch;

    // Set up terminal settings for non-canonical mode
    tcgetattr(STDIN_FILENO, &oldt);        // Get current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);       // Disable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply new settings

    // Loop until a valid key is pressed
    while (1) {
        ch = getchar();  // Read a single character from input

        // Check if the key pressed matches any of the valid inputs
        switch (ch) {
            case 'w':  // UP
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
                return UP;
            case 'a':  // LEFT
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
                return LEFT;
            case 's':  // DOWN
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
                return DOWN;
            case 'd':  // RIGHT
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
                return RIGHT;
            case 'e':  // RIGHT
                tcsetattr(STDIN_FILENO, TCSANOW, &oldt);  // Restore terminal settings
                return SELECT;
            default:
                // If the input is not recognized, continue looping
                continue;
        }
    }
}