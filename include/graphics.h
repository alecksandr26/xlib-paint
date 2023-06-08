#ifndef GRAPHICS_INCLUDED
#define GRAPHICS_INCLUDED

#include <X11/Xlib.h>
#include <X11/Xft/Xft.h>

#define DEFAULT_LINE_WIDTH 5
extern XGCValues gc_vals;
extern unsigned long valuemask;
extern GC gc;

extern void create_graphics_contex(XftColor *fg, int lw);

#endif
