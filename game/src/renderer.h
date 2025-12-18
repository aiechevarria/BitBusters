/**
 * Drivers for the VGA screen and the buttons.
 *
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#ifndef RENDERER_H
#define RENDERER_H

#include "graphics.h"

#define VGA_BASE 0x44A00000

void drawPixel(int x, int y, Pixel rgb);
void drawRect(int x, int y, int width, int height, Pixel color);
void renderMenu(int selection);
void renderAll();
void renderEndScreen(bool won, int finalScore);
#endif