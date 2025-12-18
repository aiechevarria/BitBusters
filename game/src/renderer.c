#include "renderer.h"
#include "graphics.h"
#include "levels.h"

// Referencia externa al nivel actual (definido en main.c)
// NOTA: Se ha corregido de puntero (*) a estructura directa para evitar errores de memoria.
extern LevelInfo currentLevel; 

/**
 * Convierte una estructura Pixel a un entero de 32 bits compatible con el hardware VGA.
 */
int rgbToInt(Pixel px) {
    return (px.r >> 4) | (px.b & 0xf0) | ((px.g & 0xf0) << 4);
}

/**
 * Dibuja un píxel individual.
 */
void drawPixel(int x, int y, Pixel rgb) {
    // Clipping para evitar escribir fuera de memoria
    if (x < 0 || x >= 160 || y < 0 || y >= 120) return;

	if (rgb.r != 0xff || rgb.g != 0xff || rgb.b != 0xff) {
        // Usamos volatile para asegurar la escritura en hardware
		volatile int* ptr = (int*) VGA_BASE;
		int val = rgbToInt(rgb);
		ptr[(y << 8) | x] = val;
	}
}

/**
 * Dibuja un rectángulo relleno de un color sólido.
 * Optimizado para escribir directamente en memoria.
 */
void drawRect(int x, int y, int width, int height, Pixel color) {
    volatile int* ptr = (int*) VGA_BASE;
    int colorVal = rgbToInt(color);
    
    // Clipping básico para evitar escribir fuera de la pantalla (160x120)
    int startX = (x < 0) ? 0 : x;
    int startY = (y < 0) ? 0 : y;
    int endX = x + width;
    int endY = y + height;

    if (endX > 160) endX = 160;
    if (endY > 120) endY = 120;

    for (int i = startY; i < endY; i++) {
        for (int j = startX; j < endX; j++) {
            ptr[(i << 8) | j] = colorVal;
        }
    }
}

/**
 * Dibuja un sprite de 12x12 píxeles (Nueva función).
 * Ignora los píxeles con color TS_RGB.
 */
void drawSprite(int x, int y, const Pixel sprite[SPRITE_SIZE][SPRITE_SIZE]) {
    volatile int* ptr = (int*) VGA_BASE;

    for (int i = 0; i < SPRITE_SIZE; i++) {
        int currentY = y + i;
        if (currentY < 0 || currentY >= 120) continue;

        for (int j = 0; j < SPRITE_SIZE; j++) {
            int currentX = x + j;
            if (currentX < 0 || currentX >= 160) continue;

            Pixel px = sprite[i][j];

            // Transparencia
            if (px.r == 0xff && px.g == 0xff && px.b == 0xff) {
                continue;
            }

            ptr[(currentY << 8) | currentX] = rgbToInt(px);
        }
    }
}

// --- Lógica de Fuente Numérica (Añadido para el HUD) ---

// Mapas de bits (3x5) para los números 0-9
static const unsigned char fontNum[10][5] = {
    {0x7, 0x5, 0x5, 0x5, 0x7}, // 0
    {0x2, 0x2, 0x2, 0x2, 0x2}, // 1
    {0x7, 0x1, 0x7, 0x4, 0x7}, // 2
    {0x7, 0x1, 0x7, 0x1, 0x7}, // 3
    {0x5, 0x5, 0x7, 0x1, 0x1}, // 4
    {0x7, 0x4, 0x7, 0x1, 0x7}, // 5
    {0x7, 0x4, 0x7, 0x5, 0x7}, // 6
    {0x7, 0x1, 0x1, 0x1, 0x1}, // 7
    {0x7, 0x5, 0x7, 0x5, 0x7}, // 8
    {0x7, 0x5, 0x7, 0x1, 0x7}  // 9
};

void drawDigit(int x, int y, int digit, Pixel color) {
    if (digit < 0 || digit > 9) return;
    for (int row = 0; row < 5; row++) {
        unsigned char line = fontNum[digit][row];
        for (int col = 0; col < 3; col++) {
            if ((line >> (2 - col)) & 0x01) drawPixel(x + col, y + row, color);
        }
    }
}

/**
 * Dibuja un número entero en pantalla usando la fuente interna.
 */
void drawNumber(int x, int y, int number, Pixel color) {
    char buffer[10];
    int i = 0;
    if (number == 0) { drawDigit(x, y, 0, color); return; }
    while (number > 0 && i < 10) { buffer[i++] = number % 10; number /= 10; }
    for (int j = i - 1; j >= 0; j--) {
        drawDigit(x, y, buffer[j], color);
        x += 4;
    }
}

/**
 * Dibuja el fondo del tablero (celdas de 12x12).
 * Sin bordes ni espacios entre celdas.
 */
void renderBoardBackground() {
    for (int i = 0; i < MAX_X_SPRITES; i++) {
        for (int j = 0; j < MAX_Y_SPRITES; j++) {
            int screenY = i * SPRITE_SIZE;
            int screenX = j * SPRITE_SIZE;
            
            Tile t = currentLevel.bg[i][j];

            if (t >= 0 && t < NUM_TILES) {
                drawSprite(screenX, screenY, tileSprites[t]);
            }
        }
    }
}

void renderEndScreen(bool won, int finalScore) {
    // 1. Limpiar pantalla (Negro)
    drawRect(0, 0, 160, 120, (Pixel)BK_RGB);

    // 2. Definir colores
    Pixel mainColor = won ? (Pixel)GS_RGB : (Pixel)RS_RGB; // Verde o Rojo
    
    // 3. Dibujar Marco
    drawRect(10, 10, 140, 100, mainColor);       // Caja llena
    drawRect(15, 15, 130, 90, (Pixel)BK_RGB);    // Hueco negro dentro

    // 4. Dibujar Símbolo Gigante (Pixel art manual con drawRect)
    if (won) {
        // Dibuja un "CHECK" (✓) Verde
        // Parte corta
        drawRect(40, 60, 10, 10, mainColor);
        drawRect(45, 65, 10, 10, mainColor);
        // Parte larga
        drawRect(55, 70, 10, 10, mainColor);
        drawRect(65, 60, 10, 10, mainColor);
        drawRect(75, 50, 10, 10, mainColor);
        drawRect(85, 40, 10, 10, mainColor);
    } else {
        // Dibuja una "X" Roja
        // Diagonal 1 (\)
        drawRect(40, 40, 10, 10, mainColor);
        drawRect(50, 50, 10, 10, mainColor);
        drawRect(60, 60, 10, 10, mainColor);
        drawRect(70, 70, 10, 10, mainColor);
        drawRect(80, 80, 10, 10, mainColor);
        // Diagonal 2 (/)
        drawRect(80, 40, 10, 10, mainColor);
        drawRect(70, 50, 10, 10, mainColor);
        // (El centro 60,60 ya está dibujado)
        drawRect(50, 70, 10, 10, mainColor);
        drawRect(40, 80, 10, 10, mainColor);
    }

    // 5. Mostrar Puntuación Final a la derecha
    // Título "SC" (Score) simplificado visualmente o solo el número
    drawRect(110, 40, 20, 5, (Pixel)SP_RGB); // Etiqueta amarilla
    drawNumber(110, 50, finalScore, (Pixel)WH_RGB);
}

/**
 * Dibuja los items (frutas) sobre el tablero.
 * Sin bordes ni espacios (padding eliminado).
 */
void renderBoardForeground() {
    for (int i = 0; i < MAX_Y_SPRITES; i++) {
        for (int j = 0; j < MAX_X_SPRITES; j++) {
            Item item = currentLevel.fg[i][j];

            if (item != ITEM_EMPTY && item >= 0 && item < NUM_ITEMS) {
                int screenY = i * SPRITE_SIZE;
                int screenX = j * SPRITE_SIZE;
                drawSprite(screenX, screenY, itemSprites[item]);
            }
        }
    }
}

/**
 * Dibuja el panel de información a la derecha (HUD).
 * Ocupa desde x=120 hasta x=160.
 */
void renderInfoPanel() {
    // 1. Fondo del panel y línea separadora
    drawRect(120, 0, 40, 120, (Pixel){0x00, 0x00, 0x40}); // Fondo azul oscuro
    drawRect(120, 0, 1, 120, (Pixel)WH_RGB);             // Línea blanca vertical

    // 2. Score (Etiqueta y Valor Numérico)
    drawRect(125, 10, 30, 5, (Pixel)SP_RGB); // Título "Score" (Amarillo)
    drawNumber(126, 20, currentLevel.score, (Pixel)WH_RGB); // Puntuación

    // 3. Moves (Etiqueta y Valor Numérico)
    drawRect(125, 40, 30, 5, (Pixel)RS_RGB); // Título "Moves" (Rojo)
    drawNumber(126, 50, currentLevel.moves, (Pixel)WH_RGB); // Movimientos
    
    // 4. Level (Indicador visual)
    drawRect(125, 80, 30, 5, (Pixel)OS_RGB); // Título "Level" (Naranja)
    drawRect(135, 90, 10, 10, (Pixel)WH_RGB); // Cuadrado blanco indica nivel activo
}

// Variables de estado del cursor (definidas en main.c)
extern uint8 cursorX;
extern uint8 cursorY;
extern int8 selectedX;
extern int8 selectedY;

/**
 * Función vacía para el menú (se implementará después)
 */
/**
 * Dibuja el menú de selección de niveles.
 * Muestra 3 cajas. La caja del nivel 'selection' se pinta de amarillo.
 */
void renderMenu(int selection) { 
    // Limpiar fondo (negro)
    drawRect(0, 0, 160, 120, (Pixel)BK_RGB);

    // Titulo (Barra superior azul)
    drawRect(0, 0, 160, 20, (Pixel){0x00, 0x00, 0x80});
    
    // Configuración de las cajas
    int startX = 25;
    int startY = 45;
    int boxSize = 30;
    int gap = 10;

    for (int i = 0; i < MAX_LEVELS; i++) {
        int x = startX + (i * (boxSize + gap));
        
        // Color: Amarillo si está seleccionado, Gris si no
        Pixel boxColor = (i == selection) ? (Pixel)SP_RGB : (Pixel)C2_RGB;
        Pixel numColor = (i == selection) ? (Pixel)BK_RGB : (Pixel)WH_RGB;

        // Dibujar caja rellena
        drawRect(x, startY, boxSize, boxSize, boxColor);
        
        // Dibujar borde blanco
        drawRect(x, startY, boxSize, 1, (Pixel)WH_RGB);
        drawRect(x, startY + boxSize - 1, boxSize, 1, (Pixel)WH_RGB);
        drawRect(x, startY, 1, boxSize, (Pixel)WH_RGB);
        drawRect(x + boxSize - 1, startY, 1, boxSize, (Pixel)WH_RGB);

        // Dibujar el número del nivel dentro
        // Ajuste: +13 en X y +12 en Y para centrar el número en la caja de 30x30
        drawNumber(x + 13, startY + 12, i, numColor);
    }

    // Barra decorativa inferior
    drawRect(0, 100, 160, 2, (Pixel)RS_RGB);
}

/**
 * Dibuja el cursor y la selección.
 */
void renderCursor() {
    // 1. Dibujar selección (si existe)
    if (selectedX != -1 && selectedY != -1) {
        int sx = selectedX * SPRITE_SIZE;
        int sy = selectedY * SPRITE_SIZE;
        // Borde amarillo para selección
        Pixel col = (Pixel)SP_RGB;
        drawRect(sx, sy, SPRITE_SIZE, 1, col); // Top
        drawRect(sx, sy + SPRITE_SIZE - 1, SPRITE_SIZE, 1, col); // Bottom
        drawRect(sx, sy, 1, SPRITE_SIZE, col); // Left
        drawRect(sx + SPRITE_SIZE - 1, sy, 1, SPRITE_SIZE, col); // Right
    }

    // 2. Dibujar cursor
    int cx = cursorX * SPRITE_SIZE;
    int cy = cursorY * SPRITE_SIZE;
    // Borde blanco parpadeante o fijo para el cursor
    Pixel col = (Pixel)WH_RGB;
    drawRect(cx, cy, SPRITE_SIZE, 1, col); // Top
    drawRect(cx, cy + SPRITE_SIZE - 1, SPRITE_SIZE, 1, col); // Bottom
    drawRect(cx, cy, 1, SPRITE_SIZE, col); // Left
    drawRect(cx + SPRITE_SIZE - 1, cy, 1, SPRITE_SIZE, col); // Right
}





/**
 * Función maestra de dibujado. Llama a todas las capas en orden.
 */
void renderAll() {
    renderBoardBackground();
    renderBoardForeground();
    renderCursor();
    renderInfoPanel();
}