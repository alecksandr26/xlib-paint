
#include <assert.h>
#include <X11/Xlib.h>

#include "../include/graphics.h"
#include "../include/window.h"
#include "../include/colors.h"

XGCValues gc_vals = {0};
unsigned long valuemask;
GC gc;

void create_graphics_contex(XftColor *fg, int lw)
{

	
	assert(dp != NULL && "To create the graphics contex the display needs to be open");
	assert(src != -1 && "To create the graphics contex the display needs to be open");
	
	gc_vals.line_style = LineSolid;
	gc_vals.line_width = lw;
	gc_vals.cap_style = CapButt;
	gc_vals.fill_style = FillSolid;
	gc_vals.foreground = fg->pixel;
	gc_vals.background = COLORS[WHITE].pixel;

	valuemask = GCForeground | GCBackground
		| GCFillStyle | GCLineStyle | GCLineWidth | GCCapStyle | GCJoinStyle;
	gc = XCreateGC(dp, root, valuemask, &gc_vals);
}
