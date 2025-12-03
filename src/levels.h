/**
 * Level definitions
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#define MAX_LEVELS      3
#define MAX_X_COORDS    10
#define MAX_Y_COORDS    10

#define TILE_SIZE 5

/**
 * The different types of tiles a level can have.
 */
typedef enum {
    EMPTY,              // An item can be placed on top
    JELLY,              // An item can be placed on top and turns to EMPTY once broken
    DENSE,              // Denser JELLY, breaking it results in JELLY
    UNFIL,              // Unfillable space, for levels that have more complex layout
    NUM_TILES,
} Tile;

/**
 * The different types of objectives a level can have.
 */
typedef enum {
    OBJ_DESTROY_JELLY,      // Destroy all the jelly in a level
    OBJ_DESTROY_COLOR,      // Destroy a certain number of elements of a color
    OBJ_GET_SCORE           // Get a lot of score in this level;
} Objective;

typedef struct {
    // Parameters that do not update on each move
    uint8 startMoves;
    uint32 maxScore;
    Objective objective;

    // Params for particular objectives
    // OBJ_DESTROY_JELLY
    uint8 objJellyRemaining;    // How many jellies are left. Has to be prefilled

    // OBJ_DESTROY_COLOR
    ItemColor objColorType;     // What color to destroy
    uint16 objColorDestroy;     // How many of that color to destroy
    uint16 objScore;            // How many points to 

    // Parameters that are updated on each move. This gets copied on init
    uint8 moves;            // Remaining moves
    uint8 score;            // Current score
    Tile level[MAX_X_COORDS][MAX_Y_COORDS];     // Current state of the level
} LevelInfo;


const LevelInfo levels[MAX_LEVELS] = {
    {
        .moves = 25,
        .max_score = 0,
        .objective = OBJ_DESTROY_JELLY,
        .objJellyRemaining = 10,
        .level = {
            {JELLY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, JELLY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, JELLY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, JELLY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, JELLY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, JELLY, EMPTY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, JELLY, EMPTY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, JELLY, EMPTY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, JELLY, EMPTY},
            {EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, JELLY}
        }
    },
    {
        .moves = 25,
        .max_score = 0,
        .level = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
        }
    },
    {
        .moves = 25,
        .max_score = 0,
        .level = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1}
        }
    }
};


/* Public functions */
void initLevel(LevelInfo* level, uint8 level);