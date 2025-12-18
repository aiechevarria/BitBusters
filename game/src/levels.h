/**
 * Level definitions
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */
#ifndef LEVELS_H
#define LEVELS_H

#include "types.h"

#define MAX_LEVELS      3

// Number of elements in a level
#define MAX_X_SPRITES    10
#define MAX_Y_SPRITES    10

// Max number of colored items
#define NUM_COLORED_ITEMS 5

#define MAX_COMBINATION_PARTS 6


typedef unsigned char   bool;
#define false 0
#define true 1

// The different types of tiles a level can have. Drawn on the background
typedef enum {
    EMPTY,              // An item can be placed on top
    CORPT,              // An item can be placed on top and turns to EMPTY once broken
    DENSE,              // Denser CORPT, breaking it results in CORPT
    UNFIL,              // Unfillable space, for levels that have more complex layout
    NUM_TILES,
} Tile;

// All possible types of items. Drawn on the foreground, unless the tile is of type UNFILL
typedef enum {
    ITEM_RED,
    ITEM_ORANGE,
    ITEM_GREEN,
    ITEM_BLUE,
    ITEM_PURPLE,
    ITEM_ROW,           // Clears an entire row
    ITEM_COLUMN,        // Clears an entire column
    ITEM_BOMB,         // Clears the adjacent 9 tiles
    ITEM_SPARK,          // Clears all the items in the level that are of the same type
    ITEM_EMPTY,         // Represents no item
    NUM_ITEMS
} Item;

// The different types of objectives a level can have.
typedef enum {
    OBJ_DESTROY_CORPT,      // Destroy all the corruption in a level
    OBJ_DESTROY_ITEM,       // Destroy a certain number of items
    OBJ_GET_SCORE,          // Get a lot of score in this level;
    NUM_OBJECTIVES
} Objective;

// A full combination
typedef struct {
    Item itemToGenerate;                                // What item should be generated due to this combination.
    int8 itemY, itemX;                                  // Where the item should be placed
    int8 yMin, yMax;                                    // Y range that the combination has
    int8 xMin, xMax;                                    // X range that the combination has
} Combination;

typedef struct {
    // General parameters
    uint8 moves;
    uint32 score;
    Objective objective;

    // Params for particular objectives
    // OBJ_DESTROY_CORPT
    uint8 objCorptRemaining;    // How many corruption tiles are left. Has to be prefilled

    // OBJ_DESTROY_ITEM
    Item objItemType;          // What item to destroy
    uint16 objItemRemaining;   // How many items of that color are left to destroy

    // OBJ_GET_SCORE
    uint32 objScore;           // How much score should be reached to end the level

    // Background and foreground
    Tile bg[MAX_Y_SPRITES][MAX_X_SPRITES];     // Current state of the background
    Item fg[MAX_Y_SPRITES][MAX_X_SPRITES];     // Current state of the foreground
} LevelInfo;

extern const LevelInfo levels[MAX_LEVELS];

/* Public functions */
void initLevel(LevelInfo* level, uint8 number);
int performMove(LevelInfo* level, uint8 origY, uint8 origX, uint8 destY, uint8 destX);
bool checkWinCondition(LevelInfo* level);
void resetLevel(LevelInfo* level);
#endif