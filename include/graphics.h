#ifndef GRAPHICS_INCLUDED
#define GRAPHICS_INCLUDED

#include <X11/Xlib.h>
#include "../include/colors.h"

extern GC create_graphics_contex(COLOR color, int width);
extern void mod_graphics_contex(GC gc, COLOR color, int width);
extern void free_graphics_contex(GC gc);

#endif
