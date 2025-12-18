#include "misc.h"
#include "levels.h"
#include "xil_io.h"

// Define addresses from user's memory map
#define GPIO_0_BASE_ADDR 0x40000000 // Likely Switches (16-bit) logic
#define GPIO_1_BASE_ADDR 0x40010000 // Likely Buttons (4-bit?) logic

// We will also check the second channel of GPIO 0 just in case
#define GPIO_0_DATA2_OFFSET 0x8

unsigned int rngState = SEED;

/**
 * Returns a pseudorandom number.
 * 
 * @return The pseudorandom number in range [0..255] 
 */
unsigned char pseudoRNG(void) {
    rngState = (1664525 * rngState + 1013904223);
    return (rngState >> 24) & 0xFF;
}

/**
 * Initialize the GPIO for button input.
 * With direct memory access, we just need to ensure the direction registers (TRI) are set to Input.
 * Offset 0x4 is TRI for Ch1, 0xC is TRI for Ch2.
 */
void initInput() {
    // Set all channels to Input (0xFFFFFFFF) just to be safe
    Xil_Out32(GPIO_0_BASE_ADDR + 0x4, 0xFFFFFFFF); 
    Xil_Out32(GPIO_0_BASE_ADDR + 0xC, 0xFFFFFFFF);
    Xil_Out32(GPIO_1_BASE_ADDR + 0x4, 0xFFFFFFFF);
}

/**
 * Reads the hardware buttons and maps them to the Input enum.
 * Aggregates inputs from multiple GPIO sources to ensure we catch the buttons 
 * regardless of the specific block design wiring.
 */
Input listenForButtons() {
    static u32 last_switches = 0;
    Input i = NONE;

    
    u32 buttons = Xil_In32(GPIO_1_BASE_ADDR);
 
    u32 switches_1 = Xil_In32(GPIO_0_BASE_ADDR);
    u32 switches_2 = Xil_In32(GPIO_0_BASE_ADDR + 0x8);
    u32 current_switches = switches_1 | switches_2;

    
    if (buttons & 0x01) i = RIGHT;
    if (buttons & 0x02) i = UP;
    if (buttons & 0x04) i = DOWN;
    if (buttons & 0x08) i = LEFT;
    

    bool switch_toggled = ((current_switches ^ last_switches) & 0x01);
    
    last_switches = current_switches;

    if (switch_toggled) {
        i = SELECT;
        xil_printf("switch_selected");
    }
    
    if (i != NONE) {
        msleep(100);
        return i;        
    } else {
        return NONE;
    }
}



/**
 * Lee botones e interruptores con gestión de estado inicial.
 * Soluciona el problema de que el juego empiece solo si el switch ya estaba arriba.
 */
Input listenForControls() {
    static u32 last_switches = 0;
    static bool first_run = true; // Bandera para la primera ejecución
    Input i = NONE;

    // Leer estado actual del hardware
    u32 buttons = Xil_In32(GPIO_1_BASE_ADDR);
    u32 switches = Xil_In32(GPIO_0_BASE_ADDR) | Xil_In32(GPIO_0_BASE_ADDR + 0x8);

    // 1. Mapeo de Botones (Prioridad normal)
    if (buttons & 0x01) i = RIGHT;
    if (buttons & 0x02) i = UP;
    if (buttons & 0x04) i = DOWN;
    if (buttons & 0x08) i = LEFT;

    // 2. Lógica del Interruptor SW0 (SELECT)
    if (first_run) {
        // Si es la primera vez que entramos aquí (al encender la Basys),
        // guardamos cómo está el switch AHORA y NO hacemos nada.
        // Esto evita el "disparo fantasma" al inicio.
        last_switches = switches;
        first_run = false;
    } else {
        // Si no es la primera vez, buscamos cambios (toggle)
        // Usamos XOR (^) para ver si el bit 0 ha cambiado respecto a la última vez
        bool switch_toggled = ((switches ^ last_switches) & 0x01);
        
        if (switch_toggled) {
            i = SELECT;
        }
    }

    // Actualizamos el estado "anterior" para la siguiente vuelta
    last_switches = switches;

    // Retorno con debouncing básico
    if (i != NONE) {
        msleep(100);
        return i;        
    } else {
        return NONE;
    }
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
            if (x != MAX_X_SPRITES - 1 && currentLevel->bg[y][x + 1] != UNFIL) {
                (*cursorX)++;
            }
            return true;
        default:
            // Error, do nothing
            break;
    }
    return false;
}

/*
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
*/


/**
 * For debuging purposes, prints the current level to stdout.
 * 
 * @param tiles The tileset.
 * @param items The itemset.
 */
void printLevelToConsole(LevelInfo* level) {
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        for (int j = 0; j < MAX_X_SPRITES; j++) {
            xil_printf("%x%x ", level->bg[i][j], level->fg[i][j]);
        }
        xil_printf("\n");
    }



}