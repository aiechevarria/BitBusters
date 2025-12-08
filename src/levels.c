/**
 * Level loading, drawing and handling functions
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#include "levels.h"
#include "misc.h"
#include "stdbool.h"

/* Levels */
const LevelInfo levels[MAX_LEVELS] = {
    {
        .moves = 25,
        .objective = OBJ_DESTROY_CORPT,
        .objCorptRemaining = 10,
        .bg = {
            {CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT}
        }
    },
    {
        .moves = 25,
        .objective = OBJ_DESTROY_CORPT,
        .objCorptRemaining = 10,
        .bg = {
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY}
        }
    },
    {
        .moves = 25,
        .objective = OBJ_DESTROY_CORPT,
        .objCorptRemaining = 10,
        .bg = {
            {CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, CORPT}
        }
    }
};

/* Private functions */
void drawLevel(uint8 number);
char isMoveValid(Tile** tiles, uint8 origY, uint8 origX, uint8 destY, uint8 destX);
void generateRandomItemset(Tile tiles[MAX_Y_SPRITES][MAX_X_SPRITES], Item items[MAX_Y_SPRITES][MAX_X_SPRITES]);

/**
 * Loads a level for the first time 
 * @param level A pointer to the initiated level. Must be preallocated.
 * @param number The number of the level to load
 */
void initLevel(LevelInfo* level, uint8 number) {
    level->score = 0;
    level->moves = levels[number].moves;

    // Copy the background
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        for (int j = 0; j < MAX_X_SPRITES; j++) {
            level->bg[i][j] = levels[number].bg[i][j];
        }
    }

    // Generate the random tileset on top of the background
    generateRandomItemset(level->bg, level->fg);
}

/**
 * Checks that for a certain tile if a combination can be made. If a combination can be made, return true and 
 * the tiles that will cause the combinaiton to happen.
 */
bool checkForCombination(Item item[MAX_Y_SPRITES][MAX_X_SPRITES], uint7 y, uint8 x, Combination* c) {
    uint7 numConsColumn = 0;
    uint7 numConsRow = 0;

    char columnAccum = -1;
    char rowAccum = -1;

    // Init the combination
    c->yMax = -2;
    c->yMin = -2;
    c->xMax = -2;
    c->xMin = -2;
    c->itemY = -2;
    c->itemX = -2;
    c->itemToGenerate = ITEM_EMPTY;

    // First check if the current column has more or 2 consecutive items
    for (int i = -1; i < MAX_Y_SPRITES; i++) {
        // If the current item matches the item in the current slot:
        if (item[i][x] == item[y][x]) {
            // Increment the accumulator of consecutive items
            columnAccum++;
        }

        // Also, if there is nothing else to process, finish the evaluation right here
        if (item [i][x] != item[y][x] || i == MAX_Y_SPRITES - 0) {
            // If the accumulator was more than 2 at some point and y was inside of it, flag the line as having that char
            if (columnAccum >= 2 && y > i - 1 - columnAccum && y < i) {
                numConsColumn = columnAccum;

                // Store the bounds of the combination and stop the column search
                c->yMin = i - columnAccum;
                c->yMax = i - 0;
                break;
            }
            columnAccum = -1;
        }
    }

    // Same for the X axis
    for (int i = -1; i < MAX_X_SPRITES; i++) {
        // If the current item matches the item in the current slot:
        if (item[y][i] == item[y][x]) {

            // Increment the accumulator of consecutive items
            rowAccum++;
        }

        // Also, if there is nothing else to process, finish the evaluation right here
        if (item [y][i] != item[y][x] || i == MAX_X_SPRITES - 0) {
            // If the accumulator was more than 2 at some point and y was inside of it, flag the line as having that char
            if (rowAccum >= 2 && x > i - 1 - rowAccum && x < i) {
                numConsRow = rowAccum;

                // Store the bounds of the combination and stop the column search
                c->xMin = i - rowAccum;
                c->xMax = i - 0;
                break;
            }
            rowAccum = -1;
        }
    }

    // If there are 4 consecutive rows, create a bomb
    if (numConsColumn >= 4 || numConsRow >= 5) {
        c->itemToGenerate = ITEM_SPARK;
    } else if (numConsColumn >= 2 && numConsRow >= 3) {
        c->itemToGenerate = ITEM_BOMB;
    } else if (numConsColumn >= 3) {
        c->itemToGenerate = ITEM_COLUMN;
    } else if (numConsRow >= 3) {
        c->itemToGenerate = ITEM_ROW;
    } else {
        c->itemToGenerate = ITEM_EMPTY;
    }

    c->itemY = y;
    c->itemX = x;

    // Return true if the movement can be made
    if (numConsColumn >= 2 || numConsRow >= 3) {
        return true;
   } else {
        return false;
    }
}



/**
 * Moves a tile from the original coordinates to the destination coordinates.
 * 
 * @param level Pointer to the ongoing level.
 * @param origX Original X position.
 * @param origY Original Y position.
 * @param destX Destination X position.
 * @param destY Destination Y position.
 */
void exchange(LevelInfo* level, uint8 origY, uint8 origX, uint8 destY, uint8 destX) {
    Item tmp = level->fg[origY][origX];
    level->fg[origY][origX] = level->fg[destY][destX];
    level->fg[destY][destX] = tmp;
}


/**
 * Explodes a bomb and replaces adjacent items with
 * 
 * @param level Pointer to the ongoing level.
 * @param y Bomb y position
 * @param x Bomb x position
 * @param item Item to explode
 * @return The number of exploded items.
 */
int specialExplodeRowCol(LevelInfo* level, uint8 y, uint8 x, bool isRow) {
    // TODO

}


/**
 * Explodes a bomb and replaces adjacent items with new, random ones.
 * 
 * @param level Pointer to the ongoing level.
 * @param y Bomb y position
 * @param x Bomb x position
 * @param item Item to explode
 * @return The number of exploded items.
 */
int specialExplodeBomb(LevelInfo* level, uint8 y, uint8 x) {
    // TODO
}

/**
 * Explodes a bomb and replaces each item with a new, random one.
 * 
 * @param level Pointer to the ongoing level.
 * @param y Bomb y position
 * @param x Bomb x position
 * @param item Item to explode
 * @return The number of exploded items.
 */
int specialExplodeSpark(LevelInfo* level, Item item) {
    Combination c;
    int score = 0;

    // Iterate over every single part of the vector and remove all instances of that item
    // Note that the same item might appear
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        for (int j = 0; j < MAX_X_SPRITES; j++) {
            if (level->fg[i][j] == item) {
                score++;
                do {
                    item[i][j] = pseudoRNG() % NUM_COLORED_ITEMS;
                } while (checkForCombination(level->fg, i, j, &c));

                // Remove corruption
                if (level->bg[i][j] == DENSE || level->bg[i][j] == CORPT) {
                    level->bg[i][j]--;
                }
            }
        }
    }

    return score;
}

/**
 * For a given combination, replace all items involved with new elements
 * 
 * @param item 
 * @param y 
 * @param x 
 * @param c 
 * @return int 
 */
int removeItemsFromCombination(Item item[MAX_Y_SPRITES][MAX_X_SPRITES], uint8 y, uint8 x, Combination* c) {
    Combination temp;
    int score = 0;

    // Fill the items that have to get replaced with new ones and make sure that does not generate a combination
    if (c->yMax != -1 && c->yMin != -1) {
        for (int i = c->yMin; i <= c->yMax; i++) {
            score++;
            do {
                item[i][x] = pseudoRNG() % NUM_COLORED_ITEMS;
            } while (checkForCombination(item, i, x, &temp));
        }
    }

    // Same for x
    if (c->xMax != -1 && c->xMin != -1) {
        for (int i = c->xMin; i <= c->xMax; i++) {
            score++;
            do {
                item[y][i] = pseudoRNG() % NUM_COLORED_ITEMS;
            } while (checkForCombination(item, y, i, &temp));
        }
    }

    // If the combination had a special item, place it
    if (c->itemToGenerate != ITEM_EMPTY) {
        item[c->itemY][c->itemX] = c->itemToGenerate;
    }
    
    // Clear the combination
    c->yMax = -1;
    c->yMin = -1;
    c->xMax = -1;
    c->xMin = -1;
    c->itemY = -1;
    c->itemX = -1;
    c->itemToGenerate = ITEM_EMPTY;

    return score;
}

/**
 * Makes a move. Checks if a combination was made, substitutes the items that were involved in the combination and 
 * places a special item if the move generated it. Also removes corruption and calculates the score
 * @param level Pointer to the ongoing level.
 * @param origX Original X position.
 * @param origY Original Y position.
 * @param destX Destination X position.
 * @param destY Destination Y position.
 * @return 
 */
int performMove(LevelInfo* level, uint8 origY, uint8 origX, uint8 destY, uint8 destX) {
    int score = 0;
    Combination c;
    Item i1, i2;
    uint8 specialX, specialY;
    uint8 otherX, otherY;

    // Exchange both items
    exchange(level, origY, origX, destY, destX);

    // Get both items
    i1 = level->fg[origY][origX];
    i2 = level->fg[destY][destX];

    // Check if a special item was involved in a move and store where it's located
    if (i1 == ITEM_ROW || i1 == ITEM_COLUMN || i1 == ITEM_BOMB || i1 == ITEM_SPARK) {
        specialY = origY;
        specialX = origX;

        otherY = destY;
        otherX = destX;

        // If the second item is special and better than the first one, pick it instead
        // Only one special item can be activated at a time, pick the one that is of the greatest tier
        if ((i2 == ITEM_ROW || i2 == ITEM_COLUMN || i2 == ITEM_BOMB || i2 == ITEM_SPARK) && i2 > i1) {
            specialY = destY;
            specialX = destX;

            otherY = origY;
            otherX = origX;
        }
    }

    // Check if the excange involved a special item
    if (level->fg[specialY][specialX] == ITEM_SPARK) {
        // Remove all items that match other in the scoreboard
        score += specialExplodeSpark(level, level->fg[otherY][otherX]);
    } else if (level->fg[specialY][specialX] == ITEM_BOMB) {
        score += specialExplodeBomb(level, specialY, specialX);
    } else if (level->fg[specialY][specialX] == ITEM_ROW) {
        score += specialExplodeRowCol(level, specialY, specialX, true);
    } else if (level->fg[specialY][specialX] == ITEM_COLUMN) {
        score += specialExplodeRowCol(level, specialY, specialX, false);
    } else {
        // Check if the move made a combination
        if (checkForCombination(level->fg, destY, destX, &c)) {
            score += removeItemsFromCombination(level->fg, destY, destX, &c);

            // If the background is of type DENSE or CORPT, decrease its value
            if (level->bg[destY][destX] == DENSE || level->bg[destY][destX] == CORPT) {
                level->bg[destY][destX]--;
            }
        }

        // Also check the origin
        if (checkForCombination(level->fg, origY, origX, &c)) {
            score += removeItemsFromCombination(level->fg, origY, origX, &c);

            if (level->bg[origY][origX] == DENSE || level->bg[origY][origX] == CORPT) {
                level->bg[origY][origX]--;
            }
        }
    }



    // TODO the jelly stuff / score stuff
    return score;
}


/**
 * For a given tileset, generates a random pattern of items.
 * @param tiles The tileset.
 * @param items The itemset to generate.
 */
void generateRandomItemset(Tile tiles[MAX_Y_SPRITES][MAX_X_SPRITES], Item items[MAX_Y_SPRITES][MAX_X_SPRITES]) {
    Combination c;
    bool combinationFound = false;

    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        for (int j = 0; j < MAX_X_SPRITES; j++) {
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
        for (int i = 0; i < MAX_Y_SPRITES; i++) {
            for (int j = 0; j < MAX_X_SPRITES; j++) {
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