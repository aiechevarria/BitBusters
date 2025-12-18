#include "types.h"
#include "misc.h"
#include "levels.h"
#include "renderer.h"
#include "xil_io.h"

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
int8 attemps = 0;

int main() {
    if (attemps == 0){
        initInput();
    }
    while (true) {
        // Level selection
        while (selectedLevel == -1) {
            xil_printf("Selected level: %d\n", levelCursor);

            renderMenu(levelCursor); 

            // USAMOS LA NUEVA FUNCIÓN AQUÍ
            while(input == NONE) {
                input = listenForControls(); 
            }

            if (input == RIGHT) {
                levelCursor = (levelCursor + 1) % MAX_LEVELS;
            } else if (input == LEFT) {
                levelCursor--;
                if (levelCursor < 0) levelCursor = MAX_LEVELS - 1;
            } 
            // ACEPTAR NIVEL: Con SW0 (SELECT) o con botón DOWN
            else if (input == SELECT || input == DOWN) { 
                selectedLevel = levelCursor;
            }

            input = NONE;
            msleep(150); 
        }

        // Load the selected level
        initLevel(&currentLevel, selectedLevel);
        xil_printf("Level %d, ", selectedLevel);

        // Print the corresponding message depending on the type of level
        switch (currentLevel.objective) {
            case OBJ_DESTROY_CORPT:
                xil_printf("destroy all corruption.\n");
                break;
            case OBJ_DESTROY_ITEM:
                xil_printf("destroy all items of type %d\n", currentLevel.objItemType);
                break;
            case OBJ_GET_SCORE:
                xil_printf("get %d points\n", currentLevel.objScore);
                break;
            default:
                xil_printf("\n");
                break;
        }
        bool levelWon = false;
        // Tun the level while there are moves left
        while(currentLevel.moves > 0) {
            printLevelToConsole(&currentLevel);

            input = NONE;

            // Check if there are any inputs
            while(input == NONE) {
                input = listenForButtons();
            }

            if (checkWinCondition(&currentLevel)) {
                levelWon = true;
                break; 
            }

            xil_printf("Score: %d\n", currentLevel.score);
            xil_printf("Moves: %d\n", currentLevel.moves);
            switch (currentLevel.objective) {
                case OBJ_DESTROY_CORPT:
                    xil_printf("Corruption left: %d\n", currentLevel.objCorptRemaining);
                    break;
                case OBJ_DESTROY_ITEM:
                    xil_printf("Items remaining: %d\n", currentLevel.objItemRemaining);
                    break;
                case OBJ_GET_SCORE:
                    xil_printf("Points to get: %d\n", currentLevel.objScore);
                    break;
                default:
                    xil_printf("\n");
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
                        renderAll();

                        // Decrement the moves
                        currentLevel.moves--;

                        // And disselect the previous block
                        selectedY = -1;
                        selectedX = -1;
                    }
                }
            }
            renderAll();
        }

        attemps++; //Amuentamos intentos para evitar reinicializar el switch.

        renderAll();
        msleep(50); 

        // Mostrar pantalla de resultado
        renderEndScreen(levelWon, currentLevel.score);

        // Esperar a que el usuario pulse algo para volver al menú
        input = NONE;
        while(input == NONE) {
            input = listenForControls();
        }
        
        // Resetear para volver al menú
        selectedLevel = -1;
        msleep(50);    


        // Print the stats to to console
        xil_printf("--- Finished Game ---\n");
        xil_printf("------- STATS -------\n\n");
        xil_printf("Score:           %d\n", currentLevel.score);
        switch(currentLevel.objective) {
            case OBJ_DESTROY_CORPT:
                xil_printf("Corruption left: %d\n", currentLevel.objCorptRemaining);
                break;
            case OBJ_GET_SCORE:
                xil_printf("Required score:  %d\n", currentLevel.objScore);
                break;
            case OBJ_DESTROY_ITEM:
                xil_printf("Items left:      %d\n", currentLevel.objItemRemaining);
                break;
            default:
                break;
        }
        xil_printf("---------------------\n\n");
        resetLevel(&currentLevel);
        

        // Clear the currently selected level to jump back to the level select
        selectedLevel = -1;
    }

    return 0;
}