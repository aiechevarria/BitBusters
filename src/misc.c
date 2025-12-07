#include "misc.h"

unsigned int rngState = SEED;

/**
 * Returns a pseudorandom number.
 * 
 * @return The pseudorandom number in range [0..255] 
 */
unsigned char pseudoRNG(void) {
    rngState = (1664525 * rngState + 1013904223);

    // Return the high 8 bits (better than low bits)
    return (rngState >> 24) & 0xFF;
}
