#include <stdio.h>

#include "renderer.h"
#include "graphics.h"
#include "levels.h"

/**
 * Draws a particular pixel in the specified part of the screen.
 * 
 * @param x The X position
 * @param y The Y position
 * @param rgb The pixel color information
 */
void drawPixel(int x, int y, Pixel rgb) {
	// Draw only non transparent pixels
	if (rgb.r != 0xff && rgb.g != 0xff && rgb.b != 0xff) {
		int* ptr = (int*) VGA_BASE;
		int val = (rgb.r >> 4) | (rgb.b & 0xf0) | ((rgb.g & 0xf0) << 4);
		ptr[(y << 8) | x] = val;
	}
}

/**
 * Fetches a particular pixel color information from the specified coordinates.
 * 
 * @param x The X position
 * @param y The Y position
 * @return The pixel color information
 */
Pixel getPixel(int x, int y) {
	Pixel col;
	int* ptr = (int*) VGA_BASE;
	int val = ptr[(y<<8) | x];
	col.r = (val & 0xf) << 4;
	col.b = (val & 0xf0);
	col.g = (val & 0xf00) >> 4;
	return col;
}

/**
 * Draws the board's background. Should be called each time a background change is made.
 */
void renderBoardBackground() {

}

/**
 * Draws the board's foreground. Should be called each time a valid move is made.
 */
void renderBoardForeground() {

}

/**
 * Draws the board's foreground. Should be called each time a valid move is made.
 */
void renderCursor() {

}

/**
 * Draws the main menu
 */
void renderMenu() {

}

void printColored(const char text, int colorCode) {
    printf("\033[0;%dm%x\033[0m", 30 + colorCode, text);
}

/**
 * For debuging purposes, prints the current level to stdout.
 * 
 * @param tiles The tileset.
 * @param items The itemset.
 */
void printLevelToConsole(Tile tiles[MAX_Y_SPRITES][MAX_X_SPRITES], Item items[MAX_Y_SPRITES][MAX_X_SPRITES], uint8 cursorY, uint8 cursorX) {
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        for (int j = 0; j < MAX_X_SPRITES; j++) {
			if (i == cursorY && j == cursorX) {
				printColored(9, items[i][j]);
			} else {
				printColored(tiles[i][j], items[i][j]);
			}
        }
        printf("\n");
    }
}