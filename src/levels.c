/**
 * Level loading, drawing and handling functions
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#include "levels.h"
#include "misc.h"
#include "stdbool.h"

/* Private functions */
void drawLevel(uint8 number);
char isMoveValid(Tile** tiles, uint8 origX, uint8 origY, uint8 destX, uint8 destY);

/**
 * Loads a level for the first time 
 * @param level A pointer to the initiated level. Must be preallocated.
 * @param number The number of the level to load
 */
void initLevel(LevelInfo* level, uint8 number) {

}

/**
 * Draws a level in the level part of the screen
 * @param number The number of the level to draw 
 */
void drawLevel(uint8 number) {

}



/**
 * Moves a tile from the original coordinates to the destination coordinates.
 * If the move can be done, decrement the number of moves the player has by one and add to it's score.
 * If not, return without altering state.
 * 
 * @param level Pointer to the ongoing level.
 * @param origX Original X position.
 * @param origY Original Y position.
 * @param destX Destination X position.
 * @param destY Destination Y position.
 */
void move(LevelInfo* level, uint8 origX, uint8 origY, uint8 destX, uint8 destY) {
    // Check if the move is valid
    return;
}

/**
 * Checks if the move is valid or not
 * @param origX Original X position.
 * @param origY Original Y position.
 * @param destX Destination X position.
 * @param destY Destination Y position.
 * @return true if valid, false if not 
 */
char isMoveValid(Tile** tiles, uint8 origX, uint8 origY, uint8 destX, uint8 destY) {
   return false;
}


/**
 * Checks if the move is valid or not
 * @param level Pointer to the ongoing level.
 * @param origX Original X position.
 * @param origY Original Y position.
 * @param destX Destination X position.
 * @param destY Destination Y position.
 * @return The score 
 */
int performMove(Tile** tiles, Item** items, uint8 origX, uint8 origY, uint8 destX, uint8 destY) {
   return false;
}

/**
 * Checks that for a certain tile if a combination can be made. If a combination can be made, return true and 
 * the tiles that will cause the combinaiton to happen.
 */
bool checkForCombination(Item** item, uint8 x, uint8 y, Combination* c) {
    uint8 numConsColumn = 0;
    uint8 numConsRow = 0;

    char columnAccum = 0;
    char rowAccum = 0;

    // First check if the current column has more or 3 consecutive items
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        // If the current item matches the item in the current slot:
        if (item[x][i] == item[x][y]) {

            // Increment the accumulator of consecutive items
            columnAccum++;
        } else {
            // If the accumulator was more than 3 at some point and y was inside of it, flag the line as having that char
            // TODO check if this is right
            if (columnAccum > 3 && y >= i - 1 - columnAccum && y < i - 1) {
                numConsColumn = columnAccum;

                // Store the bounds of the combination and stop the column search
                c->yMin = i - 1 - columnAccum;
                c->yMax = i - 1;
                break;
            } else {
                columnAccum = 0;
            }
        }
    }

    // Same for the X axis
    for (int i = 0; i < MAX_X_SPRITES; i++) {
        // If the current item matches the item in the current slot:
        if (item[i][y] == item[x][y]) {

            // Increment the accumulator of consecutive items
            rowAccum++;
        } else {
            // If the accumulator was more than 3 at some point and y was inside of it, flag the line as having that char
            // TODO check if this is right
            if (rowAccum > 3 && x >= i - 1 - rowAccum && x < i - 1) {
                numConsRow = rowAccum;

                // Store the bounds of the combination and stop the column search
                c->xMin = i - 1 - rowAccum;
                c->xMax = i - 1;
                break;
            } else {
                rowAccum = 0;
            }
        }
    }

    // If there are 5 consecutive rows, create a bomb
    if (numConsColumn >= 5 || numConsRow >= 5) {
        c->itemToGenerate = ITEM_BOMB;
    } else if (numConsColumn >= 3 && numConsRow >= 3) {
        c->itemToGenerate = ITEM_SPARK;
    } else if (numConsColumn >= 4) {
        c->itemToGenerate = ITEM_COLUMN;
    } else if (numConsRow >= 4) {
        c->itemToGenerate = ITEM_COLUMN;
    } else {
        c->itemToGenerate = ITEM_EMPTY;
    }

    // Return true if the movement can be made
    if (numConsColumn >= 3 || numConsRow >= 3) {
        return true;
   } else {
        return false;
    }
}

/**
 * For a given tileset, generates a random pattern of items.
 * @param tiles The tileset.
 * @param items The itemset to generate.
 */
void generateRandomItemset(Tile** tiles, Item** items) {
    Combination c;
    bool combinationFound = false;

    for (int i = 0; i < NUM_TILES; i++) {
        for (int j = 0; j < NUM_TILES; j++) {
            // If the tile can be filled, do so with a random item
            if (tiles[i][j] != UNFIL) {
                items[i][j] = pseudoRNG() % NUM_COLORED_ITEMS;
            } else {
                // If the background is of UNFIL type, put nothing in it
                items[i][j] =  ITEM_EMPTY;
            }
        }
    }

    // After that, for each tile, check that no combinations are present, and if so, change that item for another one 
    do {
        combinationFound = false;
        for (int i = 0; i < NUM_TILES; i++) {
            for (int j = 0; j < NUM_TILES; j++) {
                // If a combination is possible for that position, replace it with another random item
                if (checkForCombination(items, i, j, &c)) {
                    items[i][j] = pseudoRNG() % NUM_COLORED_ITEMS;

                    // Note that a combination has been found, keep trying until no combination is present
                    combinationFound = true;
                }
            }
        }
    } while (combinationFound == true);
}