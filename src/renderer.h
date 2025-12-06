/**
 * Drivers for the VGA screen and the buttons.
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#include "graphics.h"

#define VGA_BASE 0x44A00000

void drawPixel(int x, int y, Pixel rgb);