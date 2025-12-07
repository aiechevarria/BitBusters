#include "types.h"
#include "misc.h"
#include "levels.h"
#include "renderer.h"

int main() {
    // Pointer to the current loaded level
    LevelInfo currentLevel;

    // Last input read
    Input input = NONE;

    // Current cursor position
    uint8 cursorY = 0;
    uint8 cursorX = 0; 

    // Selected cursor position
    int8  selectedY = -1;
    int8  selectedX = -1;
    

    // Load the selected level
    initLevel(&currentLevel, 1);

    printLevelToConsole(currentLevel.bg, currentLevel.fg);

    while (true) {
        // Check if there are any inputs

        // If there was no previous selection
        if (selectedY == -1) {
            // If a select was made, mark these as selected
            if (input == SELECT) {
                selectedY = cursorY;
                selectedX = cursorX;
            } else {
                // If the move was of a diferent type, move the cursor
                updateCursor(&currentLevel, &cursorY, &cursorX, input);
            }
        } else {
            // If it is select again, disselect everything
            if (input == SELECT) {
                selectedY = -1;
                selectedX = -1;
            } else {
                // If something was selected AND a move was just made, move the cursor 
                if (updateCursor(&currentLevel, &cursorY, &cursorX, input)) {
                    // If the movement was succesful, exchange both blocks and run all the game logic
                    currentLevel.score += performMove(&currentLevel, selectedY, selectedX, cursorY, cursorX);

                    // Decrement the moves
                    currentLevel.moves--;

                    // And disselect the previous block
                    selectedY = -1;
                    selectedX = -1;
                }
            }
        }
        // After
    }

    return 0;
}