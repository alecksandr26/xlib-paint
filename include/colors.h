#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include <X11/Xft/Xft.h>

#define AMOUNT_COLORS 7

enum IND_COLORS {
	BLACK = 0,
	WHITE,
	RED,
	BLUE,
	GREEN,
	YELLOW,
	ORANGE,
};

#define DEFAULT_INITIAL_COLOR BLACK
#define DEFAULT_SWAP_COLOR WHITE

extern const char HEX_COLORS[AMOUNT_COLORS][8];
extern XftColor COLORS[AMOUNT_COLORS];

extern void create_colors(void);
extern void free_colors(void);
extern const char *color_name(enum IND_COLORS ind_color);

#endif

