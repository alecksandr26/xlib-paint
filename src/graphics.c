#include <assert.h>
#include <X11/Xlib.h>

#include "../include/graphics.h"
#include "../include/window.h"
#include "../include/colors.h"
#include "../include/utils.h"
#include "../include/tools.h"

GC create_graphics_contex(COLOR color, int width)
{
	GC gc;
	XGCValues vals = {0};
	unsigned long valuemask;
	
	assert(dp != NULL && "To create the graphics contex the display needs to be open");
	assert(src != -1 && "To create the graphics contex the display needs to be open");
	
	vals.line_style = LineSolid;
	vals.line_width = width;
	vals.cap_style = CapButt;
	vals.fill_style = FillSolid;
	
	vals.foreground = COLORS[color].pixel;
	vals.background = COLORS[WHITE].pixel;

	valuemask = GCForeground | GCBackground
		| GCFillStyle | GCLineStyle | GCLineWidth | GCCapStyle | GCJoinStyle;
	
	gc = XCreateGC(dp, root, valuemask, &vals);
	LOG("Graphics Created");
	
	return gc;
}

void free_graphics_contex(GC gc)
{
	XFreeGC(dp, gc);
}

void mod_graphics_contex(GC gc, COLOR color, int width)
{
	XSetLineAttributes(dp, gc, width, LineSolid, CapButt, FillSolid);
	XSetForeground(dp, gc, COLORS[color].pixel);
	LOG("Graphics Changed %s - %i", color_name(color), width);
}
