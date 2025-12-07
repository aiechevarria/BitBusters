/**
 * All graphics, sprites and colors.
 * 
 * @authors Aitor Echevarría Floranes, Rubén San Pedro.
 */

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "levels.h"

#define SPRITE_SIZE 12

// Color mappings
#define RS_RGB {0xff, 0x00, 0x00}
#define RL_RGB {0xff, 0x43, 0x43}
#define GS_RGB {0x11, 0xB9, 0x48}
#define GL_RGB {0x31, 0xD7, 0x68}
#define BS_RGB {0x00, 0x00, 0xff}
#define BL_RGB {0x20, 0x71, 0xff}
#define PS_RGB {0x73, 0x00, 0x98}
#define PL_RGB {0x82, 0x09, 0xc5}
#define OS_RGB {0xf4, 0x63, 0x05}
#define OL_RGB {0xf4, 0x84, 0x3c}
#define SP_RGB {0xf4, 0xf4, 0x00}
#define WH_RGB {0xfe, 0xfe, 0xfe}
#define BK_RGB {0x00, 0x00, 0x00}
#define C1_RGB {0xc0, 0xc0, 0xc0}
#define C2_RGB {0x80, 0x80, 0x80}
#define TS_RGB {0xff, 0xff, 0xff}

// Color names
typedef enum {
    RS,         // Red strong
    RL,         // Red light
    GS,         // Green strong
    GL,         // Green light
    BS,         // Blue strong
    BL,         // Blue light
    PS,         // Purple strong
    PL,         // Purple light
    OS,         // Orange strong
    OL,         // Orange light
    SP,         // Special
    WH,         // White
    BK,         // Black
    C1,         // Corruption 1
    C2,         // Corruption 2
    TS,         // Transparent
    NUM_COLORS
} Colors;

typedef struct {
	unsigned char r, g, b;
} Pixel;

// Item Sprites
extern const char itemSprites[NUM_ITEMS][SPRITE_SIZE][SPRITE_SIZE];
extern const char tileSprites[NUM_TILES][SPRITE_SIZE][SPRITE_SIZE];

#endif