#include <assert.h>

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xatom.h>
#include <X11/Xft/Xft.h>
#include <err.h>

#include "../include/window.h"
#include "../include/colors.h"
#include "../include/utils.h"

Display *dp = NULL;
int src = -1;
Window root = {0};
Visual *vis = NULL;

void win_size(Window win, int *w, int *h)
{
	int x, y;
	unsigned int bw, d;
	XGetGeometry(dp, win, &root, &x, &y, (unsigned int *) w, (unsigned int *) h, &bw, &d);
}

Window create_window(int x, int y, int w, int h, const char *win_name)
{
	Window win;
	XSetWindowAttributes watt = {0};
	assert(dp != NULL && "To execute this thing you need to open a display");
	assert(src != -1 && "You must to have an screen number");
	
	watt.background_pixel = COLORS[WHITE].pixel;
	watt.border_pixel = COLORS[BLACK].pixel;

	watt.event_mask = Button1MotionMask | ButtonPressMask | ButtonReleaseMask
		| KeyPressMask | PointerMotionMask | LeaveWindowMask | StructureNotifyMask
		| ExposureMask;
	
	/* Border with zero */
	win = XCreateWindow(dp, root, x, y, w, h, DEFAULT_BORDER_WIDTH,
			    DefaultDepth(dp, src), InputOutput,  vis,
			    CWBackPixel | CWBorderPixel | CWEventMask, &watt);

	XSizeHints xsh = {
		.min_width = DEFAULT_MIN_WIDTH,
		.min_height = DEFAULT_MIN_HEIGHT,
		.max_width = DEFAULT_MAX_WIDTH,
		.max_height = DEFAULT_MAX_HEIGHT
	};

	xsh.flags = PMinSize | PMaxSize;
	XSetSizeHints(dp, win, &xsh, XA_WM_NORMAL_HINTS);
	
	XStoreName(dp, win, win_name);
	XMapWindow(dp, win);

	LOG("Window %s created", win_name);
	return win;
}

void destroy_window(Window win)
{
	XUnmapWindow(dp, win);
	XDestroyWindow(dp, win);
}

void open_display(void)
{
	dp = XOpenDisplay(NULL); /* Open the defualt dispaly */
	if (dp == NULL) errx(1, "The display should be open can't be null");
	
	src = DefaultScreen(dp);
	root = RootWindow(dp, src);
	vis = DefaultVisual(dp, src);
	
	LOG("Display opened");
}

void close_display(void)
{
	assert(dp != NULL && "The display should be open can't be null");

	XCloseDisplay(dp);
	
	LOG("Display closed");
}

