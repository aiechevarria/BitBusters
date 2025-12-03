/**
 * Level loading, drawing and handling functions
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#include "stdbool.h"
#include "level.h"

/* Private functions */
void drawLevel(uint8 number);
bool isMoveValid(Tile** tiles, uint8 origX, uint8 origY, uint8 destX, uint8 destY);

/**
 * Loads a level for the first time 
 * @param level A pointer to the initiated level. Must be preallocated.
 * @param number The number of the level to load
 */
void initLevel(LevelInfo* level, uint8 level) {

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
    if (isMoveValid(level->level, origX, origY, destX, destY)) {
        // Update the state if so

    }

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
bool isMoveValid(Tile** tiles, uint8 origX, uint8 origY, uint8 destX, uint8 destY) {
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
int performMove(Tile** tiles, uint8 origX, uint8 origY, uint8 destX, uint8 destY) {
   return false;
}

/**
 * Gets a random color.
 * @return The random color
 */
ItemColor getRandomColor() {
    return RED;
}