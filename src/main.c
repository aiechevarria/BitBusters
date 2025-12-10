#include "types.h"
#include "misc.h"
#include "levels.h"
#include "renderer.h"

#include <stdio.h>

int main() {
    // Pointer to the current loaded level
    LevelInfo currentLevel;
    int8 selectedLevel = -1;
    int8 levelCursor = 0;

    // Last input read
    Input input = NONE;

    // Current cursor position
    uint8 cursorY = 0;
    uint8 cursorX = 0; 

    // Selected cursor position
    int8  selectedY = -1;
    int8  selectedX = -1;

    // Main loop
    while (true) {
        // Level selection
        while (selectedLevel == -1) {
            printf("Selected level: %d\n", levelCursor);

            // Scroll the levels
            input = listenForKeypress();

            if (input == RIGHT) {
                levelCursor = (levelCursor + 1) % MAX_LEVELS;
            } else if (input == SELECT) {
                selectedLevel = levelCursor;
            }
        }

        // Load the selected level
        initLevel(&currentLevel, selectedLevel);
        printf("Level %d, ", selectedLevel);

        // Print the corresponding message depending on the type of level
        switch (currentLevel.objective) {
            case OBJ_DESTROY_CORPT:
                printf("destroy all corruption.\n");
                break;
            case OBJ_DESTROY_ITEM:
                printf("destroy all items of type %d\n", currentLevel.objItemType);
                break;
            case OBJ_GET_SCORE:
                printf("get %d points\n", currentLevel.objScore);
                break;
            default:
                printf("\n");
                break;
        }

        // Tun the level while there are moves left
        while(currentLevel.moves > 0) {
            printLevelToConsole(currentLevel.bg, currentLevel.fg, cursorY, cursorX);

            // Check if there are any inputs
            input = listenForKeypress();

            printf("Score: %d\n", currentLevel.score);
            printf("Moves: %d\n", currentLevel.moves);
            switch (currentLevel.objective) {
                case OBJ_DESTROY_CORPT:
                    printf("Corruption left: %d\n", currentLevel.objCorptRemaining);
                    break;
                case OBJ_DESTROY_ITEM:
                    printf("Items remaining: %d\n", currentLevel.objItemRemaining);
                    break;
                case OBJ_GET_SCORE:
                    printf("Points to get: %d\n", currentLevel.objScore);
                    break;
                default:
                    printf("\n");
                    break;
            }

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
        }

        // Print the stats to to console
        printf("--- Finished Game ---\n");
        printf("------- STATS -------\n\n");
        printf("Score:           %d\n", currentLevel.score);
        switch(currentLevel.objective) {
            case OBJ_DESTROY_CORPT:
                printf("Corruption left: %d\n", currentLevel.objCorptRemaining);
                break;
            case OBJ_GET_SCORE:
                printf("Required score:  %d\n", currentLevel.objScore);
                break;
            case OBJ_DESTROY_ITEM:
                printf("Items left:      %d\n", currentLevel.objItemRemaining);
                break;
            default:
                break;
        }
        printf("---------------------\n\n");
        


        // Clear the currently selected level to jump back to the level select
        selectedLevel = -1;
    }

    return 0;
}