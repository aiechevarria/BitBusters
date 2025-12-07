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
 * Explodes a bomb and replaces each tile with a new, random one.
 * 
 * @param level Pointer to the ongoing level.
 * @param y Bomb y position
 * @param x Bomb x position
 * @param item Item to explode
 * @return The number of exploded items.
 */
int specialExplodeBomb(LevelInfo* level, uint8 y, uint8 x, Item item) {

}


/**
 * Checks that for a certain tile if a combination can be made. If a combination can be made, return true and 
 * the tiles that will cause the combinaiton to happen.
 */
bool checkForCombination(Item item[MAX_Y_SPRITES][MAX_X_SPRITES], uint8 y, uint8 x, Combination* c) {
    uint8 numConsColumn = 0;
    uint8 numConsRow = 0;

    char columnAccum = 0;
    char rowAccum = 0;

    // Init the combination
    c->yMax = -1;
    c->yMin = -1;
    c->xMax = -1;
    c->xMin = -1;
    c->itemToGenerate = ITEM_EMPTY;

    // First check if the current column has more or 3 consecutive items
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        // If the current item matches the item in the current slot:
        if (item[i][x] == item[y][x]) {
            // Increment the accumulator of consecutive items
            columnAccum++;
        }

        // Also, if there is nothing else to process, finish the evaluation right here
        if (item [i][x] != item[y][x] || i == MAX_Y_SPRITES - 1) {
            // If the accumulator was more than 3 at some point and y was inside of it, flag the line as having that char
            if (columnAccum >= 3 && y > i - 1 - columnAccum && y < i - 1) {
                numConsColumn = columnAccum;

                // Store the bounds of the combination and stop the column search
                c->yMin = i - 1 - columnAccum;
                c->yMax = i - 1;
                break;
            }
            columnAccum = 0;
        }
    }

    // Same for the X axis
    for (int i = 0; i < MAX_X_SPRITES; i++) {
        // If the current item matches the item in the current slot:
        if (item[y][i] == item[y][x]) {

            // Increment the accumulator of consecutive items
            rowAccum++;
        }

        // Also, if there is nothing else to process, finish the evaluation right here
        if (item [y][i] != item[y][x] || i == MAX_X_SPRITES - 1) {
            // If the accumulator was more than 3 at some point and y was inside of it, flag the line as having that char
            if (rowAccum >= 3 && x > i - 1 - rowAccum && x < i - 1) {
                numConsRow = rowAccum;

                // Store the bounds of the combination and stop the column search
                c->xMin = i - 1 - rowAccum;
                c->xMax = i - 1;
                break;
            }
            rowAccum = 0;
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

int removeItemsFromCombination(Item item[MAX_Y_SPRITES][MAX_X_SPRITES], uint8 y, uint8 x, Combination* c) {
    Combination temp;
    int score;

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
    
    // Clear the combination
    c->yMax = -1;
    c->yMin = -1;
    c->xMax = -1;
    c->xMin = -1;
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

    // If it's a bomb, explode it
    if (level->fg[origY][origX] == ITEM_BOMB) {
        score = specialExplodeBomb(level, origY, origX, level->fg[destY][destX]);
    } else if (level->fg[destY][destX] == ITEM_BOMB) {
        score = specialExplodeBomb(level, destY, destX, level->fg[origY][origX]);
    } else {
        // If not, make the move
        exchange(level, origY, origX, destY, destX);

        // Check if the move made a combination
        if (checkForCombination(level->fg, destY, destX, &c)) {
            score += removeItemsFromCombination(level->fg, destY, destX, &c);
        }

        // Also check the origin
        if (checkForCombination(level->fg, origY, origX, &c)) {
            score += removeItemsFromCombination(level->fg, origY, origX, &c);
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