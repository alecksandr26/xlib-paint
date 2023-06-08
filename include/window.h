#ifndef WINDOW_INCLUDED
#define WINDOW_INCLUDED

#include <X11/Xlib.h>

#define DEFAULT_POSX 500
#define DEFAULT_POSY 500

#define DEFAULT_MIN_WIDTH 640
#define DEFAULT_MIN_HEIGHT 480

#define DEFAULT_MAX_WIDTH 1920
#define DEFAULT_MAX_HEIGHT 1080

#define DEFAULT_BORDER_WIDTH 1

extern Display *dp;
extern int src;
extern Window root;
extern Visual *vis;
extern Window create_window(int x, int y, int w, int h, int bw, const char *name);
extern void open_display(void);
extern void close_display(Window win);

#endif


