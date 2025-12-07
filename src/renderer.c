#include <stdio.h>

#include "renderer.h"
#include "graphics.h"

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

/**
 * For debuging purposes, prints the current level to stdout.
 * 
 * @param tiles The tileset.
 * @param items The itemset.
 */
void printLevelToConsole(Tile** tiles, Item** items) {
    for (int i = 0; i < NUM_TILES; i++) {
        for (int j = 0; j < NUM_TILES; j++) {
            printf("%x%x ", tiles[i][j], items[i][j]);
        }
        printf("\n");
    }
}