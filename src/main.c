#include "types.h"
#include "misc.h"
#include "levels.h"
#include "renderer.h"

// Pointer to the current loaded level
LevelInfo currentLevel;

int main() {
    Input input = NONE;
    uint8 cursorY = 0;
    uint8 cursorX = 0; 
    

    // Load the selected level
    initLevel(&currentLevel, 1);

    printLevelToConsole(currentLevel.bg, currentLevel.fg);

    while (true) {
        // Check if there are any inputs

        // When an input is made, pass it to move()
        

    }
    return 0;
}