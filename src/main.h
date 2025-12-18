#ifndef __MAIN_H__
#define __MAIN_H__

#define VGA_CTRL_BASE 0x44A00000

struct position {
	int x, y;
};
struct color {
	unsigned char r, g, b;
};

#define A {0x00, 0x00, 0xf0}
#define B {0x00, 0x00, 0x80}
#define C {0x00, 0x80, 0x00}
#define D {0x00, 0xf0, 0x00}
#define E {0xf0, 0xf0, 0x00}
#define F {0xf0, 0x00, 0x00}
#define W {0xff,0xff,0xff}
#define N {0,0,0}

static const struct color negro = N;
static const struct color blanco = W;
static const struct color azul = A;
static const struct color azul_oscuro = B;
static const struct color verde = C;
static const struct color verde_oscuro = D;
static const struct color amarillo = E;
static const struct color rojo = F;

struct color nave[11][11]={
	    {N,N,N,N,N,A,N,N,N,N,N},
		{N,N,N,N,A,B,A,N,N,N,N},
		{N,N,N,N,A,B,A,N,N,N,N},
		{N,N,N,A,B,C,B,A,N,N,N},
		{N,N,N,A,C,D,C,A,N,N,N},
		{N,A,N,A,B,C,B,A,N,A,N},
		{A,B,A,B,B,B,B,B,A,B,A},
		{A,B,B,B,B,B,B,B,B,B,A},
		{A,A,A,A,B,B,B,A,A,A,A},
		{A,E,F,E,A,A,A,E,F,E,A},
		{N,N,E,N,N,N,N,N,E,N,N}

};

// Función que pinta un pixel en pantalla
// X entre 0 y 159, Y entre 0 y 119,
// R/G/B: colores - entre 0 y 255 (los cuatro bits menos significativos se ignoran)
void pinta(int x, int y, struct color rgb);

// Función que retorna el valor de un pixel en pantalla
struct color pixel(int x, int y);

// Función que pinta un rectángulo de un color
// Pos: esquina superior izquierda del rectangulo
// Color: color del rectángulo
// W: anchura, H: altura
void rect (struct position pos, struct color col, int w, int h);


// Función que pinta una imagen en la VGA.
// Solo pinta los puntos que no son de color alfa (en este caso, negro), que se quedan "transparentes".
void imagen_11x11(struct position pos, struct color img[11][11]);


// Mueve la náve automáticamente de derecha a izquierda o viceversa
// El procedimiento para mover la nave es:
//        borrar la nave de pantalla, calcular la nueva posición, pintar la nave
void mueve_nave();

// Inicializa una bala en la posición X
void lanza_bala(int x);

// Mueve la bala, en vertical, hasta y = 0. Cuando llega ahí la desactiva
void mueve_bala();

#endif
