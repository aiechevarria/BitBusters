/**
 * Item definitions
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

// The different item colors
typedef enum {
    RED,        // 5 Basic types of items
    ORANGE,
    GREEN,
    BLUE,
    PURPLE,
    NUM_ITEM_COLORS
} ItemColor;

// The different item grades 
typedef enum {
    NORMAL,     // The regular ones
    ROW,        // Clears an entire row
    COLUMN,     // Clears an entire column
    SPARK,      // Clears the adjacent 9 tiles
    BOMB,       // Clears all the items in the level that are of the same type
    NUM_ITEM_GRADES
} ItemGrade;