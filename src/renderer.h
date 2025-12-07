/**
 * Drivers for the VGA screen and the buttons.
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#include "graphics.h"
#include "levels.h"

#define VGA_BASE 0x44A00000

void drawPixel(int x, int y, Pixel rgb);
void printLevelToConsole(Tile tiles[MAX_Y_SPRITES][MAX_X_SPRITES], Item items[MAX_Y_SPRITES][MAX_X_SPRITES], uint8 cursorY, uint8 cursorX);