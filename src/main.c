#include "misc.h"
#include "levels.h"
#include "renderer.h"
#include "graphics.h"

// Pointer to the current loaded level
LevelInfo currentLevel;

int main() {
    initLevel(&currentLevel, 1);

    printLevelToConsole(currentLevel.bg, currentLevel.fg);

    return 0;
}