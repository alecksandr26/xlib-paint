#include <malloc.h>
#include <assert.h>
#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>
#include <err.h>

#include "../include/window.h"
#include "../include/colors.h"

#define COLOR_NAME_LEN 20

static const char COLOR_NAME[AMOUNT_COLORS][COLOR_NAME_LEN] = {
	"Black",
	"White",
	"Red",
	"Blue",
	"Green",
	"Yellow",
	"Orange",
	"Purpule",
};

const char HEX_COLORS[AMOUNT_COLORS][8] = {
	"#000000\0",		/* Black */
	"#FFFFFF\0",		/* White */
	"#FF0000\0",		/* Red */
	"#0000FF\0", 		/* Blue */
	"#00FF00\0", 		/* Green */
	"#FFFF00\0",		/* Yellow */
	"#FFA500\0", 		/* Orange */
	"#800080\0",		/* Purpule */
};

XftColor COLORS[AMOUNT_COLORS] = {0};

void create_colors(void)
{
	assert(dp != NULL && "To create the graphics contex the display needs to be open");
	assert(src != -1 && "To create the graphics contex the display needs to be open");
	
	for (size_t i = 0; i < AMOUNT_COLORS; i++)
		if (!XftColorAllocName(dp, vis, DefaultColormap(dp, src), HEX_COLORS[i], &COLORS[i]))
			errx(1, "XftColorAllocName: Can't allocate color");
}

void free_colors(void)
{
	for (size_t i = 0; i < AMOUNT_COLORS; i++)
		XftColorFree(dp, vis, XDefaultColormap(dp, src), &COLORS[i]);
}

const char *color_name(COLOR color)
{
	return (const char *)  COLOR_NAME[color];
}

