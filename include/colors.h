#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include <X11/Xft/Xft.h>

#define AMOUNT_COLORS 8

typedef enum {
	NONE_COLOR = -1,
	BLACK = 0,
	WHITE,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	ORANGE,
	PURPULE,
} COLOR;

#define DEFAULT_INITIAL_COLOR BLACK
#define DEFAULT_SWAP_COLOR WHITE

extern const char HEX_COLORS[AMOUNT_COLORS][8];
extern XftColor COLORS[AMOUNT_COLORS];

extern void create_colors(void);
extern void free_colors(void);
extern const char *color_name(COLOR color);

#endif

