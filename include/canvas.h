#ifndef CANVAS_INCLUDED
#define CANVAS_INCLUDED

#include <X11/Xlib.h>

extern int canv_width, canv_height;
extern void draw_canvas(GC gc, int x, int y);
extern void draw_line_canvas(GC gc, int src_x, int src_y, int des_x, int des_y);
extern void init_canvas(void);
extern void del_canvas(void);
extern void clear_canvas(void);
extern void resize_canvas(int new_width, int new_height);
extern void refresh_canvas(void);

#endif


